#include "IOHandler.h"

using namespace std;

IOHandler::IOHandler()
{
    //ctor
}

IOHandler::~IOHandler()
{
    //dtor
}

void IOHandler::runIntro(void)
{
    //ascii art intro
    cout << "##      ## ######## ##        ######   #######  ##     ## ########    ########  #######  " << endl;
    cout << "##  ##  ## ##       ##       ##    ## ##     ## ###   ### ##             ##    ##     ## " << endl;
    cout << "##  ##  ## ##       ##       ##       ##     ## #### #### ##             ##    ##     ## " << endl;
    cout << "##  ##  ## ######   ##       ##       ##     ## ## ### ## ######         ##    ##     ## " << endl;
    cout << "##  ##  ## ##       ##       ##       ##     ## ##     ## ##             ##    ##     ## " << endl;
    cout << "##  ##  ## ##       ##       ##    ## ##     ## ##     ## ##             ##    ##     ## " << endl;
    cout << " ###  ###  ######## ########  ######   #######  ##     ## ########       ##     #######  " << endl;
    cout << endl;
    cout << endl;
    cout << "########  ##     ## ########  #### ##    ##  ##   ######      ######  ##     ## ########  ########" << endl;
    cout << "##     ## ##     ## ##     ##  ##  ##   ##  #### ##    ##    ##    ## ##     ## ##     ## ##      " << endl;
    cout << "##     ## ##     ## ##     ##  ##  ##  ##    ##  ##          ##       ##     ## ##     ## ##      " << endl;
    cout << "########  ##     ## ########   ##  #####    ##    ######     ##       ##     ## ########  ######  " << endl;
    cout << "##   ##   ##     ## ##     ##  ##  ##  ##              ##    ##       ##     ## ##     ## ##      " << endl;
    cout << "##    ##  ##     ## ##     ##  ##  ##   ##       ##    ##    ##    ## ##     ## ##     ## ##      " << endl;
    cout << "##     ##  #######  ########  #### ##    ##       ######      ######   #######  ########  ########" << endl;
    cout << endl;
    cout << endl;
    cout << " ######  #### ##     ## ##     ## ##          ###    ########  #######  ########      #######    #####      ##    ####### " << endl;
    cout << "##    ##  ##  ###   ### ##     ## ##         ## ##      ##    ##     ## ##     ##    ##     ##  ##   ##   ####   ##     ##" << endl;
    cout << "##        ##  #### #### ##     ## ##        ##   ##     ##    ##     ## ##     ##           ## ##     ##    ##   ##     ##" << endl;
    cout << " ######   ##  ## ### ## ##     ## ##       ##     ##    ##    ##     ## ########      #######  ##     ##    ##    ####### " << endl;
    cout << "      ##  ##  ##     ## ##     ## ##       #########    ##    ##     ## ##   ##      ##        ##     ##    ##   ##     ##" << endl;
    cout << "##    ##  ##  ##     ## ##     ## ##       ##     ##    ##    ##     ## ##    ##     ##         ##   ##     ##   ##     ##" << endl;
    cout << " ######  #### ##     ##  #######  ######## ##     ##    ##     #######  ##     ##    #########   #####    ######  ####### " << endl;
    cout << endl;
    //ascii art was generated with the patorjk ascii art generator
    //intro includes help
    runHelp();
}

void IOHandler::runHelp(void)
{
    //runs help file
    cout << "Use standard notation to manipulate the cube" << endl;
    cout << endl;
    cout << "Possible moves are:" << endl;
    cout << "F - Front   - Turns Blue Face" << endl;
    cout << "B - Back    - Turns Green Face"<< endl;
    cout << "R - Right   - Turns Red " << endl;
    cout << "L - Left    - Turns Magenta (Orange Face)" << endl;
    cout << "U - Up      - Turns Yellow" << endl;
    cout << "D - Down    - Turns White Face" << endl;
    cout << "E - Equator - Slice between top and bottom" << endl;
    cout << "M - Middle  - Between Top and bottom" << endl;
    cout << "S - Side    - Between front and back" << endl;
    cout << endl;
    cout << "These moves can be modified by the following move suffixes" << endl;
    cout << endl;
    cout << "none - Regular Turn  - Face turns clockwise relative to the face" << endl;
    cout << "'    - Inverted Turn - Face turns counter-clockwise relative to the face" << endl;
    cout << "2    - Double Turn   - Face turns 180 equivalent to 2 regular or inverted turns" << endl;
    cout << endl;
    cout << "Double lay turns are also supported. A double layer turn is when 2 layers are turned at once. " << endl;
    cout << "For example a double layer u turn would turn the top face and the equator of the cube. ";
    cout << "They can be called using by lowercase letters. " << endl;
    cout << "Hint: keep caps lock on as single face turns are much more common than double turns" << endl;
    cout << endl;
    cout << "Possible Commands" << endl;
    cout << endl;
    cout << "reset    - Resets cube to a solved state" << endl;
    cout << "help     - Shows this help dialog" << endl;
    cout << "credits  - Shows credits" << endl;
    cout << "exit     - Exits program" << endl;
    cout << "save     - Saves current state to a file" << endl;
    cout << "load     - Loads from a file to current state" << endl;
    cout << "pattern  - Displays preloaded patterns" << endl;
    cout << "scramble - Scrambles the cube" << endl;
    cout << endl;
    system("pause");
}

void IOHandler::runCredits(void)
{
    //runs credits
    cout << "Rubik's Cube Simulator 2018 (c)" << endl;
    cout << endl;
    cout << "Created by       : Hao Yun" << endl;
    cout << "With the help of : Jim Fare, Isaiah Witzkey, Abigail Ripley-Natarelli and patorjk " << endl;
    system("pause");
}

int IOHandler::suffix(char turn)
{
    //determines proper suffix based on char passed in
    if(turn == '\'') //char escape to allow single quote
    {
        return 1;
    }
    else if(turn == '2')
    {
        return 2;
    }
    else //defaults to regular clockwise turn
    {
        return 0;
    }
}

int IOHandler::type(char turn)
{
    bool type;
    type = islower(turn);

    //determines and stores of the inputted move is upper or lower case
    //lower case means a wide turn where 2 slices are turned while upper case
    //is just a regular move

    turn = tolower(turn);
    //case is stored so case can be defaulted to lower for easy comparisons

    char dic[] = {'f', 'r', 'l', 'b', 'd', 'u', 'e', 's', 'm'};
    /*
    Values and corresponding moves:
    0 - Front
    1 - Right
    2 - Left
    3 - Back
    4 - Down
    5 - Up
    6 - Equator (slice between top and bottom)
    7 - Side (between front and back)
    8 - Middle (top and bottom)
    */

    //finds and returns which element of the array the character corresponds to
    for(int i = 0; i < 9; i++)
    {
        if(turn == dic[i])
        {
            if(i <= 5 && type) //if char is lower case that means it is a double turn and it gets offset by 10
            {
                return i + 10;
            }
            else
            {
                return i;
            }
        }
    }
    //returns -1 when move is not valid
    return -1;
}

vector <string> IOHandler::partion(string moves)
{
    //vector to store output
    vector <string> lst;

    //goes through moves array and looks for moves
    for (int i = 0 ; i < moves.length(); i++)
    {
        int mov = type(moves[i]); //finds the type if any of move the current char is
        int nextmov = type(moves[i + 1]); //finds the type if any of move the next char is
        string push; //string to collect the moves and push back vector with

        if(mov == -1) //if the current char is not a move then just move on
        {
            continue;
        }
        //if program has gotten pass this part then that means the current char must be a valid move
        //if the next move is not a valid move then it must be a modifier or some other ignored character
        if(nextmov != -1)
        {
            push += moves[i];//adds the current char to string
            push += '#'; //adds filler so program will not go off array
        }
        else //otherwise it must be another move
        {
            push += moves[i]; //add the move char to the string
            push += moves[i + 1]; //add modifier to string
            i++; //i is incremented even more so it skips next the next char as it is already accounted for
        }
        lst.push_back(push); //adds this string to the vector
    }
    //returns vector after whole string is processed
    return lst;
}

bool IOHandler::saveFile(string name, int* values)
{
    ofstream fout; //file out object
    fout.open(name.c_str()); //opens file
    if(!fout.is_open())//if file is not open return error
    {
        return false;
    }
    //if the file is properly loaded write all the passed in values onto document
    for(int i = 0; i < 54; i++)
    {
        fout << values[i] << endl; //values separated by newlines
    }
    fout.close();//close file
    return true; //return successful save
}
bool IOHandler::loadFile(string name,int* tiles)
{
    ifstream fin; //file in object
    int value; //int variable for reading in integers
    fin.open(name.c_str()); //opens file
    if(!fin.is_open())//if file is not open return error
    {
        return false;
    }

    for(int i = 0; i < 54; i++) //read 54 integers from file
    {
        fin >> value;
        tiles[i] = value; //passes value into tiles
    }
    fin.close(); //close file
    return true; //return successful
}
