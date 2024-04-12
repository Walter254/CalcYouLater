/* 
 * unit_tests.h
 * 
 * CS 15 proj1
 * by Walter, October 2021
 * 
 * Tests the DatumStack class
 */

#include <cassert>
#include "DatumStack.h"
#include "RPNCalc.h"
#include "Datum.h"
#include <vector>
#include <fstream>

/********************************************************************\
*                      DatumStack tests                    *
\********************************************************************/

/* default constructor test
 * Run the DatumStack default constructor to make sure there are no runtime
 * errors or memory leaks
 */
void Test_DatumStack_constructor1_Function()
{
    //initialize an empty stack
    DatumStack testDatumStack;

}

/* constructor2 test
 * Test if the constructor creates a stack 
 */
void Test_DatumStack_constructor2_Function()
{
    Datum Test[2] = { Datum (5), Datum (true) };
    DatumStack testDatumStack(Test, 2);
    
    std::cout << "The top is " << testDatumStack.top().getBool() << std::endl;

}

/* 
 * isEmpty test
 * check if the stack is empty
 */
void Test_DatumStack_isEmpty_Function()
{
    Datum Test[2] = { Datum (5), Datum (true) };
    DatumStack testDatumStack(Test, 2);
    
    testDatumStack.clear();
    
    assert(testDatumStack.isEmpty() == true);

}

/* 
 * clear 
 * call clear function then check if the stack is empty
 */
void Test_DatumStack_clear_Function()
{
    Datum Test[2] = { Datum (5), Datum (true) };
    DatumStack testDatumStack(Test, 2);
    
    testDatumStack.clear();
    
    assert(testDatumStack.isEmpty() == true);

}

/* 
 * size
 * initialize Datumstack with two elements then check if the size is two
 */
void Test_DatumStack_size_Function()
{
    Datum Test[2] = { Datum (5), Datum (true) };
    DatumStack testDatumStack(Test, 2);
    
    assert(testDatumStack.size() == 2);

}

/* 
 * top
 * check if the top element is the one added to the stack last
 */
void Test_DatumStack_top_Function()
{
    Datum Test[2] = { Datum (true), Datum (5) };
    DatumStack testDatumStack(Test, 2);
    
    std::cout << "The top should be 5 = " << testDatumStack.top().getInt()
              << std::endl;

}

/* 
 * pop
 * call pop function then check if the top element is the previous second last
 * element on the stack 
 */
void Test_DatumStack_pop_Function()
{
    // DatumStack testDatumStack_empty;
    // testDatumStack_empty.pop(); // should throw runtime_error
    // tested it and it throws a runtime_error
    
    Datum Test[3] = { Datum (true), Datum (7), Datum (6) };
    DatumStack testDatumStack(Test, 3);
    testDatumStack.pop();
    
    std::cout << "The top should be 7 = " << testDatumStack.top().getInt()
              << std::endl;

}

/* 
 * push
 * add an element to the stack using push function then check if it is the top
 * element
 */
void Test_DatumStack_push_Function()
{
    
    Datum Test[3] = { Datum (true), Datum (7), Datum (6) };
    DatumStack testDatumStack(Test, 3);
    
    Datum test(false);
    
    testDatumStack.push(test);
    
    std::cout << "The top should be 0 = " << testDatumStack.top().getBool()
              << std::endl;

}
