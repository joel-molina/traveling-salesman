/*
Author: Joel Molina 
Purpose: Implement the array Graph class.
Date: 12/3/2023
*/

#include "arraygraph.h"

template <typename T>
ArrayGraph<T>::ArrayGraph()
{
    numVertices = 0;
    numEdges = 0;

    for(int i=0; i<MAX_CAPACITY; i++)
    {
        vertexIndices[i] = -1;
    }

    for(int i=0; i<MAX_CAPACITY; i++)
    {
        for(int j=0; j<MAX_CAPACITY; j++)
        {
            arr[i][j] = __INT_MAX__; //"infinity" is a default value in the matrix.
        }
    }
}

template <typename T>
int ArrayGraph<T>::getNumVertices() const
{
    return numVertices;
}

template <typename T>
int ArrayGraph<T>::getNumEdges() const
{
    return numEdges;
}

template <typename T>
bool ArrayGraph<T>::add(T start, T end, int edgeWeight)
{
    bool startFlag = false;
    bool endFlag = false;
    int vertex1, vertex2;

    bool canAddVertex;
    if(numVertices < MAX_CAPACITY)
    {
        canAddVertex = true; 
    }
    else
    {
        return false;
    }

    //Check if the vertex already exists
    for(int i=0; i<MAX_CAPACITY; i++)
    {
        if(vertexIndices[i] == start)
        {
            startFlag = true;
            vertex1 = i;
        }
        if(vertexIndices[i] == end)
        {
            endFlag = true;
            vertex2 = i;
        }
    }

    //A vertex is "Added" by keeping track of their indices and increasing numVertices.
    if(canAddVertex)
    {
        if(startFlag == false)
        {
            vertex1 = numVertices;
            vertexIndices[vertex1] = start;
            numVertices++;
        }
        if(endFlag == false)
        {
            vertex2 = numVertices;
            vertexIndices[vertex2] = end;
            numVertices++;
        }
    }
    
    //Add the edge
    arr[vertex1][vertex2] = edgeWeight;
    arr[vertex2][vertex1] = edgeWeight;
    numEdges++;

    return canAddVertex;
}

template <typename T>
bool ArrayGraph<T>::remove(T start, T end)
{
    bool canRemove;
    bool startFlag = false;
    bool endFlag = false;

    //Get vertex indices
    int a,b;
    for(int i=0; i<MAX_CAPACITY; i++)
    {
        if(vertexIndices[i] == start)
        {
            a = i;
        }
        if(vertexIndices[i] == end)
        {
            b = i;
        }
    }

    //Remove the edges
    if(arr[a][b] == __INT_MAX__) 
    {
        canRemove = false; //Nothing to remove, there is no edge there.
        return canRemove;
    }
    else
    {
        arr[a][b] = __INT_MAX__;
        arr[b][a] = __INT_MAX__;
        numEdges--;
    }

    //If vertex has no more edges, remove vertex.
    for(int i=0; i<MAX_CAPACITY; i++)
    {
        if(arr[a][i] != __INT_MAX__)
        {
            startFlag = true;
        }
        if(arr[b][i] != __INT_MAX__)
        {
            endFlag = true;
        }
    }

    if(startFlag == false)
    {
        removeVertex(start);
    }
    if(endFlag == false)
    {
        removeVertex(end);
    }

    return canRemove;
}

template <typename T>
void ArrayGraph<T>::removeVertex(T vertex)
{
    //Get vertex index
    int a;
    for(int i=0; i<MAX_CAPACITY; i++)
    {
        if(vertexIndices[i] == vertex)
        {
            a = i;
        }
    }

    //Move everything after the index left.
    for(int i=0; i<MAX_CAPACITY; i++)
    {
        for (int j=a; j<MAX_CAPACITY; j++)
        {
            arr[i][j] = arr[i][j+1];
        }
    }

    
    //Move everything after the index up.
    for(int i=a; i<MAX_CAPACITY; i++)
    {
        for (int j=0; j<MAX_CAPACITY; j++)
        {
            arr[i][j] = arr[i+1][j];
        }
    }

    numVertices--;
}

template <typename T>
int ArrayGraph<T>::getEdgeWeight(T start, T end) const
{
    int a,b;
    for(int i=0; i<MAX_CAPACITY; i++)
    {
        if(vertexIndices[i] == start)
        {
            a = i;
        }
        if(vertexIndices[i] == end)
        {
            b = i;
        }
    }
    
    if(arr[a][b] != __INT_MAX__)
    {
        return arr[a][b];
    }
    else
    {
        return __INT_MAX__;
        //throw "There is no edge.";
        //cout << "There is no edge." << endl;
        //return -1;
    }


}

template <typename T>
void ArrayGraph<T>::depthFirstTraversal(T start, void visit(T&))
{
    ArrayStack<T> stack;
    bool seen[numVertices];

    //Initialize seen array
    for(int i=0; i<numVertices; i++)
    {
        seen[i] = 0;
    }

    //Get index of start node.
    int a;
    for(int i=0; i<numVertices; i++)
    {
        if(vertexIndices[i] == start)
        {
            a = i;  
        }
    }
    
    //First vertex
    stack.push(vertexIndices[a]);
    visit(vertexIndices[a]);
    seen[a] = 1;

    //Rest of the vertices.
    while(!stack.isEmpty())
    {
        bool flag = false;
        //Get  current vertex
        T topVertex = stack.peek();
        for(int i=0; i<numVertices; i++)
        {
            if(vertexIndices[i] == topVertex)
            {
                a = i;
            }
        }

        //Check adjacent vertices
        for(int i=0; i<MAX_CAPACITY; i++)
        {
            if(arr[a][i] != __INT_MAX__ && seen[i] == 0) //First check finds index of edge. Then checks if it has been seen.
            {
                stack.push(vertexIndices[i]);
                visit(vertexIndices[i]);
                seen[i] = 1;
                flag = true;
                break; //One adjacent vertex at a time.
            }
        }

        //Pop if dead end (no more adjacent vertices not seen).
        if(!flag)
        {
            stack.pop();
        }
    }
}

template <typename T>
void ArrayGraph<T>::breadthFirstTraversal(T start, void visit(T&))
{
    //visit(start);
    ArrayQueue<T> queue;
    bool seen[numVertices];

    //Initialize seen array
    for(int i=0; i<numVertices; i++)
    {
        seen[i] = 0;
    }

    //Get index of start node.
    int a;
    for(int i=0; i<numVertices; i++)
    {
        if(vertexIndices[i] == start)
        {
            a = i;  
        }
    }
    
    //First vertex
    queue.enqueue(vertexIndices[a]);
    visit(vertexIndices[a]);
    seen[a] = 1;

    //Rest of the vertices.
    while(!queue.isEmpty())
    {
        bool flag = false;
        //Get  current vertex
        T topVertex = queue.peekFront();
        for(int i=0; i<numVertices; i++)
        {
            if(vertexIndices[i] == topVertex)
            {
                a = i;
            }
        }
        queue.dequeue(); //Different than DFS and dequeues current vertex and puts adjacent vertices in queue.
        //Check adjacent vertices
        for(int i=0; i<MAX_CAPACITY; i++)
        {
            if(arr[a][i] != __INT_MAX__ && seen[i] == 0) 
            {
                visit(vertexIndices[i]);
                seen[i] = 1;
                flag = true;
                queue.enqueue(vertexIndices[i]);
                //Unlike DFS, no break so it can get both adjacent vertices immediately.
            }
        }
    }
}
