/*
Author: Joel Molina 
Purpose: Implementation of the arrayqueue class.
Date: 12/3/2023
*/

#include "arrayqueue.h"

template <typename T>
ArrayQueue<T>::ArrayQueue()
{
    itemCount = 0;
    front = 0;
    back = -1;
    queue = new T[MAX_SIZE];
}

template <typename T>
ArrayQueue<T>::ArrayQueue(int i, int f, int b, T other[])
{
    itemCount = i;
    front = f;
    back = b;

    queue = new T[itemCount];

    for(int i=0; i<itemCount; i++)
    {
        queue[i] = other[i];
    }
}

template <typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& rhs)
{
    itemCount = rhs.itemCount;
    front = rhs.itemCount;
    back = rhs.itemCount;

    queue = new T[itemCount];

    for(int i=0; i<itemCount; i++)
    {
        T newObject = new T;
        newObject = rhs.queue[i];
        queue[i] = newObject;
    }
}

template <typename T>
ArrayQueue<T>::~ArrayQueue()
{
    delete [] queue;
}

template <typename T>
bool ArrayQueue<T>::isEmpty() const
{
    return itemCount == 0;
}

template <typename T>
bool ArrayQueue<T>::enqueue(const T& newEntry)
{
    bool canEnqueue = itemCount != MAX_SIZE;
   
    if(canEnqueue)
    {
        if(itemCount == 0)
        {
            back = front;
            queue[back] = newEntry;
            itemCount++;
        }
        else
        {
            back++;
            back = back % MAX_SIZE;
            queue[back] = newEntry;
            itemCount++;
        }
     
    }
    else
    {
        cout << "Line is full." << endl;
    }

    return canEnqueue;
}

template <typename T>
bool ArrayQueue<T>::dequeue()
{
    bool canDequeue = !isEmpty();

   if(canDequeue)
   {
        front++;
        itemCount--;
        front = front % MAX_SIZE;
   }
   else
   {
        cout << "Line is already empty." << endl;
   }

    return canDequeue;
}

template <typename T>
T ArrayQueue<T>::peekFront() const
{
    if(!isEmpty())
    {
        return queue[front];
    }
    else
    {
        cout << "I am empty." << endl;
    }
    return queue[0];
}