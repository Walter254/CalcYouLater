/*
 * main.cpp
 *
 * Comp 15 
 *
 * Created by:
 *        Walter Wagude - October 2021
 *
 * Notes: Creates an instance of RPNCalc called Calculator then calls run
 *        function. Run is a member function of RPNCalc that calls a command
 *        loop which takes inputs and executes a Reverse Polish Notation
 *        calculator. The calculator supports datum objects.
 *
 */
 

#include <iostream>
#include <fstream>
#include <string>

#include "DatumStack.h"
#include "RPNCalc.h"
#include "Datum.h"

using namespace std;

int main()
{
    // create an instance of RPNCalc
    RPNCalc Calculator;
    // call run function
    Calculator.run();
    
    return 0;
}
