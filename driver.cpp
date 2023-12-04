#include "arraygraph.h"
#include <iostream>
#include <fstream>
using namespace std;


void write(string&);
void generatePermutations(string, string*, int, int);
int factorial(int);

int main()
{
    ArrayGraph<string> graph;
    int numberOfCities = 5;
    string cities[numberOfCities];
    string city1, city2;
    float miles;

    //Clear paths file.
    fstream fout;
    fout.open("paths.txt", ios::out);
    if(fout.fail())
    {
        cout << "File not found.";
    }
    fout.close();
    
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

    fin.open("paths.txt");
    int tempI = 0;
    while(fin >> city1)
    {
        permutations[tempI] = city1;
        tempI++;
    }
    fin.close();

    //Put elements into a paths array
    string paths[numPaths];
    fin.open("paths.txt");
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
    fout.open("paths.txt", ios::out);
    for(int i=0; i<numPaths; i++)
    {
        if(paths[i] != "invalid")
        {
            fout << paths[i] << endl;
        }
    }
    fout.close();

    //Find the best path

    //Write out the best path
    /*
    fout.open("paths.txt", ios::app);
    if(fout.fail())
    {
        cout << "File not found.";
    }

    fout << "\nBest Path: " << endl;
    fout << "path";
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

void generatePermutations(string start, string* cities, int numCities, int index)
{
    //Base case
    if (index == numCities - 1) 
    {
        //Starting city could be anything so based on input. Here, want to start in Reno.
        if(cities[0] == start)
        {
            fstream fout;
            fout.open("paths.txt", ios::app);

            for(int i=0; i<numCities; i++)
            {
                
                fout << cities[i] + " ";
            }
            fout << "Reno" << endl;
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
