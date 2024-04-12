/*
 * DatumStack.cpp
 *
 * Comp 15 
 *
 * Created by:
 *        Walter Wagude - October 2021
 *
 * Notes: Implementation of the DatumStack class interface.
 *        Uses vector to implement a DatumStack.
 *        Implements functions such as pop and top.
 *
 */


#include "DatumStack.h"
#include "Datum.h"
#include <vector>
#include <string>

using namespace std;

/*
* DatumStack constructor 1
* Parameters: None
* return: None
* purpose: A default constructor - takes no parameters and
*        initializes empty stack
*/
DatumStack::DatumStack(){
    count = 0;
}

/*
* DatumStack constructor 2
* Parameters: an array of Datum and an integer
*             specifying the size of the array
* return: None
* purpose: A constructor which takes an array of Datum and an integer
*          specifying the size of the array as parameters and creates a stack
*          initialized so that the elements of the array are on the stack with
*          the array’s element 0 pushed on first and it’s (size - 1)th element
*          at the top of the stack
*/
DatumStack::DatumStack(Datum *data, int size){
    count = size;
    for (int i = 0; i < size; i++){
        Datum_Stack.push_back(data[i]);
    }
    
}

/*
* isEmpty
* Parameters: None
* return:  a boolean value
* purpose: takes no parameters and returns a boolean
*          value that is true if this specific instance of the DatumStack
*          class is empty and false otherwise.
*/
bool DatumStack::isEmpty(){
    return (count == 0);
}

/*
* clear
* Parameters: None
* return: None
* purpose: takes no parameters and has a void return type.
*          It makes the current stack into an empty stack.
*/
void DatumStack::clear(){
    Datum_Stack.clear();
    count = 0;
}

/*
* size
* Parameters: None
* return: returns an integer value
* purpose: takes no parameters and returns an integer value
*          that is the number of Datum elements on the stack.
*/
int DatumStack::size(){
    return Datum_Stack.size();
}

/*
* top
* Parameters: None
* return: returns the top Datum
*         element on the stack.
* purpose: takes no parameters and returns the top Datum
*          element on the stack.
*/
Datum DatumStack::top(){
    if (count == 0){
        throw runtime_error("empty_stack");
    }else{
        return Datum_Stack.back();
    }
    
}

/*
* pop
* Parameters: None
* return: None
* purpose: takes no parameters and has a void return type.
*          It removes the top element on the stack
*/
void DatumStack::pop(){
    if (count == 0){
        throw runtime_error("empty_stack");
    }else{
        Datum_Stack.pop_back();
        count--;
    }
}

/*
* push
* Parameters: Datum element to be added to the stack
* return: None
* purpose: takes a Datum element and puts it on the top of
*          the stack.
*/
void DatumStack::push(Datum element){
    Datum_Stack.push_back(element);
    count++;
        
}
