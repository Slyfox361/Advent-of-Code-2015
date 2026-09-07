#include <iostream>
using namespace std;

int main()
{
    //getting directions input
    string directions;
    cout << "Enter the Directions: ";
    cin >> directions;
    //for second task to track when the basement has been entered
    bool foundBasement = false;

    //track the floor number. set to zero as it defaults to 1
    int floor = 0;

    //for loop to cycle through the string
    for (int i = 0; i<directions.length();i++)
    {
        //gets the current character
        char d = directions[i];

        //checking which it is
        if (d == '(') //go up if this
        {
            floor++;
        }
        else if (d == ')') //go down if this
        {
            floor--;
        }
        else //error handling
        {
            cout << d << " is an unrecognised character";
        }

        //checking for the basement floor
        if (floor == -1 && !foundBasement)
        {
            cout << "Basement Location: " << i+1 << endl;
            foundBasement = true; //marking it so it doesn't 'discover' it again
        }
    }

    //print results
    cout << "\nFinal Floor: " << floor << endl;
}