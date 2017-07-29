#include "CubeState.h"

using namespace std;

CubeState::CubeState()
{
    Settiles(solvedCube());
    //fills the tiles array with a solved cube
}

CubeState::~CubeState()
{
    //dtor
}

int CubeState::callManip(int mov, int dir)
{
    /*
    A turn of one face of a rubik's cube consists of 5 sets of 4 tiles swapping
    Arrays of pointers to the values of the 4 tiles desired to be turned are hard coded in
    If given one of these 4 tile point arrays, the values can be easily rotated forward or backwards
    6 groups of 5 are made for each of the six faces

    Naming Convention:

    First letter is move in standard notion
    Second letter is whether it is inner (on the face that is being turned), or outer (not on the face being turned)
    Third letter is which type of piece it is
    e = edge
    c = corner
    d = left side corner

    For center slice turns only 3 suffules are needed and the rest are filled with filler
    the name convention is r, l and m standing from right, left and middle

    These values are here because of the issue with passing around variables
    You told me that this is acceptable as long as it works
    */
    int* foe[4] = {&tiles[7 ], &tiles[27], &tiles[46], &tiles[23]};
    int* fie[4] = {&tiles[13], &tiles[26], &tiles[37], &tiles[24]};
    int* fic[4] = {&tiles[12], &tiles[14], &tiles[38], &tiles[36]};
    int* foc[4] = {&tiles[6 ], &tiles[15], &tiles[47], &tiles[35]};
    int* fod[4] = {&tiles[8 ], &tiles[39], &tiles[45], &tiles[11]};

    int* roe[4] = {&tiles[5 ], &tiles[30], &tiles[50], &tiles[26]};
    int* rie[4] = {&tiles[16], &tiles[29], &tiles[40], &tiles[27]};
    int* ric[4] = {&tiles[15], &tiles[17], &tiles[41], &tiles[39]};
    int* roc[4] = {&tiles[8 ], &tiles[18], &tiles[53], &tiles[38]};
    int* rod[4] = {&tiles[2 ], &tiles[42], &tiles[47], &tiles[14]};

    int* loe[4] = {&tiles[3 ], &tiles[24], &tiles[48], &tiles[32]};
    int* lie[4] = {&tiles[10], &tiles[23], &tiles[34], &tiles[21]};
    int* lic[4] = {&tiles[9 ], &tiles[11], &tiles[35], &tiles[33]};
    int* loc[4] = {&tiles[0 ], &tiles[12], &tiles[45], &tiles[44]};
    int* lod[4] = {&tiles[6 ], &tiles[36], &tiles[51], &tiles[20]};

    int* boe[4] = {&tiles[1 ], &tiles[21], &tiles[52], &tiles[29]};
    int* bie[4] = {&tiles[19], &tiles[32], &tiles[43], &tiles[30]};
    int* bic[4] = {&tiles[18], &tiles[20], &tiles[44], &tiles[42]};
    int* boc[4] = {&tiles[2 ], &tiles[9 ], &tiles[51], &tiles[41]};
    int* bod[4] = {&tiles[0 ], &tiles[33], &tiles[53], &tiles[17]};

    int* doe[4] = {&tiles[37], &tiles[40], &tiles[43], &tiles[34]};
    int* die[4] = {&tiles[46], &tiles[50], &tiles[52], &tiles[48]};
    int* dic[4] = {&tiles[45], &tiles[47], &tiles[53], &tiles[51]};
    int* doc[4] = {&tiles[33], &tiles[36], &tiles[39], &tiles[42]};
    int* dod[4] = {&tiles[35], &tiles[38], &tiles[41], &tiles[44]};

    int* uoe[4] = {&tiles[19], &tiles[16], &tiles[13], &tiles[10]};
    int* uie[4] = {&tiles[1 ], &tiles[5 ], &tiles[7 ], &tiles[3 ]};
    int* uic[4] = {&tiles[0 ], &tiles[2 ], &tiles[8 ], &tiles[6 ]};
    int* uoc[4] = {&tiles[20], &tiles[17], &tiles[14], &tiles[11]};
    int* uod[4] = {&tiles[18], &tiles[15], &tiles[12], &tiles[9 ]};

    int* el[4] = {&tiles[32],&tiles[29],&tiles[26],&tiles[23]};
    int* ec[4] = {&tiles[31],&tiles[28],&tiles[25],&tiles[22]};
    int* er[4] = {&tiles[30],&tiles[27],&tiles[24],&tiles[21]};

    int* sl[4] = {&tiles[3],&tiles[16],&tiles[50],&tiles[34]};
    int* sc[4] = {&tiles[4],&tiles[28],&tiles[49],&tiles[22]};
    int* sr[4] = {&tiles[5],&tiles[40],&tiles[48],&tiles[10]};

    int* ml[4] = {&tiles[1],&tiles[13],&tiles[46],&tiles[43]};
    int* mc[4] = {&tiles[4],&tiles[25],&tiles[49],&tiles[31]};
    int* mr[4] = {&tiles[7],&tiles[37],&tiles[52],&tiles[19]};

    int* fil[4] = {&tiles[0],&tiles[0],&tiles[0],&tiles[0]};
    //used for fill up arrays so there are no issues later on

    //then these sets of 5 are grouped together for organization
    //names are the standard notation names

    int** f[5] = {foe, fie, fic, foc, fod};
    int** r[5] = {roe, rie, ric, roc, rod};
    int** l[5] = {loe, lie, lic, loc, lod};
    int** b[5] = {boe, bie, bic, boc, bod};
    int** d[5] = {doe, die, dic, doc, dod};
    int** u[5] = {uoe, uie, uic, uoc, uod};

    int** e[5] = {el, ec, er, fil, fil};
    int** s[5] = {sl, sc, sr, fil, fil};
    int** m[5] = {ml, mc, mr, fil, fil};

    //these six are grouped into the master array "moves"
    //this array contains every possible need set of 5 sets of 4 tiles to manipulate any face

    int*** moves[9] = {f, r, l, b, d, u, e, s, m};

    if(mov <= 8) //handles simple moves
    {
        manip(moves[mov], dir);
        //manip called using the desired face as well as direction
    }
    else //does double slice moves
    {
        int inversdir; //finds the inverted move for when the opposite moves are called

        manip(moves[mov - 10], dir);

        //calls manip by subtraction 10 to get the original move
        //double slice turn consists of 2 turns, one regular face and one center slice

        if(dir == 0)
        {
            inversdir = 1;
        }
        else if(dir == 1)
        {
            inversdir = 0;
        }
        else if(dir == 2)
        {
            inversdir = 2;
        }

        //inverse direction needed to determine the proper way to turn the center slice
        //a turning the top clock wise would turn the center clockwise while turning the bottom
        //clockwise would turn the middle counter clockwise relative to the top

        //proper corresponding move and direction are called based on the double layer turn
        switch(mov)
        {
        case 10:
            manip(moves[7], dir);
            break;
        case 13:
            manip(moves[7], inversdir);
            break;
        case 11:
            manip(moves[8], inversdir);
            break;
        case 12:
            manip(moves[8], dir);
            break;
        case 14:
            manip(moves[6], inversdir);
            break;
        case 15:
            manip(moves[6], dir);
            break;
        }
    }
}

void CubeState::manip(int** tiles[4], int dir)
{
    //takes one element of the master array of all moves
    //this element contains 5 groups of 4 tiles that need to be manipulated
    //each element is called using the passed in direction

    for(int i = 0; i < 5; i++)
    {
        turn(tiles[i], dir);
    }
}

void CubeState::turn(int* tiles[4], int dir)
{
    //used when swapping around values
    int temp;

    /*
    dir is an int that can be 0, 1 or 2

    0 swaps forward:
    1234
    4123

    1 swaps backwards:
    1234
    2341

    2 swaps adjacent:
    1234
    3412

    */

    if(dir == 0)
    {
        temp = *tiles[3]; //the last value is saved
        for(int i = 3; i > 0; i--)
        {
            *tiles[i] = *tiles[i - 1]; //values are shifted forward on the the last value
        }

        *tiles[0] = temp; //the first value is filled
    }
    else if(dir == 1)
    {
        //same as above but in reverse order
        temp = *tiles[0];
        for(int i = 0; i < 3; i++)
        {
            *tiles[i] = *tiles[i + 1];
        }
        *tiles[3] = temp;
    }
    else if(dir == 2)
    {
        //adjacent swap uses 2 value flip flops
        temp = *tiles[0];
        *tiles[0] = *tiles[2];
        *tiles[2] = temp;

        temp = *tiles[1];
        *tiles[1] = *tiles[3];
        *tiles[3] = temp;
    }
}

int* CubeState::solvedCube(void)
{
    //creates and returns an array that would represent a solved rubik's cube

    int *cube;
    cube = new int[54]; //the cube is created and initialized

    for(int i = 0; i < 9; i++) //first 9 tiles are a certain colour
    {
        cube[i] = 2;
    }
    for(int i = 45; i < 54; i++) //last 9 tiles are a certain colour
    {
        cube[i] = 1;
    }

    int i = 0;
    int col[4] = {4,5,3,6}; //order colours should be used

    for(int j = 9; j < 19; j += 3) //iterates onto the top left corner of each of the 4 faces
    {
        for(int k = j; k < j + 25; k+=12) //proceeds to fill them with a value
        {
            int c = col[i];
            cube[k] = c;
            cube[k + 1] = c;
            cube[k + 2] = c;
        }
        //diagram can be found in the console output file
        i++;
        //moves onto next colour
    }
    return cube;
}
