/*
 * RPNCalc.h
 *
 * Comp 15
 * October 2021
 *
 * Created by: Walter Wagude, October 2021
 *
 * Notes: The interface of a Reverse Polish Notation Calculator(RPNCalc) -
 *        Uses postfix notation, operator comes after its operands and not in 
 *        between. The RPNCalc will support Datum Objects
 */
 
#ifndef _RPNCALC_H_
#define _RPNCALC_H_

#include <iostream>
#include <vector>
#include <string>
#include "DatumStack.h"
#include "Datum.h"


class RPNCalc
{
public:
    //default constructor
    RPNCalc();
    //destructor
    ~RPNCalc();
    //reads commands from std::cin
    void run();

private:
    //DatumStack of RPNCalc
    DatumStack RPN_Calc;
    
    void command_loop(std::istream &input);
    //check if the string is an int
    bool got_int(std::string s, int *resultp);
    //helper function for prrint commnad
    void print();
    //helper function for not command
    void Not();
    //helper function for swap command
    void Swap();
    //helper function for +, -, *, /, and mod commands
    void calculate(std::string cmd);
    //helper function for the comparison commands apart from ==
    void compare(std::string cmd);
    //helper function for the == command
    void comp_eq();
    //helper function for the drop command
    void drop();
    //helper function for the dup command
    void dup();
    //helper function for the exec command
    void exec();
    //helper function for the file command
    void file();
    //helper function for the if_cmd command
    void if_cmd();
    
    std::string remove_braces(std::string rstring);
    std::string parseRString(std::istream &input);
};

#endif

