/*
 * DatumStack.h
 *
 * Comp 15
 * October 2021
 *
 * Created by: Walter Wagude, October 2021
 *
 * Notes: Interface of DatumStack - has functions such as pop, that removes
 *        an element from the top of the stack, top function that returns the 
 *        element at the top of the stack without removing it etc...
 *
 *
 * Implemented using a vector.
 */
 
#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_

#include "Datum.h"
#include <iostream>
#include <vector>
#include <string>

class DatumStack
{
public:
    // A default constructor - takes no parameters and initializes empty stack
    DatumStack();
    // A constructor which takes an array of Datum and an integer
    DatumStack(Datum *data, int size);
    // checks whether the stack is empty or not
    bool isEmpty();
    // makes the current stack into an empty stack.
    void clear();
    // returns the size of the stack
    int size();
    // returns element at the top of the stack
    Datum top();
    // Removes the top element on the stack
    void pop();
    // takes a Datum element and puts it on the top of
    // the stack.
    void push(Datum element);
    
private:
    // create an instance of a vector of type Datum
    std::vector <Datum> Datum_Stack;
    int count;
         
};

#endif
