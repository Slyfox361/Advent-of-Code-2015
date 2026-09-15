#include <iostream>
#include <vector>
#include <string>
using namespace std;

string lookAndSay(string s) //this calculates the new string
{
    string newSequence;
    vector<char> temp;

    for (int i=0; i<=s.length(); i++) //iterate through the string
    {
        //setting c (since it needs to run once more at the end to count all the characters)
        char c;
        if (i < s.length())
        {
            c = s[i];
        }
        else
        {
            c = 'f';
        }
         
        if (temp.size() > 0) //if temp is populated
        {
            if (c == temp.back() && i < s.length()) //if c is the same as the last digit in temp (they should all be the same)
            {
                temp.push_back(c); //add it to the list
            }
            else //otherwise it's a new character
            {
                char num = temp.size() + '0'; //turn the length of temp into a char
                newSequence += num; //add it to the back of the new sequence
                newSequence += temp.back(); //and add the character it counted
                if (c != 'f') //if it is not the last (overflow)
                {
                    temp.clear(); //clear temp
                    temp.push_back(c); //add the new character
                }
            }
        }
        else if (s.length() == 1 && i < s.length()) //if the length of s is 1 it is a special case
        {
            //add 1 and the character counted
            newSequence += "1";
            newSequence += c;
        }
        else //otherwise it's an empty list, so add c
        {
            temp.push_back(c);
        }
    }

    return newSequence; //return the new sequence
}

int main()
{
    //get the input
    string sequence;
    cout << "Enter the input: ";
    cin >> sequence;

    //get how many times to repeat it
    int repetitions; //will be 0 if not a number
    cout << "Enter the repetitions: ";
    cin >> repetitions;

    for (int r=0; r<repetitions; r++) //iterate through the correct amount
    {
        //calculate the sequence using the function
        sequence = lookAndSay(sequence);
        cout << "Current sequence: " << sequence << endl;
    }

    //printing results
    cout << "Result: " << sequence << endl;
    cout << "Length of result: " << sequence.length() << endl;
}