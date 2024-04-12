/*
 * RPNCalc.cpp
 *
 * Comp 15 
 *
 * Created by:
 *        Walter Wagude - October 2021
 *
 * Notes: Implementation of the RPNCalc interface. Implements RPNCalc member
 *        functions such as run that calls the command_loop function. All of
 *        functions work together to implement a Reverse Polish Notation
 *        calculator-  postfix notation. The program requires input from either
 *        cin or a file to execute.
 * Known Bugs: During testing, the program's fails to execute file command on 
 *             nested rstrings. Tried different Implementations to the point 
 *             of frustration but did not find a solution. 
 * Key notes:  whenever the operators are encountered as a command, the program 
 *             pops the two top elements whether the operation can be performed
 *             on them or not.
 *
 */

#include "RPNCalc.h"
#include "DatumStack.h"
#include "Datum.h"
#include "DatumStack.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

/*
* RPNCalc
* Parameters: none
* return: none
* purpose: a default constructor
*/
RPNCalc::RPNCalc(){
    
}

/*
* ~RPNCalc
* Parameters: none
* return: none 
* purpose: clears the stack - destroys any heap allocated data.
*/
RPNCalc::~RPNCalc(){
    RPN_Calc.clear();
}

/*
* command_loop
* Parameters: a reference to an istream - can be cin or a fstream.
* return: void
* purpose: Takes commands from either a file or cin then executes a RPN
*          Calculator in accordance with the read inputs.
*/
void RPNCalc::command_loop(std::istream &input){

    std::string cmd;
    // read inputs from cin or a file then call respective functions or execute
    // appropriately
    while (input >> cmd){ 
        int resultp;
        if (got_int(cmd, &resultp)){ // check if the input is a number
            Datum temp(resultp); // create a datum 
            RPN_Calc.push(temp); // push the created datum to the stack 
        } else if (cmd == "#t"){
            Datum temp(true);
            RPN_Calc.push(temp);    
        } else if (cmd == "#f"){
            Datum temp(false);
            RPN_Calc.push(temp);     
        } else if (cmd == "not"){
            Not();
        } else if (cmd == "print"){
            print();
        } else if (cmd == "clear"){
            RPN_Calc.clear();
        } else if (cmd == "drop"){
            drop();
        } else if (cmd == "dup"){
            dup();
        } else if (cmd == "swap"){
            Swap();
        } else if (cmd == "+"){
            calculate(cmd);    
        } else if (cmd == "-"){
            calculate(cmd);
        } else if (cmd == "*"){
            calculate(cmd);
        } else if (cmd == "/"){
            calculate(cmd);
        } else if (cmd == "mod"){
            calculate(cmd);
        } else if (cmd == "<"){
            compare(cmd);
        } else if (cmd == ">"){
            compare(cmd);
        } else if (cmd == "<="){
            compare(cmd);
        } else if (cmd == ">="){
            compare(cmd);
        } else if (cmd == "=="){
            comp_eq();
        } else if (cmd == "exec"){
            exec();
        } else if (cmd == "{"){    
            RPN_Calc.push(Datum (parseRString(std::cin)));
        } else if (cmd == "file"){
            file();    
        } else if (cmd == "if"){
            if_cmd();
        } else if (cmd == "quit"){
            std::cerr << "Thank you for using CalcYouLater." << std::endl;
            return; // terminate the command_loop
        } else {
            std::cerr << cmd << ": unimplemented" << std::endl;
        }
    }
    
}

/*
* run
* Parameters: none
* return: void
* purpose: calls the command_loop which reads inputs from std::cin 
*/
void RPNCalc::run(){
    command_loop(std::cin);
}

/*
* got_int
* Parameters: a string and an integer pointer
* return: a boolean - true if the string is a number, false otherwise
* purpose: checks whether a string is a number.
* Notes: this function is borrowed from the got_int.cpp file
*/
bool RPNCalc::got_int(std::string s, int *resultp)
{
    // Holds the first non-whitespace character after the integer */
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
* print
* Parameters: none
* return: void
* purpose: prints the value on the top of the stack without popping it
*/
void RPNCalc::print(){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    // print if top element is an integer
    if (RPN_Calc.top().isInt()){
        std::cout << RPN_Calc.top().getInt() << std::endl;
        // print if top element is a boolean
    } else if (RPN_Calc.top().isBool()){
        if (RPN_Calc.top().getBool() == 0){
            std::cout << "#f" << std::endl;
            
        } else {
            std::cout << "#t" << std::endl;
            
        }
        // print if top element is an rstring
    } else if (RPN_Calc.top().isRString()){
        std::cout << RPN_Calc.top().getRString() << std::endl;
    }
}

/*
* Not
* Parameters: none
* return: void
* purpose: called whenever the not command is encountered, it reads and pops the
*          top element off the stack, a boolean and pushes a datum with the 
*          opposite value on the stack
*/
void RPNCalc::Not(){
    try {
        RPN_Calc.top();//check if the stack is empty
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    try {
        RPN_Calc.top().getBool();//check if the top element is a boolean
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: datum_not_bool" << std::endl;
        return;
    }
    
    bool Top;
    //get the top element on the stack - should be a boolean
    Top = RPN_Calc.top().getBool();
    RPN_Calc.pop(); //remove the top element
    
    if (Top == 1){
        Datum temp(false);
        RPN_Calc.push(temp);
        
    }else if (Top == 0){
        Datum temp(true);
        RPN_Calc.push(temp);
    }   
}

/*
* Swap
* Parameters: none
* return: void
* purpose: Swaps the top two elements on the stack
*/
void RPNCalc::Swap(){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    
    //store the top element then pop it
    Datum curr = RPN_Calc.top();
    RPN_Calc.pop();
    //store the top element then pop
    Datum temp = RPN_Calc.top();
    RPN_Calc.pop();
    //swap the two elements
    RPN_Calc.push(curr);
    RPN_Calc.push(temp);
    
}

/*
* calculte
* Parameters: takes a command of type string
* return: void
* purpose: whenever an operator is encountered as a command, this function
*          is called. the top two elements are popped off the stack, the
*          operation performed on them and the datum with the result is pushed 
*          on the top of the stack.
* Note: first operand of the operation is the deeper item on the stack.
*       this function applies to operators that logically calculates the two
*       elements and give a integer result
*/
void RPNCalc::calculate(std::string cmd){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    try {
        RPN_Calc.top().getInt();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: datum_not_int" << std::endl;
        RPN_Calc.pop();
        RPN_Calc.pop();
        return;
    }

    
    int result;
    
    // store the top integer then pop it
    int f_num = RPN_Calc.top().getInt();
    RPN_Calc.pop();
    
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    
    try {
        RPN_Calc.top().getInt();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: datum_not_int" << std::endl;
        RPN_Calc.pop();
        return;
    }
    
    
    // store the top integer then pop it
    int s_num = RPN_Calc.top().getInt();
    RPN_Calc.pop();
    
    // perform the appropriate operation on the two integers
    if (cmd == "+"){
        result = s_num + f_num;
    } else if (cmd == "-"){
        result = s_num - f_num;
    } else if (cmd == "*"){
        result = s_num * f_num;
    } else if (cmd == "/"){
        result = s_num / f_num;
    } else {
        result = s_num % f_num;
    }
    
    // create a Datum with the result
    Datum sum(result);
    // push the datum on the stack
    RPN_Calc.push(sum);
}

/*
* compare
* Parameters: command of type string
* return: void
* purpose: whenever an operator is encountered as a command, this function
*          is called. the top two elements are popped off the stack, the
*          operation performed on them and the datum with the result is pushed 
*          on the top of the stack.
* Notes: this function applies to operators that compare elements apart from ==
*        the result from the operation is of type boolean
*/
void RPNCalc::compare(std::string cmd){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    try {
        RPN_Calc.top().getInt();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: datum_not_int" << std::endl;
        RPN_Calc.pop();
        RPN_Calc.pop();
        return;
    }
    
    bool result = false;
    
    if (RPN_Calc.top().isInt()){
        int f_num = RPN_Calc.top().getInt();
        RPN_Calc.pop();
        
        try {
            RPN_Calc.top().getInt();
        }
        catch(std::runtime_error &e){
            std::cerr << "Error: datum_not_int" << std::endl;
            RPN_Calc.pop();
            return;
        }
        
        int s_num = RPN_Calc.top().getInt();
        RPN_Calc.pop();
        
        if (s_num == f_num)
        result =  true;
        
        // perform the appropriate operation on the two elements
        if (cmd == "<"){
            if(s_num < f_num)
            result = true;    
        } else if (cmd == ">"){
            if(s_num > f_num)
            result = true;    
        } else if (cmd == "<="){
            if(s_num <= f_num)
            result = true;    
        } else if (cmd == ">="){
            if(s_num >= f_num)
            result = true;    
        } 
        
        Datum sum(result);
        RPN_Calc.push(sum);
         
    } 
    
}

/*
* comp_eg
* Parameters: none
* return: void
* purpose: whenever the == operator is encountered as a command, this function
*          is called. the top two elements are popped off the stack, the
*          operation performed on them and the datum with the result is pushed 
*          on the top of the stack.
* Notes: I made a different function for only the == operator because the
*        program can compare datum of different types with == operator.
*        if the datums are of different types then the boolean result will
*        just be false.
*/
void RPNCalc::comp_eq(){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    
    bool result = false;
    
    if (RPN_Calc.top().isInt()){
        int f_num = RPN_Calc.top().getInt();
        RPN_Calc.pop();
        
        if (RPN_Calc.top().isInt()){
            int s_num = RPN_Calc.top().getInt();
            RPN_Calc.pop();
            
            if (s_num == f_num)
            result =  true;
            
        } else {
            RPN_Calc.pop();
            result = false;
        }
         
    } else if (RPN_Calc.top().isBool()){
        int f_Bool = RPN_Calc.top().getBool();
        RPN_Calc.pop();
        
        if (RPN_Calc.top().isBool()){
            int s_Bool = RPN_Calc.top().getBool();
            RPN_Calc.pop();
            
            if (s_Bool == f_Bool)
            result =  true;
        } else {
            RPN_Calc.pop();
            result = false;
        }
        
    } else if (RPN_Calc.top().isRString()){
        std::string f_rstring = RPN_Calc.top().getRString();
        RPN_Calc.pop();
        
        if (RPN_Calc.top().isRString()){
            std::string s_rstring = RPN_Calc.top().getRString();
            RPN_Calc.pop();
            
            if (f_rstring == s_rstring)
            result = true;
        } else {
            RPN_Calc.pop();
            result = false;
        }
    }
    
    Datum sum(result);
    RPN_Calc.push(sum);
}

/*
* drop
* Parameters: none
* return: void
* purpose: causes the top element of the stack to be removed
*/
void RPNCalc::drop(){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    
    RPN_Calc.pop();
}

/*
* dup
* Parameters: none
* return: void
* purpose: duplicates the top element on the stack
*/
void RPNCalc::dup(){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    
    Datum dup = RPN_Calc.top();
    RPN_Calc.push(dup);
}

/*
* exec
* Parameters: none
* return: void
* purpose:  takes the topmost element on the stack, which must be an
*           rstring, and processes its contents as a sequence of commands.
*           If the topmost element of the stack is not an rstring, 
*           it should print “Error: cannot
*           execute non rstring” to std::cerr, and your program should
*           continue to accept input.
* Notes: calls the command_loop and passes in a string stream of commands
*        to it after removing the braces.
*/
void RPNCalc::exec(){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    try {
        RPN_Calc.top().getRString();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: cannot execute non rstring" << std::endl;
        return;
    }
    
    std::string rstring = RPN_Calc.top().getRString();

    RPN_Calc.pop();
    // remove the braces
    std::stringstream my_stream(remove_braces(rstring));
    // pass string stream to command loop
    command_loop(my_stream);

        
}


/*
* parseRString function
* Parameters: a reference to an istream
* return: string (rstring) with the preceding rstring specs.
* purpose: reads data from file until it reaches the end of the input or until
*          all curly braces are matched.
*/
std::string RPNCalc::parseRString(std::istream &input){
    //initialize opening and closing braces counts
    std::string temp_Rstr;
    int open_brace = 1;
    int close_brace = 0;
    // initialize opening braces
    std::string o_brace = "{";
    std::stringstream data;
    // initialize closing braces
    std::string c_brace = "}";
    
    data << "{ ";
    //read from file
    
    while (input >> temp_Rstr){
        data << temp_Rstr;
        data << " ";
        
        if (temp_Rstr ==  c_brace){ 
            close_brace++;
            
            if (open_brace == close_brace){
               break;// break if all curly braces are matched
               
            }
            
        } 
        else if (temp_Rstr == o_brace){
            open_brace++;
            
        }
    
    }
    
    return data.str();
    
}

/*
* remove_braces
* Parameters: a rstring of type string
* return: string with no braces
* purpose: take an rstring and remove its braces
*/
std::string RPNCalc::remove_braces(std::string rstring){
    rstring.erase(0,2);
    rstring.erase(rstring.length() - 3);
    
    return rstring;
    
}

/*
* file
* Parameters: none
* return: void
* purpose: pops the top element off of the stack, which must be an rstring.
*          If it is not an rstring it should print “Error: file operand 
*          not rstring” to std::cerr, and continue to accept input.
*/
void RPNCalc::file(){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    try {
        RPN_Calc.top().getRString();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: file operand not rstring" << std::endl;
        return;
    }
    
    std::string rstring = RPN_Calc.top().getRString();
    remove_braces(rstring);
    
    std::string filename;
    filename = remove_braces(rstring);
    
    std::ifstream input_file;
    input_file.open(filename);
    
    if (not input_file.is_open()){
        std::cerr << "Unable to read "
             << filename << std::endl;
        return;     
    }
    
    command_loop(input_file);
    
    input_file.close();
    
}

/*
* if_cmd
* Parameters: none
* return: void
* purpose: pops an rstring off the stack - will exec this if condition is false
*          pops another rstring off of the stack - will exec this if condition
*          is true.
*          pops a boolean off of the stack - condition to test
* Notes: this function assumes that the stack has false and true case at the
*        top respectively, and test condition at the bottom
*/
void RPNCalc::if_cmd(){
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }

    try {
        RPN_Calc.top().getRString();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: expected rstring in if branch" << std::endl;
        RPN_Calc.pop();
        return;
    }
    //store the top rstring on the stack before deleting it
    std::string temp1 = RPN_Calc.top().getRString();
    RPN_Calc.pop();
    
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    try {
        RPN_Calc.top().getRString();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: expected rstring in if branch" << std::endl;
        RPN_Calc.pop();
        return;
    }
    
    //store the top rstring on the stack before deleting it
    std::string temp2 = RPN_Calc.top().getRString();
    RPN_Calc.pop();
    try {
        RPN_Calc.top();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    
    try {
        RPN_Calc.top().getBool();
    }
    catch(std::runtime_error &e){
        std::cerr << "Error: expected boolean in if test" << std::endl;
        RPN_Calc.pop();
        return;
    }
    
    //store a top boolean on the stack before deleting it
    bool condition = RPN_Calc.top().getBool();
    RPN_Calc.pop();
    
    //check condition then execute as necessary
    if (condition == 0){
        Datum temp(temp1);
        RPN_Calc.push(temp);
        exec();
    } else if (condition == 1){
        Datum temp(temp2);
        RPN_Calc.push(temp);
        exec();
    }
    
}