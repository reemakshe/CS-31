//
// Reema Kshetramade
// SID: 205328402
// CS31 Project 3

#include "grid.h"
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

//Initializing constants that will be used throughout the program
const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

//Function prototypes for all the functions implemented in the program other than main
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);

int performCommands(string commandString, char& plotChar, int& mode, int& badPos);

int isValid(string command);

int readDigits(string commandString, int i, string& digitCmd);

int main()
{
    setSize(20, 30);
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
          case 0:
            draw();
            break;
          case 1:
                cout << "Syntax error at position " << position+1 << endl;
            break;
          case 2:
                cout << "Cannot perform command at position " << position+1 << endl;
            break;
          default:
              // It should be impossible to get here.
                cerr << "performCommands returned " << status << "!" << endl;
        }
    }
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
    //If an empty string was passed, simply return the function successfully without plotting anything
    if (commandString == "") {
        return 0;
    }
    
    //Check whether the command is syntactically valid
    int resultIsValid = isValid(commandString);
    //If the result is not valid set badPos to the index of the error as returned by the isValid function
    if (resultIsValid != -1) {
        badPos = resultIsValid;
        return 1;
    }
    
    int i = 0;
    //Declare a string variable to hold to the digit part of the command
    string digitCmd;
    //Declare an int variable to hold the distance to plot as given by the digits in the command
    int distance = 0;
    //Set positions of row and column to (1, 1)
    int r = 1;
    int c = 1;
    char currChar;
    bool plotLineResult = true;
    
    //Loop through string while index position is less than size of the string
    while (i < commandString.size()) {
        //Initialize currChar to the lowercase version of the char at index i to make comparisons simpler
        currChar = tolower(commandString[i]);
        digitCmd = "";
        
        //If the character is either h or v, read the digits after and convert that string to an integer
        if (currChar == 'h' || currChar == 'v')
        {
            readDigits(commandString, i, digitCmd);
            distance = stoi(digitCmd);
            
            //If the character is h, the line will be plotted horizontally and change c by the distance
            if (currChar == 'h')
                {
                    //If the result of plotLine is false, then it must mean that the line is outside the grid
                    plotLineResult = plotLine(r, c, distance, HORIZ, plotChar, mode);
                    if (!plotLineResult)
                    {
                        badPos = i;
                        return 2;
                    }
                    c += distance;
                }
            //If char is v, line will be vertical and distance is added to r
            else if (currChar == 'v')
                {
                    //Same as logic above: the only reason for plotLine to return false here is if the
                    //line is outside the grid
                    plotLineResult = plotLine(r, c, distance, VERT, plotChar, mode);
                    if (!plotLineResult)
                    {
                        badPos = i;
                        return 2;
                    }
                    r += distance;
            }
            
            //Increase index by number of digits to make the next iteration of loop start at next command
            i += digitCmd.size();
        }
        //If the current character is f, set the mode to foreground and set plotChar to the next char
        else if (currChar == 'f')
        {
            mode = FG;
            plotChar = commandString[i + 1];
            i++;
        }
        //If the current character is b, set the mode to background and set plotChar to the next char
        else if (currChar == 'b')
        {
            mode = BG;
            plotChar = commandString[i + 1];
            i++;
        }
        //If the current character is c, clear the grid, reset the row and column position to 1,
        //reset the plot character to * and set the mode to foreground
        else if (currChar == 'c')
        {
            clearGrid();
            r = 1;
            c = 1;
            plotChar = '*';
            mode = FG;
        }
        i++;
        
    }
    //If no error is caught before this in the string and all plotting is successful, return 0
    return 0;
}


bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) {
    //Declare variables for the position that r and c would be at when the line is plotted
    int rDist = r;
    int cDist = c;
    
    //Increase the column position by distance if the line is vertical; increase row if vertical
    if (dir == HORIZ)
    {
        cDist += distance;
    }
    else if (dir == VERT)
    {
        rDist += distance;
    }
    
    //Declare a bool variable for whether the r and c position are in the grid for this line
    bool inGridStart = r >= 1 && r <= getRows() && c >= 1 && c <= getCols();
    //Declare bool to check if the entire line to be plotted will be in the grid
    bool inGrid = inGridStart && rDist >= 1 && rDist <= getRows() && cDist >= 1 && cDist <= getCols();
    
    //Check whether the arguments of the function are not correct and return false if they are not correct
    if ((dir != HORIZ && dir != VERT) || !(inGrid) || (fgbg != FG && fgbg != BG) || !(isprint(plotChar)))
    {
        return false;
    }
    
    //If the distance of the line is 0, plot the single point indicated by the row and column position
    if (distance == 0)
    {
        setChar(r, c, plotChar);
    }
    else
    {
        //Plot points using a for loop to set each character 'distance' number of times
        for (int i = 0; i <= abs(distance); i++) {
            //If the fgbg setting is foreground, the character is changed regardless of the current char
            if (fgbg == FG)
            {
                setChar(r, c, plotChar);
            }
            //If mode is background, the char is only plotted if the current char is empty (char is a space)
            else if (fgbg == BG && getChar(r, c) == ' ')
            {
                setChar(r, c, plotChar);
            }
            
            //If distance is positive: increment the row if line is vertical; increment column if horizontal
            if (distance > 0)
            {
                if (dir == VERT)
                    r++;
                else if (dir == HORIZ)
                    c++;
            }
            //If distance is negative: decrement the row if line is vertical; decrement column if horizontal
            else if (distance < 0)
            {
                if (dir == VERT)
                    r--;
                else if (dir == HORIZ)
                    c--;
            }
        }
    }
    //Return true if line is plotted successfully
    return true;
}

int isValid(string command) {
    //Initialize an empty string variable to hold the digit part of a command
    string digitCmd = "";
    char currChar;
    
    for (int i = 0; i < command.size(); i++) {
        //Set the current character to the lowercase verson of the character at index i in the command string
        currChar = tolower(command[i]);
        
        //If currChar is h or v, there should be a digit command after it which is processed by readDigits
        if (currChar == 'h' || currChar == 'v')
        {
            digitCmd = "";
            readDigits(command, i, digitCmd);
            //Increase the index by the length of the digit command so that the next character accessed
            //is the next command in the string
            i += digitCmd.size();
            
            //If the length of the digit command string is 0, that means there is no digits after the command
            //This is a syntax error, so function returns index of error (index of where digits should start)
            if (digitCmd.size() == 0)
            {
                return i + 1;
            }
        }
        //If currChar is f or b, it should not be the last character in the command and there should be
        //a printable character after it
        else if (currChar == 'f' || currChar == 'b')
        {
            if (i == command.size() - 1 || !(isprint(command[i + 1])))
            {
                return i + 1;
            }
            i++;
        }
        //The only other possible command is c, so if currChar is not c then this is a syntax error and the
        //function returns the index of the error
        else if (currChar != 'c')
        {
            return i;
        }
    
    }
    //If there is no syntax error in the command, the function returns -1
    return -1;
}

int readDigits(string commandString, int i, string& digitCmd) {
    //Add one to the index of the command because the digits should start at the next character
    i++;
    
    //The maximum length of the digit command is 2, so the for loop must only run twice to collect the digits
    for (int k = 0; k < 2; k++) {
        //Only the first character can be something other than a digit, and it can only be a negative sign
        if ((k == 0 && commandString[i] == '-'))
        {
            digitCmd += commandString[i];
            //Decrement k because the negative sign is not a digit, so the loop can still run two more times
            //to get a maximum of two digits
            k--;
            i++;
        }
        else if (isdigit(commandString[i]))
        {
            //If the next character is a digit, add it to the digit command string
            digitCmd += commandString[i];
            i++;
        }
    }
    
    //If the size of the digit command is 0, return 0 to avoid passing an empty string to stoi()
    if (digitCmd.size() == 0)
    {
        return 0;
    }
    //If there is a digit command, return the integer representation of the command
    else
    {
        return stoi(digitCmd);
    }
}



