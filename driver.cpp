//Author: Joel Molina
//Purpose: Solve the traveling salesman problem using the brute force method.
//Date: Fall 2023

#include "graph/arraygraph.h"
#include <iostream>
#include <fstream>
using namespace std;


void write(string&);
void generatePermutations(string, string*, int, int);
int factorial(int);

int main()
{
    //Declarations
    ArrayGraph<string> graph;
    int numberOfCities = 5;
    string cities[numberOfCities];
    string city1, city2;
    float miles;

    //Clear output file.
    fstream fout;
    fout.open("sample_data/output.txt", ios::out);
    if(fout.fail())
    {
        cout << "File not found.";
    }
    fout.close();
    
    //Load data from input file
    fstream fin;
    fin.open("sample_data/input.txt");
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

    //Generate the path permutations.
    string startCity = "Reno";
    int theIndex = 0; //Always 0 to do all permutations.

    generatePermutations(startCity, cities, numberOfCities, theIndex);

    //Add permutations' elements to array.    
    int numPaths = factorial(numberOfCities-1); //Path size
    int permElements = (numPaths * numberOfCities) + numPaths;
    string permutations[permElements]; //Elements in all paths. Need to be individual to get edgeweights.
    for(int i=0; i<numPaths; i++)
    {
        permutations[i] = "";
    }

    fin.open("sample_data/output.txt");
    int tempI = 0;
    while(fin >> city1)
    {
        permutations[tempI] = city1;
        tempI++;
    }
    fin.close();

    //Put elements into a paths array
    string paths[numPaths];
    fin.open("sample_data/output.txt");
    int tempI2 = 0;
    while(getline(fin, paths[tempI2]))
    {
        tempI2++;
    }
    fin.close();
    permutations[0] = startCity;

    //Use permutations array to get edgeweights and remove invalid paths in paths array.
    string departure, arrival;
    int edge = 0;
    int t = 0;
    for(int i=0; i<permElements; i++)
    {
        departure = permutations[i];
        arrival = permutations[i+1];
        edge = graph.getEdgeWeight(departure, arrival);

        if(edge == __INT_MAX__ && arrival != departure)
        {
            paths[t] = "invalid";    
        }
        
        if(i % 6 == 0 && i != 0)
        {
            t++;
        }
    }

    //Write valid paths to file
    fout.open("sample_data/output.txt", ios::out);
    for(int i=0; i<numPaths; i++)
    {
        if(paths[i] != "invalid")
        {
            fout << paths[i] << endl;
        }
    }
    fout.close();

    //Update paths array
    fin.open("sample_data/output.txt");
    tempI = 0;

    for(int i=0; i<numPaths; i++)
    {
        paths[i] = "invalid";
    }

    while(getline(fin, paths[tempI]))
    {
        tempI++;
    }
    fin.close();

    for(int i=0; i<numPaths; i++)
    {
        //clean up if theres any whitespace
        if(paths[i] == "")
        {
            paths[i] = "invalid";
        }
    }

    //update elements array.    
    fin.open("sample_data/output.txt");
    tempI = 0;

    for(int i=0; i<permElements; i++)
    {
        permutations[i] = "empty";
    }

    while(fin >> city1)
    {
        permutations[tempI] = city1;
        tempI++;
    }
    fin.close();

    //Find the best path with updated array.
    float cheapest = __INT_MAX__;
    int cost = 0;
    edge = 0;
    t = 0;
    int resultT;
    for(int i=0; i<tempI-1; i++)
    {
        //So that edges of empty spaces arent checked.
        departure = permutations[i];
        arrival = permutations[i+1];
        edge = graph.getEdgeWeight(departure, arrival);

        if(arrival != departure)
        {
            cost += edge;
        }

        if((i + 1) % 6 == 0 && i != 0)
        {
            if(cost < cheapest)
            {
                cheapest = cost;
                cost = 0;
                resultT = t;
            }
        }

        if((i+1) % 6 == 0 && i != 0)
        {
            t++;
        }   
        
    }
    //Write out the best path
    
    fout.open("sample_data/output.txt", ios::app);

    fout << "\nBest Path: " << paths[resultT] << endl;
    fout << "Cost: " << cheapest/40;
    fout.close();
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

void generatePermutations(string start, string* cities, int numCities, int index)
{
    //Base case
    if (index == numCities - 1) 
    {
        //Starting city could be anything so based on input. Here, want to start in Reno.
        if(cities[0] == start)
        {
            fstream fout;
            fout.open("sample_data/output.txt", ios::app);

            for(int i=0; i<numCities; i++)
            {
                
                fout << cities[i] + " ";
            }
            fout << start << endl; //Appends start city to end of each path.
            fout.close();
        }
        return;
    }
    else
    {
        for (int i=index; i<numCities; i++) 
        {
            //Swap with all elements
            string temp = cities[index];
            cities[index] = cities[i];
            cities[i] = temp;

            ///Get permutations after the current affixed value
            generatePermutations(start, cities, numCities, index+1);
            
            //Backtrack
            temp = cities[index];
            cities[index] = cities[i];
            cities[i] = temp;
        }
    }   
}
