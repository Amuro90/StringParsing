// main.cpp
#include <iostream>

#include "binput.h"
    
int main() {
    bInput inputObject;
    
    // code for test
    bool promptFromUser = false;
    
    // here i tried to test all the different combination, of course at the end of the test
    // the programm will give the possibility to the user to test it from prompt
    string ArrayForTesting[25] = {
        "$INIT#&IT",
        "$STOP#&OP", 

        "$INIT#2,3&IT", 

        "$INIT#&IT",
        "$ECHO#2,3&HO",
        "$SORT#3,2,5,4&RT",
        "$SUMM#2&MM",
        "$SUMM#28&MM",
        "$VMAX#3,2&AX",
        "$VAVG#3,2&VG",
        "$HHEX#15&EX",
        "$DDEC#1F&EC",
        "$SUMM#10&MM",

        "$STOP#&OP", 

        "$INIT#&IT",
        "$SUMM#10&MM",
        
        "$STOP#&OP", 
        "$SUMM#10&MM",

        "$INIT#&IT",
        "$INIT#&IT",

        "$STOP#&OP", 
        "$INIT#3,4&IT",

        "INIT#IT",

        "$INIT#&IW",

        "$IPIT#&IN"

        };

    int i = 0;
    int sizeOfArrayTest = sizeof(ArrayForTesting) / sizeof(ArrayForTesting[0]);
    
    inputObject.inputString(ArrayForTesting[i]);
    // code for test

    // if you don't want to run the test uncomment the next line and comment the test code
    //inputObject.inputString(ArrayForTesting[i]);
    
    
    while (inputObject.getInputString() != "exit")
    {

        // code for test
        if (i<sizeOfArrayTest){
            cout << "Only for test, to show as if the user have prompted this line:" << endl;
            cout << ArrayForTesting[i] << endl;
            i++;
        }
        // code for test

        if (inputObject.checkDollarSign() && inputObject.checkHashMark() && inputObject.findPositionAmpersend() )
        {
            inputObject.extractAndSaveFourCharacterCommand();
            if (inputObject.checkLastTwoCharacters())
            {
                // if dollar sign in right position, if HashMark in right position, if Ampersend is found after the hashmark go on
                // check if the command is something known
                if (inputObject.retrieveBoolIfCommandExist())
                {
                    if (inputObject.checkParameters()) // check for the specific command if there must be or not parameters, and if we are expecting them they must be correct
                    {
                        inputObject.checkCommand(); // and run it
                    }
                }else
                {
                    // if command is not recognised
                    cout << "$RERR#CMD:"<< inputObject.getFourCharacterCommand() << "&RR" << endl;
                }

            }else
            {
                // wrong checksum
                cout << "$RERR#CRC&RR" << endl;
            }  
        }else
        {
            // poorly formed message
            cout << "$RERR#MSG&RR" << endl;
        }

        // code for test
        if (i<sizeOfArrayTest)
        {
            inputObject.inputString(ArrayForTesting[i]);
        }else
        {
            if (!promptFromUser)
            {
                cout << "Now the test is finished, from now on the user can test different combination"<< endl;
                promptFromUser = true;
            }
            inputObject.inputString("");
        }
        // code for test

        // if not testing comment the code "code for test" and uncomment the next line
        // inputObject.inputString("");
    }
    
    cout << "Program terminated";

    return 0;
}
/* 
input            output

$INIT#&IT                        $INIT#&IT

$INIT#2,3&IT                     "$RERR#MSG&RR"


$STOP#2,3&OP                     "$RERR#MSG&RR"

$STOP#&OP                        $STOP#&OP


$ECHO#2,3&HO                     $ECHO#2,3&HO

$ECHO#&HO                        "$RERR#MSG&RR"

$ECHO#IS5KVTW90DJTERF&HO         $ECHO#IS5KVTW90DJTERF&HO

$ECHO#IS5KVTW90DJTERDF&HO        "$RERR#MSG&RR"


$SORT#3,2&RT                    $SORT#2,3&RT

$SORT#3,2.4&RT                    $SORT#2,3&RT


$SUMM#2,3&MM                    "$RERR#MSG&RR"

$SUMM#2.7&MM                    "$RERR#MSG&RR"

$SUMM#2&MM                      $SUMM#2&MM

$SUMM#2&MM                      $SUMM#4&MM

$VMAX#3,2&AX                    $VMAX#3&AX


$VAVG#3,2&VG                    $VMAX#3&AX


$HHEX#1&EX                      $HHEX#1&EX

$HHEX#15&EX                      $HHEX#f&EX

$INIT#&IT 

$DDEC#1G&EC                      $DDEC#f&EX


*/