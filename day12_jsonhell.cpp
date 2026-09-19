#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isDigit(char& c) //this is just to check if the char is a number
{
    int val = c; //converts the char to ASCII
    if((c >= 48 && c <= 57) || c == 45) //it checks the ASCII value and if it is inside this range, it's a number
    {
        return true;
    }
    return false;
}

int main() //this was a lot simpler in part 1. i just needed to find the numbers and minuses. part 2 took wayyy too long, since there was no built in json library, so i wanted to code it myself... that choice put my through it and it took wayyy longer than it should. but once i started, i was determined to code it myself. hence it is not a perfect json decoder (if one at all) and just works for this very specific problem...
{
    //getting the input (which is a mess, might i add)
    fstream abacus("abacus.json");
    string line;

    //some variables
    int total = 0;
    string temp = ""; //stores any discovered numbers (as they are being found)
    string last3 = ""; //stores the last three to check if it's "red"
    vector<int> objectAndArraysStack = {0}; //used to be two stacks but making it one simplified the problem. it has one value to store the total it calculates
    vector<bool> redFound; //stores if the object has a "red" object (only counts alongside objects and not arrays)
    vector<string> thingsStack = {"null"}; //stores what type of 'thing' the data is in (object or array)

    while (getline(abacus, line))
    {
        for (char c : line) //cycling through all the characters
        {
            if (c == '{') //if it finds the start of an object
            {
                objectAndArraysStack.push_back(0); //add one to the numbers stack
                thingsStack.push_back("object"); //add "object" to the things stack
                redFound.push_back(false); //add a false to the red stack
            }
            else if (c == '[') //if it finds the start of an array
            {
                objectAndArraysStack.push_back(0); //add one to the numbers stack
                thingsStack.push_back("array"); //add "array" to the things stack
            }

            if (last3.length() < 3) //while last3 is less than 3 (literally the first two characters)
            {
                last3 += c; //just add the next character
            }
            else //for the rest of the document
            {
                string last2; //temporary to store the last 2 characters of the last3 string
                int count = 0; //coutn for index
                for (char l : last3)
                {
                    if (count > 0) //basically if it's not the first index
                    {
                        last2 += l; //add the character to last2
                    }
                    count++; //increment count
                }
                last3 = last2 + c; //change last3 to last2 (the last two chraracters of the previous last3 string) and the new character
            }

            if (last3 == "red" && thingsStack.back() == "object" && objectAndArraysStack.size() > 1) //if last3 is red and we are currently inside an object
            {
                redFound.back() = true; //change the last element of redFound to true
            }

            if (isDigit(c)) //if the current character is a digit or a minus
            {
                temp += c; //add it to temp
            }
            else //otherwise
            {
                if (temp != "") //if temp is not empty
                {
                    cout << "Number found: " << temp << endl; //its found a number!
                    objectAndArraysStack.back() += stoi(temp); //add it to the total of the current thing
                    temp = ""; //empty temp
                }

                if (c == '}') //if it has found the end of an object
                {
                    if (!redFound.back()) //if there is no red in the object
                    {
                        objectAndArraysStack[objectAndArraysStack.size()-2] += objectAndArraysStack.back(); //add its total to its parent
                    }
                    else //otherwise it has found a red
                    {
                        //nothing it added to the parent (the total is ignored)
                        cout << "Object Contains Red" << endl;
                    }

                    //pop all the things related to the object to return to the parent
                    objectAndArraysStack.pop_back();
                    thingsStack.pop_back();
                    redFound.pop_back();
                }
                else if (c == ']') //if it has found the end of an array
                {
                    objectAndArraysStack[objectAndArraysStack.size()-2] += objectAndArraysStack.back(); //add its total to its parent

                    //pop all the things related to the object to return to the parent
                    objectAndArraysStack.pop_back();
                    thingsStack.pop_back();
                }
            }
        }
    }

    abacus.close(); //close the file!

    total = objectAndArraysStack.front(); //the total is just the number left in the stack (at the front) it should be the only element left in the list

    //print my result
    cout << "Total counted: " << total << endl;
}