#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool checkPassword(vector<char> p) //this checks if the password meets the elve's standards
{
    //these check for the condition of a straight (abc, xyz) or two doubles (aa, zz)
    bool straightCheck = false;
    int doubleCheck = 0;
    char doubleChar = '0';

    for (int i=0; i<p.size(); i++) //cyclnig through the vector
    {
        if (p[i] == 'i' || p[i] == 'o' || p[i] == 'l') //if iit has any of these 'confusing' letters, it immediately fails
        {
            return false;
        }
        else if (i >= 2) //it needs to be past the 3rd index to check for the other conditions
        {
            if (p[i] == p[i-1] && p[i] != p[i-2] && doubleChar != p[i]) //if the two letters are the same as one another and differnt to the one before. (and also a different double to the first one if applicable)
            {
                doubleCheck++;
                if (doubleChar == '0') doubleChar = p[i];
            }

            if (i == 2) //only for the first instance this check is run as i need to account for the first character
            {
                if (p[i-1] == p[i-2] && p[i] != p[i-1] && doubleChar != p[i-1]) //this checks the first two characters as well
                {
                    doubleCheck++;
                    if (doubleChar == '0') doubleChar = p[i-1];
                }
            }
            
            //this is for the straight check. i turn all the characters into ascii to check for adjacent numbers
            int asciiOfC = int(p[i]);
            int ascii1 = int(p[i-1]);
            int ascii2 = int(p[i-2]);

            if (asciiOfC == ascii1+1 && asciiOfC == ascii2+2)
            {
                straightCheck = true;
            }
        }
    }

    if(straightCheck && doubleCheck >= 2) //if all checks are passed, the password passes
    {
        return true;
    }
    else //otherwise it fails
    {
        return false;
    }
}

vector<char> incrementPassword(vector<char> p) //this increments the password
{
    //due to it being more like a base of 24 rather than a base of 10, this check speeds up the process A LOT

    bool turnToA = false; //a marker to say if the rest of the characters are to be set to a (essentially 0)
    for (int j=0; j<p.size(); j++) //cycling through the vector
    {
        if (turnToA) //if the marker is true, just turn the character to an a
        {
            p[j] = 'a';
        }
        else if (p[j] == 'i' || p[j] == 'o' || p[j] == 'l') //otherwise check if it's an illegal character
        {
            //if so, increment that character and turn the rest to a (skipping all the passwords with that letter in)
            int asciiOfChar = int(p[j]);
            asciiOfChar++;
            p[j] = char(asciiOfChar);
            turnToA = true;
        }
    }

    if (turnToA) return p; //if this was true, the password has already been incremented

    //otherwise it does it normally
    for (int i=p.size()-1; i>=0; i--) //cycling through the password in reverse
    {
        int asciiOfChar = int(p[i]); //turning the character into ascii
        if (asciiOfChar < 122) //if it's less than z (122 in ascii)
        {
            asciiOfChar++; //increment the ascii
            p[i] = char(asciiOfChar); //turn it back into a char
            return p; //return the incremented password
        }
        else //otherwise it needs to wrap
        {
            p[i] = 'a'; //turn the character to a and continue to the next one
        }
    }

    return p; //returns down here in case it exits the for loop
}

int main()
{
    //getting the input
    string password;
    cout << "Enter the first password: ";
    cin >> password;

    //other varibales
    vector<char> passwordList; //makes it easier to read and manipulate the string
    bool check = false; //a marker to say if the password passes all the checks
    string newPassword; //the new password

    //turning the input into a vector
    for (char c : password)
    {
        passwordList.push_back(c);
    }

    while (!check) //while the password does not pass the checks
    {
        passwordList = incrementPassword(passwordList); //increment it
        check = checkPassword(passwordList); //check it

        //printing for debug
        newPassword.clear();
        for (char c : passwordList)
        {
            newPassword += c;
        }

        cout << newPassword << endl;

        cout << "Passed? " << check << endl;
    }

    //printing my result
    cout << "Final Password: " << newPassword << endl;
}