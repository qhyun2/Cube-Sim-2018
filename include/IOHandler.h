#ifndef IOHANDLER_H
#define IOHANDLER_H
#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;

class IOHandler
{
public:
    IOHandler();
    virtual ~IOHandler();
    int type(char turn); //takes a string the represents a desired move and returns an int corresponding to the face that will be turned
    int suffix(char turn); //takes in a string and finds the suffix of the move (clockwise, counter...), and returns a corresponding int
    vector <string> partion(string moves); //partition a string into respective
    void runIntro(void); //run intro
    void runHelp(void); //runs help
    void runCredits(void); //runs credits
    bool saveFile(string name, int* values); //saves state
    bool loadFile(string name, int* tiles); //loads state
protected:
private:
};

#endif // IOHANDLER_H
