#include "arraygraph.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;


void write(string&);
void generatePermutations(int, string*, int, string*);
int factorial(int);

int main()
{
    ArrayGraph<string> graph;
    int numberOfCities = 5;
    string cities[numberOfCities];
    string city1, city2;
    float miles;


    //Load data from file
    fstream fin;
    fin.open("map.txt");
    if(fin.fail())
    {
        cout << "File not found.";
    }
    
    int index = 0;
    while(fin >> city1 >> city2 >> miles)
    {
        //Add to graph
        graph.add(city1 , city2, miles);

        //Add to cities
        bool flag = false;
        for(int i=0; i<numberOfCities; i++)
        {  
            //Check if it exists
            if(city1 == cities[i])
            {
                flag = true;
            }
        }
        if(index < numberOfCities)
        {
            if(flag == false)
            {
                cities[index] = city1;
            }
        }
        
        if(flag == false)
        {
            index++;
        }
    }
    fin.close();

    //Start city is Reno.
    int startPos;
    for(int i=0; i<numberOfCities; i++)
    {
        if(cities[i] == "Reno")
        {
            startPos = i;
        }
    }
    startPos = 0; //Change this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Find all paths
    int paths = factorial(numberOfCities-1);
    string permutations[300];
    generatePermutations(startPos, cities, numberOfCities, permutations);

    //Write paths to file.
    fstream fout;

    fout.open("paths.txt");
    if(fout.fail())
    {
        cout << "File not found.";
    }

    for(int i=0; i<paths; i++)
    {
        fout << permutations[i] << endl;
    }   
    fout.close();

    //Parse permutations array into single elements.
    /*
    int place = 0;
    int amount = paths * (numberOfCities+1); 
    string parsedPaths[144]; //Amount of singular elements in the array

    for (int i=0; i<paths; i++)
    {
        stringstream ss(permutations[i]);
        string target;

        while(getline(ss, target, ','))
        {
            parsedPaths[place] = target;
            place++;
        }
    }

    //With single elements get edgeweight and compare paths to get best one.
    
    for(int i=0; i<amount; i++)
    {
        cout << parsedPaths[i];
    }
    

    int cheapestPrice = __INT_MAX__;
    int indexCheapest = 0;
    int currentPrice = 0;
    string source, destination;
    for(int i=0; i<amount; i++)
    {
        try
        {
            if(i < amount-1)
            {
                string source = parsedPaths[i];
                string destination = parsedPaths[i+1];
                //cout << source << " ??? " << endl;
                //cout << destination << endl;
            }
            if(source != destination) //Dont compare end of last path to start of next path.
            {
                cout << "TEST" << endl;
                currentPrice += graph.getEdgeWeight(source, destination);
                cout << currentPrice << endl;
                if(currentPrice < cheapestPrice)
                {
                    cheapestPrice = currentPrice;
                    indexCheapest++;
                }
            }
        }
        catch(int edgeWeight)
        {
            cout << "NO";
        }
    }

    //Write out the best path
    fout.open("paths.txt", ios::app);
    if(fout.fail())
    {
        cout << "File not found.";
    }

    fout << "\nBest Path: " << endl;
    fout << permutations[indexCheapest] << endl;
    fout << cheapestPrice;
    */
}

void write(string& value)
{
    cout << value << endl;
}

int factorial(int numCities)
{
    if(numCities == 1)
    {
        return 1;
    }
    else
    {
        return numCities * factorial(numCities-1);
    }
}


void generatePermutations(int index, string* cities, int numCities, string* paths)
{
    //start == index
    if (index == numCities - 1) 
    {
        for(int i=0; i<numCities; i++)
        {
            paths[index * numCities + i] = cities[i];
        }
        cout << endl;
        return;
    }

    for (int i=index; i<numCities; ++i) 
    {
        string temp = cities[index];
        cities[index] = cities[i];
        cities[i] = temp;

        generatePermutations(index+1, cities, numCities, paths);

        temp = cities[index];
        cities[index] = cities[i];
        cities[i] = temp;
    }
}
/*
void generatePermutations(int start, string* cities, int numCities, string* paths, int numPaths)
{
    // Generating and writing permutations 
    sort(cities, cities + numCities);
    int index = 0;
    while (next_permutation(cities, cities + numCities))
    {
        bool flag = false;
        for (int i = 0; i <= numCities; i++) 
        {
            //Only writes to the permutations array if starts with Reno since that is a valid path.
            if(cities[0] == "Reno")
            {
                if(i != 0 && (cities[i] == "Seattle" && cities[i-1] != "LasVegas") && (cities[i] == "LasVegas" && cities[i-1] != "Seattle"))
                {
                    if((cities[i] == "SanFrancisco" && cities[i-1] != "SaltLakeCity") && (cities[i] == "SaltLakeCity" && cities[i-1] != "SanFrancisco")) 
                    {
                        flag = true;
                        paths[index] = paths[index] + cities[i];
                        if (i < numCities) 
                        {
                            paths[index] = paths[index] + " ";
                        }
                        /*
                        if(i == numCities)
                        {
                            paths[index] = paths[index] + "Reno";
                        }
                        
                    } 
                }
                
            }
        }
        if(flag)
        {
            index++;
        }
    
}
*/