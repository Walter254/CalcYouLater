###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Walter Wagude
#########################################################
#             proj1: CalcYouLater Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o parser.o
	$(CXX) -o CalcYouLater $^
# This rule builds RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h  Datum.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

# This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c  DatumStack.cpp
	
# This rule builds parser.o
parser.o: parser.cpp
	$(CXX) $(CXXFLAGS) -c  parser.cpp
# This rule builds main.o
main.o: main.cpp RPNCalc.h DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# The below rule will be used by my  unit_test. 
unit_test: unit_test_driver.o  DatumStack.o RPNCalc.o Datum.o
	$(CXX) $(CXXFLAGS) $^


# This rule provides my submission 
provide:
	provide comp15 proj1_calcyoulater DatumStack.h DatumStack.cpp\
				    main.cpp RPNCalc.h\
					parser.cpp testparser.cpp testparser.txt\
					test_if_cmd.txt test_file_command.txt\
				    RPNCalc.cpp  \
				    unit_tests.h Makefile README 
					
#This rule provides my phase1
phase1:
	provide comp15 proj1phase1 DatumStack.h DatumStack.cpp\
				    README Makefile parser.cpp testparser.cpp \
					testparser.txt unit_tests.h

# remove executables, object code, and temporary files from the current folder 
clean:
	rm -f RPNCalc.o DatumStack.o main.o parser.o a.out

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
