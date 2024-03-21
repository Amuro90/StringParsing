// input.cpp
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cctype> // For std::isxdigit

#include "commands.h"

commands::commands()
{
    
}

commands::~commands()
{
    
}

string commands::getPreviousCommand()
{
    return previousCommand;
}

void commands::setPreviousCommand(string NewCommand)
{
    previousCommand = NewCommand;
}

string commands::getStringParameters()
{
    return stringParameters;
}

void commands::setStringParameters(string NewStringParameters)
{
    stringParameters = NewStringParameters;
}

string commands::getEntireCommand()
{
    return entireCommand;
}

void commands::setEntireCommand(string NewEntireCommand)
{
    entireCommand = NewEntireCommand;
}

bool commands::getIsInit()
{
    return isInit;
}

void commands::setIsInit(bool NewIsInit)
{
    isInit= NewIsInit;
}

vector<int> commands::getParamsForVector()
{
    return paramsForVector;
}

void commands::setParamsForVector(vector<int> NewParamsForSort)
{
    paramsForVector = NewParamsForSort;
}

int commands::getResultForSumm()
{
    return resultForSumm;
}

void commands::setResultForSumm(int NewResultForSumm)
{
    resultForSumm = NewResultForSumm;
}

int commands::getCacheIntForSumm()
{   
    return cacheIntForSumm;
}

void commands::setCacheIntForSumm(int NewCacheIntForSumm)
{
    cacheIntForSumm = NewCacheIntForSumm;
}

int commands::getCacheIntForHhex()
{
    return cacheIntForHhex;
}

void commands::setCacheIntForHhex(int NewCacheIntForHhex)
{
    cacheIntForHhex = NewCacheIntForHhex;
}

string commands::getHexForDdec()
{
    return hexForDdec;
}

void commands::setHexForDdec(string NewHexForDdec)
{
    hexForDdec = NewHexForDdec;
}

bool commands::commandExist(string Command)
{
    bool isCommandPresent = CommandMap.count(Command) > 0;

    if (!isCommandPresent) {
        return false;
    }
    return true;
}

bool commands::callRightCommand(string Command)
{
        cacheCommand=Command;
        
        int value = CommandMap[Command];

        // Key found
        switch (value)
        {
        case 1:
            commandInit();
            break;
        case 2:
            commandStop();
            break;
        case 3:
            commandEcho();
            break;
        case 4:
            commandSort();
            break;
        case 5:
            commandSumm();
            break;
        case 6:
            commandVMax();
            break;
        case 7:
            commandVAVG();
            break;
        case 8:
            commandHHEX();
            break;
        case 9:
            commandDDEC();
            break;
        }
    return true;
}




bool commands::commandInit()
{   
    
    if (previousCommand=="" || previousCommand == "STOP")
    {
        isInit=true;
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
        resultForSumm=0;
        cout << "R" << entireCommand << endl; // this is right
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:INIT&RR" << endl;
    }
    return true; 
}

bool commands::commandStop()
{

    if (isInit)
    {
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
        isInit=false;
        cout << "R" << entireCommand << endl; // this is right
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:STOP&RR" << endl;
    }
    return true; 
}

bool commands::commandEcho()
{   
    if (isInit)
    {
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
        cout <<"R" << entireCommand << endl; // this is right
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:STOP&RR" << endl;
    }
    return true; 
}

bool commands::commandSort() // $SORT#3,2&RT
{   
    if (isInit)
    {
        // Sort the vector in descending order using the std::sort function
        sort(paramsForVector.begin(), paramsForVector.end(), greater<int>());

        string cacheString = "";

        // now let's build the string with all the parameters
        for (size_t i = 0; i < this->paramsForVector.size(); ++i) {
        cacheString += std::to_string(paramsForVector[i]); 
            if (i + 1 < paramsForVector.size()) {
                cacheString+= ","; // Optional: Add a delimiter between numbers
            }   
        }
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
        cout << "R$SORT#" << cacheString << "&RT" << endl; // this is right
        paramsForVector.clear();
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:STOP&RR" << endl;
    }
    return true; 
}

bool commands::commandSumm()
{
    if (isInit)
    {
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
        
        resultForSumm+= cacheIntForSumm;
        cout << "R$SUMM#" << resultForSumm << "&MM" << endl; // this is right
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:STOP&RR" << endl;
    }
    return true; 
}

bool commands::commandVMax()
{   
    if (isInit)
    {
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
        auto max_it = std::max_element(paramsForVector.begin(), paramsForVector.end());
        int greatestValue;
        if (max_it != paramsForVector.end()) 
            {
                greatestValue = *max_it;
                cout << "R$VMAX#" << greatestValue << "&AX" << endl; // this is right
            }
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:STOP&RR" << endl;
    }
    
    return true; 
}

bool commands::commandVAVG()
{   
    if (isInit)
    {
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
         double sum = 0.0;
        for (int num : paramsForVector) {
            sum += num;
        }

        // Calculate the average by dividing the sum by the number of elements
        double average = sum / paramsForVector.size();

        cout << "R$VAVG#" << average << "&AX" << endl; // this is right
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:STOP&RR" << endl;
    }
    return true; 
}

bool commands::commandHHEX()
{   
    if (isInit)
    {
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
        std::stringstream stream;
        stream << std::hex << cacheIntForHhex;

        cout << "R$HHEX#" << stream.str() << "&EX" << endl; // this is right
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:STOP&RR" << endl;
    }
    return true; 
}

bool commands::commandDDEC()
{   
    if (isInit)
    {
        previousCommand = cacheCommand; // only when we know that the command take is correct we can set as previous command
        // Check if each character is a valid hexadecimal digit
        for (const char& c : hexForDdec) {
            if (!std::isxdigit(c)) {
                cout << "$RERR#MSG&RR"<< endl;
                return false;
            }
        }

        // Convert each character to its decimal value (0-15)
        int value = 0;
        for (int i = 0; i < 2; ++i) {
            char c = std::toupper(hexForDdec[i]); // Convert to uppercase for consistent handling
            value = (value << 4) | (c >= 'A' ? c - 'A' + 10 : c - '0');
        }

        cout << "R$DDEC#" << value << "&EC" << endl; // this is right
    }
    else
    {
        // this command does not respect the protocol
        cout << "$RERR#PROTO:STOP&RR" << endl;
    }
    return true; 
}

