/*
Author: Joel Molina 
Purpose: Templated interface for a stack.
Date: 12/3/2023
*/

#ifndef STACK_INTERFACE 
#define STACK_INTERFACE 

template<class ItemType> 
class StackInterface 
{ 
    public: 
        virtual bool isEmpty() const = 0; 
        virtual bool push(const ItemType& newEntry) = 0; 
        virtual bool pop() = 0; 
        virtual ItemType peek() const = 0; 
        virtual ~StackInterface() {};
};  
#endif
