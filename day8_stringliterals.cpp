#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isHexDigit(char& c) //this is just to check if the char is a hex value
{
    int val = c; //converts the char to ASCII
    if(!(c >= 48 && c <= 57) && !(c >= 97 && c <= 102)) //it checks the ASCII value and if it is outside this range, it's a hex value
    {
        return false;
    }
    return true;
}

int main()
{
    //getting my input from a file
    ifstream input("strings.txt");
    string line;
    //storing my totals
    int storedChar = 0;
    int literalChar = 0;
    int newStoreChars = 0; //for part 2

    while (getline(input, line)) //going through line by line
    {
        //this is to check character combinaations
        string temp;

        for (char c : line) //cycling through each character
        {
            //cout << c << endl;

            //increasing both of these regardless
            storedChar++;
            newStoreChars++;

            if (temp != "") //if temp is not empty
            {
                if (temp == "\\") //if it only has a backslash
                {
                    if (c == '\\' || c == '"') //if c has a \ or a " that is the same as one character
                    {
                        literalChar++;
                        newStoreChars++; //encoding adds an additional here to make something like \\\" if it was \"
                        temp = "";
                    }
                    else if (c == 'x') //if it's an x it could be a character code
                    {
                        temp += c; //temp store the info for later
                    }
                }
                //these next ones check if it's a character code
                else if (temp == "\\x" && isHexDigit(c)) //this is for when the next character is a hex digit
                {
                    temp += c;
                }
                else if (temp == "\\x" && !isHexDigit(c)) //this is for when it isn't
                {
                    temp = "";
                    literalChar += 3; //the characters are added here to make up for the mistake
                }
                else if (temp.length() == 3 && isHexDigit(c)) //this is for if it finds a complete character code
                {
                    literalChar++;
                    temp = "";
                }
                else if (temp.length() == 3 && !isHexDigit(c)) //this is like the above, making up for a mistaken character code
                {
                    temp = "";
                    literalChar += 4;
                }
            }
            else if (c == '\\') //this is when c is a backslash
            {
                temp += c;
                newStoreChars++; //adds an additional to make a double backslash
            }
            else if (c == '"') //this is for the outside quotes
            {
                newStoreChars += 2; //adds an additional 2 to make "\" or \""
            }
            else //otherwise it's a regular character a-z, 0-9
            {
                literalChar++;
            }
        }
    }

    //printing all my results
    cout << "Total Chars: " << storedChar << endl;
    cout << "Encoded Total Chars: " << newStoreChars << endl;
    cout << "Literal Chars: " << literalChar << endl;
    cout << "Difference of Literal and Total: " << storedChar - literalChar << endl;
    cout << "Difference of the Totals: " << newStoreChars - storedChar << endl;
}