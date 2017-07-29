#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H
#include <iostream>
#include <windows.h>

class ConsoleOutput
{
public:
    ConsoleOutput();
    virtual ~ConsoleOutput();
    void print(int tile[54], HANDLE hstdout); //prints the whole net using an int array with the colour values
protected:
private:
    void printRow(WORD colour, HANDLE hstdout); //prints 3 tiles of a colour followed by a backspace
    void printTile(WORD first, WORD second, WORD third, int space, HANDLE hstdout); //prints 2 rows of 3 tiles with 3 specified colours
    void printBlank(int num, HANDLE hstdout); //prints specified amount of blank spaces
};

#endif // CONSOLEOUTPUT_H
