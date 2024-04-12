/*
 * parser.cpp
 *
 * Comp 15 
 *
 * Created by:
 *        Walter Wagude - October 2021
 *
 * Notes: Implementation of the parseRString function. The function takes a 
 *        reference to an istream as a parameter and continues to read from it
 *        until it reaches the end of the input
 *
 */
 
 #include <iostream>
 #include <string>
 #include <fstream>
 #include <sstream>
 using namespace std;
 
 /*
 * parseRString function
 * Parameters: a reference to an istream
 * return: string (rstring) with the preceding rstring specs.
 * purpose: reads data from file until it reaches the end of the input or until
 *          all curly braces are matched.
 */
 string parseRString(std::istream &input){
     
     std::string temp_Rstr;
     // initialize opening and closing braces counts
     int open_brace = 1;
     int close_brace = 0;
     // initialize opening brace
     std::string o_brace = "{";
     std::stringstream data;
     // initialize closing brace
     std::string c_brace = "}";
     
     data << "{ ";
     // read from file
     while (input >> temp_Rstr){
         data << temp_Rstr;
         data << " ";

         if (temp_Rstr ==  c_brace){ 
             close_brace++;
             if (open_brace == close_brace){
                break; // break if all curly braces are matched
             } 
         } 
         else if (temp_Rstr == o_brace){
             open_brace++;
         } 
     }
     return data.str();
     
 }