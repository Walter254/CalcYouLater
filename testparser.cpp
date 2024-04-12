/*
 * testparser.cpp
 *
 * Comp 15 
 *
 * Created by:
 *        Walter Wagude - October 2021
 *
 * Notes: created a testparser.cpp file to test my parseRstring function.
 *        This file has a main that takes arguments from the command line and 
 *        calls the read_data function. 
 *
 */
 
 #include <iostream>
 #include <string>
 #include <fstream>
 #include <sstream>
 
 using namespace std;
 
 string parseRString(istream &input);
 
 int main(int argc, char *argv[])
 {
     //In the case that the user has less arguments on the command line
     if (argc < 2){
         cerr << "Missing some arguments" << endl;
         exit(EXIT_FAILURE);
     }
     
     string filename;
     filename = argv[1];
     //open file
     ifstream input_file;
     input_file.open(filename);
     //In the case that the file does not open
     if (not input_file.is_open()){
         cerr << "Error: could not open file "
              << filename << endl;
         exit(EXIT_FAILURE);
     }
     
     cout << parseRString(input_file) << endl;
     input_file.close();
     
     return 0;
 }
 
 
 
 /*
 *parseRString function
 *Parameters: a reference to an istream
 *return: string (rstring) with the preceding rstring specs.
 *purpose: reads data from file until it reaches the end of the input or until
 *         all curly braces are matched.
 */
 string parseRString(std::istream &input){
     
     std::string temp_Rstr;
     int open_brace = 1;
     int close_brace = 0;
     std::string o_brace = "{";
     std::stringstream data;
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
