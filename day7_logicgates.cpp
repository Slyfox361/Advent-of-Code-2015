#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

//this stores details on each wire. i considered turning it into a struct but my code did work with it this way after i fixed the other issues
class wire
{
    public:
        //it needs 3 details
        string name;
        int signal;
        string gate[5] = {"", "", "", "", ""}; //this is the instruction given in the input, split into an array to be easier to read

        //a constructor
        wire(string n)
        {
            name = n;
            signal = 0;
        }
};

wire* searchList(list<wire*> circuit, string n) //this is a very simple linear search algorithm so i can navigate my list of wires
{
    list<wire*>::iterator it = circuit.begin(); //it uses an iterator to cycle through the list
    while (it != circuit.end())
    {
        wire* w = *it;
        if (w->name == n) //if it finds the item, it returns it
        {
            return w;
        }
        advance(it,1);
    }

    return nullptr; //otherwise it returns a nullptr
}

bool isDigit(string& s) //this is just to check if the 'word' is a number
{
    for (char c : s) //cycling through the string
    {
        int val = c; //converts the char to ASCII
        if(!(c >= 48 && c <= 57)) //it checks the ASCII value and if it is outside this range, it's a number
        {
            return false;
        }
    }
    return true;
}

void generateSignal(list<wire*> circuit, wire* w) //this is how i process the instructions. it is a recursive algorithm that goes through the instructions until it finds one that has already been defined
{
    if (w->gate[0] == "NOT") //if it finds a NOT gate
    {
        wire* w1 = searchList(circuit, w->gate[1]); //gets the other wire

        if (w1->signal == 0) //checks if the wire has a signal (which is a good indicator if it has been defined or not)
        {
            cout << w1->name << "(" << w1->signal << ") " << " has no signal --------" << endl;
            generateSignal(circuit, w1); //if it has no signal, it processes that wire's instructions in order to find out what signal it has
        }

        w->signal = ~w1->signal; //when it confirms the wire has been defined, it applies a NOT (~) gate
        cout << "NOT (" << w1->name << ") " << w1->signal << " = " << "(" << w->name << ") " << w->signal << endl;
    }
    else
    {
        if (w->gate[1] == "AND" || w->gate[1] == "OR") //if it finds an AND or an OR gate
        {
            wire* w1 = searchList(circuit, w->gate[0]); //gets the other wire

            if (w1 != nullptr) //checks the wire exists (because sometimes the AND gates use a wire and a number)
            {
                if (w1->signal == 0) //checks if the wire has a signal
                {
                    cout << w1->name << "(" << w1->signal << ") " << " has no signal -------------" << endl;
                    generateSignal(circuit, w1); //if it has no signal, it processes that wire
                }
            }
            
            //same as above, except the check for nullptr, because it always exists (in the given input)
            wire* w2 = searchList(circuit, w->gate[2]);

            if (w2->signal == 0)
            {
                cout << w2->name << "(" << w2->signal << ") " << " has no signal ---------------" << endl;
                generateSignal(circuit, w2);
            }
            

            if (w->gate[1] == "AND" && w1 == nullptr) //if it is an AND gate with a number and wire input
            {
                w->signal = stoi(w->gate[0]) & w2->signal; //it applies the AND (&) gate
                cout << w->gate[0] << " AND " << "(" << w2->name << ") " << w2->signal << " = " << "(" << w->name << ") " << w->signal << endl;
            }
            else if (w->gate[1] == "AND") //if it is an AND gate with two wire inputs
            {
                w->signal = w1->signal & w2->signal; //it applies the AND (&) gate
                cout << "(" << w1->name << ") " << w1->signal << " AND " << "(" << w2->name << ") " << w2->signal << " = " << "(" << w->name << ") " << w->signal << endl;
            }
            else //if it is an OR gate
            {
                w->signal = w1->signal | w2->signal; //it applies the OR (|) gate
                cout << "(" << w1->name << ") " << w1->signal << " OR " << "(" << w2->name << ") " << w2->signal << " = " << "(" << w->name << ") " << w->signal << endl;
            }
        }
        else if (w->gate[1] == "LSHIFT" || w->gate[1] == "RSHIFT") //if it finds a (L/R)SHIFT gate
        {
            //finding the wires is the same as above. there's only one wire input here

            wire* w1 = searchList(circuit, w->gate[0]);

            if (w1->signal == 0)
            {
                cout << w1->name << "(" << w1->signal << ") " << " has no signal ------------" << endl;
                generateSignal(circuit, w1);
            }
            
            if (w->gate[1] == "LSHIFT") //if it is an LSHIFT
            {
                w->signal = (w1->signal)<<stoi(w->gate[2]); //it applies the LSHIFT (<<) gate with the given int input
                cout << "(" << w1->name << ") " << w1->signal << " LSHIFT " << w->gate[2] << " = " << "(" << w->name << ") " << w->signal << endl;
            }
            else //if it is an RSHIFT
            {
                w->signal = (w1->signal)>>stoi(w->gate[2]); //it applies the RSHIFT (>>) gate with the given int input
                cout << "(" << w1->name << ") " << w1->signal << " RSHIFT " << w->gate[2] << " = " << "(" << w->name << ") " << w->signal << endl;
            }
        }
        else //otherwise, it is (what i call) a definition. a straight equals
        {
            if (!(isDigit(w->gate[0]))) //checking if it has already been defined or not (because some are defined as 0 which flags, because it reads as no signal)
            {
                //if it has not been defined, it finds the wire (same as above)
                wire* w1 = searchList(circuit, w->gate[0]);

                if (w1->signal == 0)
                {
                    cout << w1->name << "(" << w1->signal << ") " << " has no signal ------------" << endl;
                    generateSignal(circuit, w1);
                }

                //then it performs the assignment
                w->signal = w1->signal;
            }
        }
    }
}

int main()
{
    //getting my input from a file
    ifstream input("gates.txt");
    string line;
    string word;

    //my list of wires
    list<wire*> circuit;

    while (getline(input, line)) //splitting the file into lines and cycling through them
    {
        //this breaks down the line into an array of words, so i can process the instruction
        stringstream ss(line);
        string sentence[5];
        int count = 0;
        while (ss >> word)
        {
            sentence[count] = word;
            count++;
        }

        //this creates the wires and adds them to the list. the only distinction is which index the wire's name is (and if it has a definition)
        if (sentence[0] == "NOT") //for NOT gates the input is: NOT inputWire -> outputWire
        {
            circuit.push_back(new wire(sentence[3])); //so the wire name is the 3rd index (4th word)
            wire* w = circuit.back();

            //it then gives the wire the intructions so it knows how it is defined (and can be processed later)
            for (int i=0; i<5; i++)
            {
                w->gate[i] = sentence[i]; 
            }
        }
        else if ((isDigit(sentence[0]) || sentence[3] == "") && sentence[1] == "->") //for definitions, the input is: inputWire/number -> outputWire
        {
            circuit.push_back(new wire(sentence[2])); //the wire name is the 2nd index (3rd word)
            wire* w = circuit.back();

            if (isDigit(sentence[0])) //if the firs index is a number, the wire's signal can be applied
            {
                w->signal = stoi(sentence[0]);
            }

            //they are all give their instructions for the case where the wire signal is defined as 0
            for (int i=0; i<5; i++)
            {
                w->gate[i] = sentence[i];
            }
        }
        else //AND and OR have similar setups: inputWire1 AND/NOT inputWire2 -> outputWire. the SHIFTS are also similar in their positions: inputWire L/RSHIFT number -> outputWire
        {        
            circuit.push_back(new wire(sentence[4])); //the wire name is the 4th index (5th word)
            wire* w = circuit.back();

            for (int i=0; i<5; i++)
            {
                w->gate[i] = sentence[i]; 
            }
        }
    }

    input.close(); //close the file!

    //now the circuit is complete (all the wires are accounted for) i can process their instructions
    wire* destinationWire = searchList(circuit, "a"); //set the destination wire (it can be any and this prevents any unecessary calculations)
    generateSignal(circuit, destinationWire); //start the recursive algorithm

    //printing my wires (as a debug)
    cout << "Wires : {";
    list<wire*>::iterator it = circuit.begin();
    while (it != circuit.end())
    {
        wire* w = *it;
        cout << "{" << w->name << ", " << w->signal << "} ";
        advance(it,1);
    }
    cout << " }" << endl;

    //printing my results
    cout << "Destination wire: " << destinationWire->name << ", " << destinationWire->signal << endl;

    //for part two, take the answer from part 1 (16076) and replace b's definition with it (on line ~55)
}