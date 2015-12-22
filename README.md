# CmdCalculator
Read from a text file line by line. Each line can either assign a value:<br>
```<VALUE_NAME> = <INTEGER>```<br>
Or it can be a command to calculate the mean average of any previously defined values:<br>
```average (<VALUE_NAME1>, <VALUE_NAME2,…)```<br>
Your program should write the results of these average commands to the standard output.<br>
So for example, your program should be able to read in the following file:<br>
restpower=10<br>
activepower=50<br>
peakpower=90<br>
average (restpower, activepower, peakpower)<br>
The output from the program for this example should be the average of 10, 50 and 90:<br>
50<br>
This should written to the standard output as one line.<br>

# Compile and Run
g++ -std=c++0x -o cmdcalculator cmdcalculator.cpp application.cpp dataprocessor.cpp <br>

# Tests
Tests follows basic TDD (Test Driven Design):<br>
The cmdcalculator must be run with a serious of test inputfiles, contained in the src folder<br>
Also the #define TESTING must be enabled which will enable assert calls<br>

#### test1_input.data
Should catch error as there is a missing VALUE_NAME/VALUE.
#### test2_input.data
Should catch error as there is invalid integer value.
#### test3_input.data
Should catch error as there is invalid format in the VALUE_NAME list.

#### Invalid Input Test
Run as such with inputfile that doesnt not exist<br>
./cmdcalculator input<br>
Should cause assert error.



