#include "arraygraph.h"
#include <iostream>

void write(string&);

int main()
{
    ArrayGraph<string> graph;
    /*
    string test1 = "Reno";
    string test2 = "SF";
    string test3 = "LV";

    cout << graph.add(test1, test2, 5);
    cout << graph.add(test1, test3, 6);
    cout << endl;
    cout << graph.getEdgeWeight(test1, test2);
    cout << endl;
    cout << graph.getEdgeWeight(test1, test3);
    */
    string A = "A";
    string B = "B";
    string C = "C";
    string D = "D";
    string E = "E";
    string F = "F";
    string G = "G";
    string H = "H";
    graph.add(A, B, 1);
    graph.add(A, C, 2);
    graph.add(B, D, 3);
    graph.add(B, E, 4);
    graph.add(E, F, 5);
    graph.add(E, H, 6);
    graph.add(F, C, 7);
    graph.add(F, G, 8);
    graph.add(G, C, 9);


    //graph.depthFirstTraversal(A, write);
    graph.breadthFirstTraversal(A, write);


    return 0;
}

void write(string& value)
{
    cout << value << endl;
}