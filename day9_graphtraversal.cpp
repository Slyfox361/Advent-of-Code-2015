#include <iostream>
#include <fstream>
#include <string>
#include <vector> //this is what is a list in my head. a linked list is actually the <list>. so i've tried using vectors this time :)
#include <sstream>
using namespace std;

struct location //this stores information about the places Santa needs to visit
{
    public:
        string name; //it's name
        //syncronised lists to track its neighbours and the distances to get to them
        vector<location*> neighbours;
        vector<int> distances;
        location(string n)
        {
            name = n;
        }
};

struct returnVal //this is just so my function can return two values
{
    public:
        vector<location*> sj;
        int ld;

        returnVal(vector<location*> l = {nullptr}, int i = 0)
        {
            sj = l;
            ld = i;
        }
};

location* searchList(vector<location*> locations, string s) //this is a very simple linear search algorithm so i can search my vectors
{
    //cycling through the vector
    for (auto* l : locations)
    {
        if (l->name == s) //if it finds the item, it returns it
        {
            return l;
        }
    }

    return nullptr; //otherwise it returns a nullptr
}

returnVal findRoute(location* current, int lowestDist, vector<location*> shortestJourney, int currentDist, vector<location*> tempJourney) //this is my recursive route searching algorithm (i decided to try and do it from memory instead of searching up an algorithm, so if it is innefficinet or long, that is why! but i am proud i managed to make one regardless)
{
    if (!searchList(tempJourney, current->name)) tempJourney.push_back(current); //just making sure the current node is in the list, otherwise it will skip the start/first node

    cout << "Current Node: " << current->name << endl;
    //cycling through the neighbour list
    for ( int i=0; i < current->neighbours.size(); i++)
    {
        location* l = current->neighbours[i]; //the current neighbour in focus
        
        if (!searchList(tempJourney, l->name)) //if the neighbour is not in the current route
        {
            int oldDist = currentDist; //store the old dist for backtracking
            currentDist += current->distances[i]; //add to the current dist
            tempJourney.push_back(current->neighbours[i]); //add to the current route
            
            returnVal rv = findRoute(l, lowestDist, shortestJourney, currentDist, tempJourney); //moving onto the neighbour to continue the route

            cout << "Current Node: " << current->name << endl;
            //when the findRoute returns, store the new shortest route vars
            shortestJourney = rv.sj;
            lowestDist = rv.ld;

            //backtracking
            tempJourney.pop_back();
            currentDist = oldDist;
        }
    }

    //debugging
    std::cout << "Current Route :";
    for (auto* l : tempJourney)
    {
        std::cout << l->name << ", ";
    }
    cout << endl << currentDist << endl << endl;

    //checking if the route is the shortest (and contains all the nodes)
    if (currentDist < lowestDist && tempJourney.size() == current->neighbours.size()+1) //for part 2 just revert the < sign
    {
        //updating the shortest route vars
        lowestDist = currentDist;
        shortestJourney = tempJourney;
        cout << "Shortests Found: " << lowestDist << " <--------------------------------" << endl << endl;
    }

    return returnVal(shortestJourney, lowestDist); //returning the shortest route vars
}

int main()
{
    //getting the input from a file
    fstream data("distances.txt");
    string line;

    //storing the locations
    vector<location*> destinations;

    while (getline(data, line)) //cycling through the file
    {
        //turning the line into an array to better navigate it
        stringstream ss(line);
        string sentence[5];
        string word;
        int count = 0;
        while (ss >> word)
        {
            sentence[count] = word;
            count++;
        }

        //temporary array to handle the current line (as each line contains two locations)
        location* temp[2] = {nullptr, nullptr};

        for (int i=0; i<3; i += 2)
        {
            temp[i/2] = searchList(destinations, sentence[i]); //tries to find the location
            if (temp[i/2] == nullptr) //creating the location if it does not exist
            {
                destinations.push_back(new location(sentence[i]));
                temp[i/2] = destinations.back();
            }
        }
        
        for (int i=0; i<2; i++)
        {
            if (!searchList(temp[i]->neighbours, temp[1-(i%2)]->name)) //checking if the locations have each other in their neighbour lists
            {
                //if not, add them and the distance
                temp[i]->neighbours.push_back(temp[1-(i%2)]);
                temp[i]->distances.push_back(stoi(sentence[4]));
            }
        }
    }

    //vars to feed into the findRoute
    vector<location*> l2;
    vector<location*> shortestJourney;
    returnVal rv;
    int lowestDist = INT_MAX; //set to INT_MAX for part 1 and -1 for part 2

    for (location* curr : destinations) //make sure to start at each node
    {
        rv = findRoute(curr, lowestDist, shortestJourney, 0, l2);

        //if the returned stuff is less than the current shortest route, update the vars anc continue
        if (rv.ld < lowestDist) //change this sign fom < to > for part 2
        {
            shortestJourney = rv.sj;
            lowestDist = rv.ld;
        }
    }
    
    //printing the shortest route
    std::cout << "Shortest Route :" << endl;
    for(auto* l : shortestJourney)
    {
        std::cout << "{" << l->name << "} " << endl;
    }
    //and my result
    cout << "Distance: " << lowestDist << endl;
}