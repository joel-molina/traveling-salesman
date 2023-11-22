#ifndef ARRAYGRAPH_H
#define ARRAYGRAPH_H

#include "graph.h" 
#include "arraystack.h"
#include "arrayqueue.h"
#include <iostream>

using namespace std;

template <class T>
class ArrayGraph : public GraphInterface<T>
{
    static const int MAX_CAPACITY = 100;
    int arr[MAX_CAPACITY][MAX_CAPACITY];
    T vertexIndices[MAX_CAPACITY];
    int numVertices;
    int numEdges;

    void removeVertex(T);

    public:
        ArrayGraph();

        int getNumVertices() const;
        int getNumEdges() const;
        bool add(T start, T end, int edgeWeight);
        bool remove(T start, T end);
        int getEdgeWeight(T start, T end) const;
        void depthFirstTraversal(T start, void visit(T&));
        void breadthFirstTraversal(T start, void visit(T&));
};
#include "arraygraph.cpp"
#endif