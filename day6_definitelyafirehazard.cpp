#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

class light //class to store data about each light
{
    public:
        int brightness = 0; //for part 2
        bool onOrOff = false; //for part 1

    void turnOnOrOff(bool onOff) //this is for 'turn on/off'
    {
        onOrOff = onOff; //it sets the internal bool to whatever the input is
        //then it adjusts the brightness
        if (onOff)
        {
            brightness++;
        }
        else
        {
            brightness--;
            if (brightness < 0) //making sure to keep it positive
            {
                brightness = 0;
            }
        }
    }

    void toggle() //this is for 'toggle'
    {
        //it toggles the bool on/off
        if (onOrOff)
        {
            onOrOff = false;
        }
        else
        {
            onOrOff = true;
        }

        brightness += 2; //adds 2 to brightness regardless
    }
};

int perfromAction(light grid[1000][1000], bool toggleOrTurn, int coord1[2], int coord2[2], bool onOff = true) //this function inacts the instruction given
{
    if (coord1[0] == -1) return 0; // making sure it's not the first one (as it calls before the instruction is read)

    //debug stuff
    cout << "Coord 1: " << coord1[0] << ", " << coord1[1] << endl;
    cout << "Coord 2: " << coord2[0] << ", " << coord2[1] << endl;
    cout << "Toggle Or Turn: " << toggleOrTurn << endl;
    cout << "On/Off: " << onOff << endl;

    if (!toggleOrTurn) //if it's a toggle action
    {
        //cycles through the coords given
        for (int x=coord1[0]; x<=coord2[0]; x++)
        {
            for (int y=coord1[1]; y<=coord2[1]; y++)
            {
                grid[x][y].toggle(); //calls the toggle function
            }
        }
    }
    else if (toggleOrTurn) //if it's a turn action
    {
        //cycles through the coords given
        for (int x=coord1[0]; x<=coord2[0]; x++)
        {
            for (int y=coord1[1]; y<=coord2[1]; y++)
            {
                grid[x][y].turnOnOrOff(onOff); //calls the turn on/off function
            }
        }
    }

    return 1;
}

int main()
{
    auto grid = new light[1000][1000]; //i realise this is an inefficent way to do it (not that i have a better idea) and it did crash when i added the brightness, but making it auto-allocate memory fixed the crash and gave me an output :D

    //getting the instructions from the file
    ifstream input("instructions.txt");
    string word;
    //storing the instruction and coords
    bool toggleOrTurn = false;
    bool onOff = true;
    bool firstOrSecond = false; //false = on the first, true = on the second
    int coord1[2] = {-1,-1};
    int coord2[2] = {-1,-1};

    while (input >> word) //splitting the file (it seems to give it a word at a time, hence i adapted my programming for that)
    {
        //flips the booleans based on the words, performing an action before the next line
        if (word == "toggle")
        {
            perfromAction(grid, toggleOrTurn, coord1, coord2, onOff);
            toggleOrTurn = false;
        }
        else if (word == "turn")
        {
            perfromAction(grid, toggleOrTurn, coord1, coord2, onOff);
            toggleOrTurn = true;
        }
        else if (word == "on")
        {
            onOff = true;
        }
        else if (word == "off")
        {
            onOff = false;
        }
        else if (word == "through") //no action when reaching this, but i need to catch it so it doesn't try to be a coord
        {
            continue;
        }
        else //formatting the coords
        {
            int x = -1;
            int y = -1;
            string temp;

            for (char c : word) //cycling through the 'word'
            {
                if (c == ',') //comma seperates the numbers
                {
                    x = stoi(temp);
                    temp = "";
                }
                else //else it is an incomplete number
                {
                    temp += c;
                }
            }
            y = stoi(temp); //end of the word is the end of another number

            //depending on if the first coord has been found, it assigns the coords to the correct arrays
            if (!firstOrSecond)
            {
                coord1[0] = x;
                coord1[1] = y;
                firstOrSecond = true;
            }
            else
            {
                coord2[0] = x;
                coord2[1] = y;
                firstOrSecond = false;
            }
        }
    }

    perfromAction(grid, toggleOrTurn, coord1, coord2, onOff); //making sure the last instruction is performed

    //counting!
    int onLights = 0;
    int totalBrightness = 0;

    //count all on lights and their brightness
    for (int x=0; x<=999; x++)
    {
        for (light l : grid[x])
        {
            if (l.onOrOff)
            {
                onLights++;
            }
            totalBrightness += l.brightness;
        }
    }

    //displaying my results
    cout << "Number of Lights on: " << onLights << endl;
    cout << "Total Brightness: " << totalBrightness << endl;
}