#include <iostream>
#include <fstream> //for file stuff
#include <string> //for stoi
using namespace std;

int main()
{
    string d;
    ifstream data("temp.txt"); //getting data from txt file (it's called temp cause i didn't expect to need it in the final build...)

    //totals
    int totalArea = 0;
    int totalRibbon = 0;

    //while the line is not empty
    while (data >> d) //this gets one line at a time from the file, storing it in d
    {
        //cout << d << "~" << endl;

        //setting up
        int currentDimensions[3] = {0,0,0}; //l,w,h
        int count = 0;
        string temp = "";

        //cycling through the line
        for (int i=0;i<=d.length();i++)
        {
            if (d[i] != 'x' && i < d.length()) //checking for the end and the 'x' as they seperate the numbers
            {
                temp += d[i];
                //cout << d[i] << "~" << endl;
            }
            else //found an 'x' or the end, so we have a complete number
            {
                currentDimensions[count] = stoi(temp); //converts temp to an int and stores it in currentDimensions. Index is tracked by count
                //cout << temp << endl;
                temp = "";
                count++;
            }
        }

        //calcualting side faces areas
        int lw = currentDimensions[0] * currentDimensions[1];
        int wh = currentDimensions[1] * currentDimensions[2];
        int hl = currentDimensions[2] * currentDimensions[0];
        //cout << "lw: " << lw << ", wh: " << wh << ", hl: " << hl << endl;
        totalArea += 2*lw + 2*wh + 2*hl + min(lw,min(wh,hl)); //adding to the total area

        //calculating the ribbon length. you need the two lowest numbers
        int volume = currentDimensions[0] * currentDimensions[1] * currentDimensions[2]; //(also need the volume for the bow)
        int minvals[2] = {0,0};
        //tries to get the lowest numbers
        minvals[0] = min(currentDimensions[0], currentDimensions[1]);
        minvals[1] = min(currentDimensions[1], currentDimensions[2]);

        //if they are the same, check the other two against each other. this guarantees you'll find the smallest two numbers
        if (minvals[0] == minvals[1])
        {
            minvals[1] = min(currentDimensions[2], currentDimensions[0]);
        }

        totalRibbon += 2*minvals[0] + 2*minvals[1] + volume; //adding to the total
    }

    data.close(); //close the file!!
    //print the results
    cout << "Total Area: " << totalArea << endl;
    cout << "Total Ribbon: " << totalRibbon << endl;
}