// input.cpp
#include <iostream>
#include <string>
#include <algorithm>

#include "bInput.h"


bInput::bInput()
{
    
}

bInput::~bInput()
{
    
}


void bInput::inputString(string ForTesting) {
    if (ForTesting=="")
    {
        std::string input;
        std::cout << "Please enter a string or exit to exit the program :"<< endl;
        std::getline(std::cin, input);
        setInputString(input);
        return;
    }

    setInputString(ForTesting);
    
    
}

string bInput::getInputString()
{
    return checksum;
}

void bInput::setInputString(string changeString)
{
    checksum=changeString;   
}

bool bInput::checkDollarSign()
{
    // first character check == $
    if ('$'==checksum[0])
    {
        return true;
    }
    else{
        return false;
    }

}

void bInput::extractAndSaveFourCharacterCommand()
{
    // get out of the string between the position 1 and 5 the command
    fourCharacterCommand = checksum.substr(1,4);
}

bool bInput::retrieveBoolIfCommandExist()
{
    return checking.commandExist(fourCharacterCommand);
}

string bInput::getFourCharacterCommand()
{
    return fourCharacterCommand;
}

bool bInput::checkCommand()
{
    // cout << "check command method " << fourCharacterCommand << endl;
    checking.setEntireCommand(checksum);
    return checking.callRightCommand(fourCharacterCommand);

}

bool bInput::findPositionAmpersend()
{
    // check if the is the & simbol
    auto isAmpersandPresent = std::find(checksum.begin(), checksum.end(), '&');
    int index;
    if (isAmpersandPresent != checksum.end()) {
        index = std::distance(checksum.begin(), isAmpersandPresent);
        positionAmpersend = index;
        if (positionAmpersend>5) // if the & is found and is beyond the # that is on position 5 return true otherwise false
        {
            return true;
        }
    } else {
        positionAmpersend = 0;
        return false;
    }
    return false;
}

bool bInput::checkParameters()
{
    string parameters = checksum.substr(6,positionAmpersend-6);
    checking.setStringParameters(parameters);
    if ((fourCharacterCommand == "INIT" || fourCharacterCommand== "STOP") && parameters.length()!=0 )
    {   
        // poorly formed message
        cout << "$RERR#MSG&RR" << endl;
        return false;
    }
    if (fourCharacterCommand == "ECHO" && (parameters.length()<1 || parameters.length()>15))
    {
        // poorly formed message
        cout << "$RERR#MSG&RR" << endl;
        return false;
    }

    if (fourCharacterCommand == "SUMM")
    {
        size_t pos = parameters.find(',');
        size_t posp = parameters.find('.');//check for decimal numbers

        if (pos != std::string::npos || posp != std::string::npos){ // if is present a , or a . then this parameter is incorrect
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
        else{
            int cacheNumber;
                    try {
                        cacheNumber = stoi(parameters);
                        checking.setCacheIntForSumm(cacheNumber);
                    } catch (const invalid_argument& e) {
                        cout << "$RERR#MSG&RR" << endl;
                    }
            
        }

    }

    if (fourCharacterCommand == "SORT")
    {
        string cacheStringNumber="";

        size_t posp = parameters.find('.');//check for decimal numbers

        if (posp != std::string::npos){ // if is present a , or a . then this parameter is incorrect
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
        
        for (size_t i = 0; i<=parameters.length();i++)
        {   
            if (parameters[i]==','|| i==parameters.length())
            {
                if (cacheStringNumber!="")
                {
                    int cacheNumber;
                    try {
                        cacheNumber = stoi(cacheStringNumber);
                        this->numParameters.push_back(cacheNumber);
                        cacheStringNumber="";
                    } catch (const invalid_argument& e) {
                        cout << "$RERR#MSG&RR" << endl;
                    }
                }
            }else
            {
                cacheStringNumber = cacheStringNumber + parameters[i];
            }
        }
        if (numParameters.size()>50 || numParameters.size()<1)
        {
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
    }

    if (fourCharacterCommand == "VMAX")
    {
        string cacheStringNumber="";

        size_t posp = parameters.find('.');//check for decimal numbers

        if (posp != std::string::npos){ // if is present a , or a . then this parameter is incorrect
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
        
        for (size_t i = 0; i<=parameters.length();i++)
        {   
            if (parameters[i]==','|| i==parameters.length())
            {
                if (cacheStringNumber!="")
                {
                    int cacheNumber;
                    try {
                        cacheNumber = stoi(cacheStringNumber);
                        this->numParameters.push_back(cacheNumber);
                        cacheStringNumber="";
                    } catch (const invalid_argument& e) {
                        cout << "$RERR#MSG&RR" << endl;
                    }
                }
            }else
            {
                cacheStringNumber = cacheStringNumber + parameters[i];
            }
        }
        if (numParameters.size()>20 || numParameters.size()<1)
        {
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
    }

    if (fourCharacterCommand == "VAVG")
    {
        string cacheStringNumber="";

        size_t posp = parameters.find('.');//check for decimal numbers

        if (posp != std::string::npos){ // if is present a , or a . then this parameter is incorrect
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
        
        for (size_t i = 0; i<=parameters.length();i++)
        {   
            if (parameters[i]==','|| i==parameters.length())
            {
                if (cacheStringNumber!="")
                {
                    int cacheNumber;
                    try {
                        cacheNumber = stoi(cacheStringNumber);
                        this->numParameters.push_back(cacheNumber);
                        cacheStringNumber="";
                    } catch (const invalid_argument& e) {
                        cout << "$RERR#MSG&RR" << endl;
                    }
                }
            }else
            {
                cacheStringNumber = cacheStringNumber + parameters[i];
            }
        }
        if (numParameters.size()>20 || numParameters.size()<1)
        {
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
    }

    if (fourCharacterCommand == "HHEX")
    {
        size_t pos = parameters.find(',');
        size_t posp = parameters.find('.');//check for decimal numbers

        if (pos != std::string::npos || posp != std::string::npos){ // if is present a , or a . then this parameter is incorrect
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
        else{
            int cacheNumber;
                    try {
                        cacheNumber = stoi(parameters);
                        checking.setCacheIntForHhex(cacheNumber);
                    } catch (const invalid_argument& e) {
                        cout << "$RERR#MSG&RR" << endl;
                    }
            
        }

    }
    
    if (fourCharacterCommand == "DDEC")
    {
        if (parameters.length()==2)
        {
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
            return false;
        }
        checking.setHexForDdec(parameters);
        return true;
    }
    else{
        
    }

    checking.setParamsForVector(numParameters);
    numParameters.clear();
    return true;


}

bool bInput::checkHashMark()
{
    if (checksum[5]=='#')
    {
        return true;
    }
    else {
        return false;
    }
}

bool bInput::checkLastTwoCharacters()
{
    string LastTwoCharacters = checksum.substr(positionAmpersend+1,2);

    if ((fourCharacterCommand[2]==LastTwoCharacters[0]) && (fourCharacterCommand[3]==LastTwoCharacters[1]))
        return true;
    
    return false;
}
