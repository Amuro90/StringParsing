// input.h
#ifndef _BINPUT_H
#define _BINPUT_H

#include <string>
#include <vector>

#include "commands.h"

using namespace std;

class bInput {
    private:
        commands checking;

        string checksum;
        string fourCharacterCommand;

        int positionAmpersend;
        
        vector<int> numParameters;

    public:
        bInput();
        ~bInput();

        void inputString(string ForTesting = "");

        string getInputString();
        void setInputString(string changeChecksum);

        bool checkDollarSign();

        void extractAndSaveFourCharacterCommand();
        
        bool retrieveBoolIfCommandExist ();

        string getFourCharacterCommand();

        bool checkCommand();

        bool findPositionAmpersend();

        bool checkParameters();
        
        bool checkHashMark();

        bool checkLastTwoCharacters();
};

#endif // INPUT_H