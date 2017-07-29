/*
Cube Simulator 2018
(c) Mr. Yun
Simulates a Rubik's Cube
*/

//Note: Screen buffer width should be at least 122 characters wide and 30 characters wide for proper viewing
//Also please use a 8 x 12 raster font for optimal viewing

#include <iostream>
#include <cctype>
#include <vector>
#include "hao.h"
#include "ConsoleOutput.h"
#include "CubeState.h"
#include "IOHandler.h"

using namespace std;

void multi(ConsoleOutput consoleoutput, CubeState cubestate, IOHandler iohandler, HANDLE hstdout, vector <string> partioned, int delay);

int main()
{

    //init handle for console output
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    //init 3 classes needed for program execution
    ConsoleOutput consoleoutput;
    CubeState cubestate;
    IOHandler iohandler;

    //run "splash screen"
    iohandler.runIntro();

    //////////////////////////////
    //main game loop starts here//
    //////////////////////////////

    while(true)
    {
        system("cls"); //clear screen for new cube
        consoleoutput.print(cubestate.Gettiles(), hstdout); //print cube onto screen
        string input = getString("Enter Command:"); //get user input

        //input handling
        //first determine that input is not one of the many preset commands
        //if input is then execute related command
        if(input == "reset")
        {
            //resets cube
            cubestate.Settiles(cubestate.solvedCube());
        }
        else if(input == "help")
        {
            //clears screen then runs help
            system("cls");
            iohandler.runHelp();
        }
        else if(input == "credits")
        {
            //clears screen then runs credits
            system("cls");
            iohandler.runCredits();
        }
        else if(input == "exit")
        {
            //exits program
            return 0;
        }
        else if(input == "save")
        {
            //runs dialog to save current state
            string name = getString("Please enter the name of the file you would like to load from:");
            bool complete = iohandler.saveFile(name, cubestate.Gettiles());
            //get string and call io handler to save current state
            //output error if save is not complete
            if(!complete)
            {
                cout << "Failed to Save to file" << endl;
                Sleep(1500);
            }
        }
        else if(input == "load")
        {
            //runs dialog to load current state
            string name = getString("Please enter the name of the file you would like to save to:");
            //creates an int array to store the values read from file before they are passed on
            int temp[54];
            bool complete = iohandler.loadFile(name, temp);
            //loads values from file, set cube to values if load succeeded and output error if failed
            if(complete)
            {
                cubestate.Settiles(temp);
            }
            else
            {
                cout << "Failed to load from file" << endl;
                Sleep(1500);
            }
        }
        else if(input == "scramble")
        {
            //iterates 20 times for "optimal scramble"
            for(int i = 0; i < 20; i++)
            {
                //uses random numbers moudlused to create desired ranges of 0-5 and 0-2
                cubestate.callManip(rand() % 6, rand() % 3);
                system("cls"); //clear screen for new cube
                consoleoutput.print(cubestate.Gettiles(), hstdout); //print cube onto screen
                Sleep(100);
            }
            //NOTE//
            //it is possible for moves to be immediately undone but this is not serious enough for me to care
            //for example a F could be generated and then a F' after
        }
        else if(input == "pattern")
        {
            cout << "Patterns: " << endl;
            cout << "1 - Cube in a cube " << endl;
            cout << "2 - Cube in a cube in a cube" << endl;
            cout << "3 - Superflip" << endl;
            cout << "4 - Facing Checker boards" << endl;
            cout << "5 - Cross" << endl;
            int type = getInt("Please Enter Desired Pattern", 0, 5);
            //dialog to get desired pattern
            vector <string> alg;
            //vector for storing partition moves that come from hard coded strings
            //determine which string to use biased on
            //partitioning on the stop is easier than creating vectors with desired values so it is done on the spot
            switch(type)
            {
            case 1:
                alg = iohandler.partion("FLFU'RUF2L2U'L'BD'B'L2U");
                break;
            case 2:
                alg = iohandler.partion("U' L' U' F' R2 B' R F U B2 U B' L U' F U R F'");
                break;
            case 3:
                alg = iohandler.partion("U R2 F B R B2 R U2 L B2 R U' D' R2 F R' L B2 U2 F2 ");
                break;
            case 4:
                alg = iohandler.partion(" U2 F2 U2 F2 B2 U2 F2 D2");
                break;
            case 5:
                alg = iohandler.partion(" U F B' L2 U2 L2 F' B U2 L2 U");
                break;
            default:
                cout << "Invalid Pattern Id" << endl;
                Sleep(1500);
                break;
            }
            multi(consoleoutput, cubestate, iohandler, hstdout, alg, 30);
        }
        //if the input is longer than 2 characters and is not the all the commands above
        //then it means multiple moves have been inputted
        else if(input == "multiple")
        {
            string moves = getString("Please enter multiple moves:"); //gets moves
            //uses partition function to separate each move into a separate string
            //also filters out other non-move characters such as brackets used to group moves together
            vector <string> partioned = iohandler.partion(moves);
            //requests delay between moves
            int delay = getInt("Please enter delay in ms between moves:");
            multi(consoleoutput, cubestate, iohandler, hstdout, partioned, delay);
        }
        else if(input.length() > 2)
        {
            //outputs error message, sleeps to give user time to read message
            cout << "Invalid Move or Command" << endl;
            cout << "Enter ? for help" << endl;
            Sleep(1500);
        }
        else
        {
            //handles a single move
            //gets required values
            int mov = iohandler.type(input[0]);
            int dir = iohandler.suffix(input[1]);

            //makes sure move is valid
            if (mov != -1)
            {
                cubestate.callManip(mov, dir);
            }
            else
            {
                //outputs error message, sleeps to give user time to read message
                cout << "Invalid Move or Command" << endl;
                cout << "Enter ? for help" << endl;
                Sleep(1500);
            }
        }
    }
    ////////////////////////////
    //main game loop ends here//
    ////////////////////////////
    return 0;
}

void multi(ConsoleOutput consoleoutput, CubeState cubestate, IOHandler iohandler, HANDLE hstdout, vector <string> partioned, int delay)
{
    //goes through vector applying all moves
    for(int i = 0; i < partioned.size(); i++)
    {
        string current = partioned[i]; //creates temporary string from current move
        int mov = iohandler.type(current[0]); //gets type of move and suffix
        int dir = iohandler.suffix(current[1]);

        cubestate.callManip(mov, dir); //calls manipulation using the values just determined
        //refreshes display and waits specified amount
        system("cls");
        consoleoutput.print(cubestate.Gettiles(), hstdout);
        Sleep(delay);
    }
}
