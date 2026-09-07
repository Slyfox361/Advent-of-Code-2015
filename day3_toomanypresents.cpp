#include <iostream>
#include <list>
#include <string>
using namespace std;

int main()
{
    //coordinate vals (r = robot for part 2)
    int x = 0;
    int y = 0;
    int rx = 0;
    int ry = 0;
    //finding all the unique positions (and ones visited 2+ times cause i misinterpreted the prompt. this overcomplicated it severely but i kept it because i did it anyway. it confuddled my brain cause i thought there was a smart way to do it. but NOPE i read it wrong and it was as simple as i imagined! note to future self "at least 1" INCLUDES 1. it makes sense with hindsight. but hindsight is 20/20)
    list<string> uniquePos = {"0,0"};
    list<string> housesRevisited;

    //input
    string input;
    cout << "Enter the directions: ";
    cin >> input;

    //cycling through the input
    for (int i = 0; i<input.length();i++)
    {
        if (i % 2 == 0) //starting with santa it alternates between him and his robot self
        {
            switch (input[i]) //it moves through the grid with the given instructions
            {
            case '^':
                x++;
                break;
            case 'v':
                x--;
                break;
            case '>':
                y++;
                break;
            case '<':
                y--;
                break;
            default:
                cout << "Unrecognised Character" << endl;
                break;
            }
        }
        else //likewise with the robot
        {
            switch (input[i])
            {
            case '^':
                rx++;
                break;
            case 'v':
                rx--;
                break;
            case '>':
                ry++;
                break;
            case '<':
                ry--;
                break;
            default:
                cout << "Unrecognised Character" << endl;
                break;
            }
        }
        
        //formatting the coords so they can be stored in a resonable way to check matches
        string c = to_string(x) + "," + to_string(y);
        string rc = to_string(rx) + "," + to_string(ry);

        //doing it once for santa
        if (find(uniquePos.begin(), uniquePos.end(), c) != uniquePos.end()) //checking if the c (coord) is already in the list
        {
            //if TRUE
            if (find(housesRevisited.begin(), housesRevisited.end(), c) == housesRevisited.end()) //same again, different list
            {
                //if FALSE
                housesRevisited.push_back(c); //add to the revisited list
            }
        }
        else
        {
            //if FALSE
            uniquePos.push_back(c); //add the new coord
        }

        //repeat for the robot using the same lists
        if (find(uniquePos.begin(), uniquePos.end(), rc) != uniquePos.end())
        {
            if (find(housesRevisited.begin(), housesRevisited.end(), rc) == housesRevisited.end())
            {
                housesRevisited.push_back(rc);
            }
        }
        else
        {
            uniquePos.push_back(rc);
        }
    }

    //printing for debugging
    cout << "Visited: {";
    list<string>::iterator it = uniquePos.begin();
    while (it != uniquePos.end())
    {
        cout << "{" << *it << "} ";
        advance(it,1);
    }
    cout << " }" << endl;
    cout << "Revisited: {";
    list<string>::iterator it2 = housesRevisited.begin();
    while (it2 != housesRevisited.end())
    {
        cout << "{" << *it2 << "} ";
        advance(it2,1);
    }
    cout << " }" << endl;
    
    //printing my results
    cout << "Houses Visited: " << uniquePos.size() << endl;
    cout << "Houses given multiple presents: " << housesRevisited.size() << endl;
}

