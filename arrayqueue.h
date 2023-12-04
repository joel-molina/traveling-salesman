/*
Author: Joel Molina 
Purpose: Define the attributes and behaviors of the arrayqueue class.
Date: 12/3/2023
*/

#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

//Necessary here.
#include <iostream> 
using namespace std; 

#include "queue.h"

template <class T>
class ArrayQueue : public QueueInterface<T>
{
    protected:
        static const int MAX_SIZE = 100;
        int itemCount;
        int front;
        int back;
        T* queue = new T[MAX_SIZE];

    public:
        ArrayQueue();
        ArrayQueue(int, int, int, T[]);
        ArrayQueue(const ArrayQueue<T>&);
        ~ArrayQueue();

        bool isEmpty() const;
        bool enqueue(const T& newEntry); 
        bool dequeue(); 
        T peekFront() const; 
};
#include "arrayQueue.cpp"
#endif