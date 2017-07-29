#include "ConsoleOutput.h"

using namespace std;

ConsoleOutput::ConsoleOutput()
{
    //ctor
}

ConsoleOutput::~ConsoleOutput()
{
    //dtor
}

void ConsoleOutput::printRow(WORD colour, HANDLE hstdout)//prints 3 tiles of a colour followed by a blackspace
{
    SetConsoleTextAttribute(hstdout, colour); //sets specified colour
    cout << "   "; //prints 3 long
    SetConsoleTextAttribute(hstdout, 0x0f); //prints a black space after
    cout << " ";
}

void ConsoleOutput::printBlank(int num, HANDLE hstdout)
{
    SetConsoleTextAttribute(hstdout, 0x0f); //set colour to black
    for(int i = 0; i < num; i++) //prints desired amount of spaces
    {
        cout << " ";
    }
}

void ConsoleOutput::printTile(WORD first, WORD second, WORD third, int space, HANDLE hstdout)//prints 2 rows of 3 tiles with 3 specified colours
{
    printBlank(space, hstdout); //prints specified amount of space
    printRow(first, hstdout); //then the 3 tiles
    printRow(second, hstdout);
    printRow(third, hstdout);
    cout << endl; //then newline
    printBlank(space, hstdout); //does it again for 2 high tiles
    printRow(first, hstdout);
    printRow(second, hstdout);
    printRow(third, hstdout);
    cout << endl;
}

void ConsoleOutput::print(int tiles[54], HANDLE hstdout)
{
    const WORD colours[] = {0x88, 0xFF, 0xEE, 0xCC, 0xDD, 0x99, 0x22, 0x00};
    /*
    Looks up for colours and their corresponding hex code
    each element. Individual colours are accessed later on form this array

    Colours:
    0 - Grey (Invalid / Missing / Irrelevant)
    1 - White
    2 - Yellow
    3 - Red
    4 - Orange (No orange, magenta used as sub)
    5 - Blue
    6 - Green

    Display:
                  ### ### ###   display is 3 wide and 2 high tiles
                  ### ### ###   3 of them x 8 pixels wide = 24 pixels
                                2 of them x 12 pixels high = 24 pixels
                  ### ### ###   resulting in square looking tiles when using a 8 x 12 (default) raster font
                  ### ### ###

                  ### ### ###   Individual Character layout on screen
                  ### ### ###

    ### ### ###   ### ### ###   ### ### ###   ### ### ###
    ### ### ###   ### ### ###   ### ### ###   ### ### ###

    ### ### ###   ### ### ###   ### ### ###   ### ### ###
    ### ### ###   ### ### ###   ### ### ###   ### ### ###

    ### ### ###   ### ### ###   ### ### ###   ### ### ###
    ### ### ###   ### ### ###   ### ### ###   ### ### ###

                  ### ### ###
                  ### ### ###

                  ### ### ###
                  ### ### ###

                  ### ### ###
                  ### ### ###

    Layout:
              0  1  2
              3  4  5   Planned locations
              6  7  8

    9  10 11  12 13 14  15 16 17  18 19 20
    21 22 23  24 25 26  27 28 29  30 31 32
    33 34 35  36 37 38  39 40 41  42 43 44

              45 46 47
              48 49 50
              51 52 53

                top      Theoretical directions


     left      front     right    back


               bottom

    colours[tiles[0]]
    colours is the array of colours from 0 - 6
    tiles is the array of all tiles of the cube
    each tiles element holds an int value that is used to determine which colour to display

    ex.

    int whichColour = tiles[whichtileisprinting]

    colours[whichColour] would get the corresponding WORD for the desired colour of that tile

    */
    printTile(colours[tiles[0]],colours[tiles[1]],colours[tiles[2]], 18, hstdout); //prints out first square top part
    cout << endl;
    printTile(colours[tiles[3]],colours[tiles[4]],colours[tiles[5]], 18, hstdout);
    cout << endl;
    printTile(colours[tiles[6]],colours[tiles[7]],colours[tiles[8]], 18, hstdout);
    cout << endl;

    for(int k = 9; k < 45; k += 12)
    {
        for(int j = 0; j < 2; j++) //iterates inside code twice for 2 high tiles
        {
            printBlank(5, hstdout); //5 spaces for alignment
            for(int i = k; i < k + 12; i+=3)//iterates 4 times, once for each group of 9 tiles
                //i starts as the first number at the start of the row as determined by k
                //increments of 3 means i will skip to the start of each block of squares
            {
                printRow(colours[tiles[i]], hstdout); //prints the 3 corresponding tiles to the current i value
                printRow(colours[tiles[i + 1]], hstdout);
                printRow(colours[tiles[i + 2]], hstdout);
                cout << " "; //adds separating space at the end
                //(the whole point of printing in batches of 3 is to make the separating space easier to fit in)
            }
            cout << endl; //a new line is start for second row
            //keep in mind a new line is made even when it is the second row
        }
        cout << endl; //so only 1 new line is need to produce a blank line
    }

    printTile(colours[tiles[45]],colours[tiles[46]],colours[tiles[47]], 18, hstdout); //prints out bottom square same as the top square
    cout << endl;
    printTile(colours[tiles[48]],colours[tiles[49]],colours[tiles[50]], 18, hstdout);
    cout << endl;
    printTile(colours[tiles[51]],colours[tiles[52]],colours[tiles[53]], 18, hstdout);
    cout << endl;
}
