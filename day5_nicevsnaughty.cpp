#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

int part1(string line) //part 1 of the challenge
{
    //used for checks
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    string dissallowed[4] = {"ab", "cd", "pq", "xy"};

    int passed = 0; //used to count the passed conditions
    int numvowels = 0; //counrs the vowels
    char previousChar = '0'; //stores the previous character
    bool doubleChar = false; //makes sure the double character check is only counted once

    for (char d : line) //cycling through the string
    {
        //checking for vowels
        for (char v : vowels)
        {
            if (d == v)
            {
                numvowels++;
            }
        }

        //checking for doubles
        if (previousChar == d && doubleChar == false)
        {
            passed++;
            doubleChar = true;
        }

        string adjacentChars = string() + previousChar + d; //combining the characters to check for the disallowed combos
        
        for (string disa : dissallowed)
        {
            if (disa == adjacentChars)
            {
                passed = -100; //it is always a fail if they are present
                cout << "Passed: " << to_string(passed) << endl;
                cout << "Vowels: " << to_string(numvowels) << endl;
            }
        }

        previousChar = d; // setting up the next loop
    }

    //checking for the righ number of vowels
    if (numvowels >= 3)
    {
        passed++;
    }

    cout << "Passed: " << to_string(passed) << endl;
    cout << "Vowels: " << to_string(numvowels) << endl;
    return passed;
}

int part2(string line) //for part 2 of the challenge
{
    int passed = 0; //this is more to match the output of part 1
    bool repeatingPairsPassed = false; //ensuring i only count the repeating pairs once
    bool sandwichPassed = false; //ensuring i only count the sandwich (e.g. xyx or aaa) once
    //previous characters
    char previousChar = '0';
    char previousPreviousChar = '7';
    list<string> pairs; //storing the paired characters

    for (char d : line) //cycling through the string
    {
        if (previousChar != '0') //making sure it doesnt count the first 'pair'
        {
            string joined = string() + previousChar + d;

            if (pairs.size() > 0) //making sure the list isn't empty
            {
                list<string>::iterator it = pairs.begin(); //cycling through the list
                int count = 0; //to check indexes

                while (it != pairs.end() && count != pairs.size()-1) // while we are not at the end and it doesn't check the very last element (to avoid aaa counting as a repeating pair)
                {
                    if (joined == *it) //if there is a match, the pair repeats
                    {
                        repeatingPairsPassed = true;
                        cout << "Repeating Pair: " << joined << endl;
                        break;
                    }
                    advance(it, 1);
                    count++;
                }
            }
            pairs.push_back(joined);
            
        }

        if (previousPreviousChar == d) //checking for a sandwich
        {
            cout << "Sandwich: " << previousPreviousChar << previousChar << d << endl;
            sandwichPassed = true;
        }

        //setting up the next loop
        previousPreviousChar = previousChar;
        previousChar = d;
    }

    //debugging (printing the pairs list)
    cout << "Pairs: {";
    list<string>::iterator it = pairs.begin();
    while (it != pairs.end())
    {
        cout << "{" << *it << "} ";
        advance(it,1);
    }
    cout << " }" << endl;

    //tailoring the output to part 1
    if (sandwichPassed)
    {
        passed++;
    }
    else
    {
        passed = -100;
    }
    if (repeatingPairsPassed)
    {
        passed++;
    }
    else
    {
        passed = -100;
    }

    return passed;
}

int main()
{
    string d;
    ifstream data("listofstrings.txt"); //getting data from txt file

    int niceStrings = 0;

    while (data >> d)
    {
        //modularised since they were both so different
        //int passed = part1(d);
        int passed = part2(d);
        
        //checking if all the conditions were passed
        if (passed >= 2)
        {
            niceStrings++; //counting the nice strings
            cout << d << " is nice!" << endl;
            
        }
        else
        {
            cout << d << " is naughty" << endl;
        }
    }

    data.close(); //close the file!!

    cout << "There are " << niceStrings << " nice strings :)" << endl;
}

