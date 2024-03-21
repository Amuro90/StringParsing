// commands.h
#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream> 

using namespace std;

class commands {
    private:
        bool isInit = false;
        
        string previousCommand="";
        string stringParameters;
        string entireCommand;
        string cacheCommand; // used to transport the command that is begin tested
        string hexForDdec = "";
        
        int resultForSumm = 0; // this int stores the compound result for summ
        int cacheIntForSumm = 0; // the new int that will be added to the resultForSumm
        int cacheIntForHhex = 0;

        vector <int> paramsForVector;


        unordered_map <string,int> CommandMap = {
            {"INIT", 1},
            {"STOP", 2},
            {"ECHO", 3},
            {"SORT", 4},
            {"SUMM", 5},
            {"VMAX", 6},
            {"VAVG", 7},
            {"HHEX", 8},
            {"DDEC", 9}    
        };

    public:
        commands();
        ~commands();

        string getPreviousCommand();
        void setPreviousCommand(string NewCommand);

        string getStringParameters();
        void setStringParameters(string NewStringParameters);

        string getEntireCommand();
        void setEntireCommand(string NewEntireCommand);

        bool getIsInit();
        void setIsInit(bool NewIsInit);

        vector<int> getParamsForVector();
        void setParamsForVector(vector<int> NewParamsForVector);

        int getResultForSumm();
        void setResultForSumm(int NewResultForSumm);

        int getCacheIntForSumm();
        void setCacheIntForSumm(int NewCacheIntForSumm);

        int getCacheIntForHhex();
        void setCacheIntForHhex(int NewCacheIntForHhex);

        string getHexForDdec();
        void setHexForDdec(string NewHexForDdec);

        bool commandExist (string Command); // check if the command exist or is just a 4 unknown letters
        bool callRightCommand(string Command);

        bool commandInit();
        bool commandStop();
        bool commandEcho();
        bool commandSort();
        bool commandSumm();
        bool commandVMax();
        bool commandVAVG();
        bool commandHHEX();
        bool commandDDEC();

};

#endif // commands_H