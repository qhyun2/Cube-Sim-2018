//Assignment 2 Question **
//(c) Mr. Yun
// *****************
#include <iostream>

using namespace std;

int main()
{


    do //input loop
    {
        cout << "***" << endl; //user interface for retrieving numbers from user
        cin >> ***;

        if(cin.fail()) //test to see if input is valid
        {
            cout << "Invalid Input Try Harder" << endl; //if not, the program criticizes user
            cin.clear(); //clears stuff up
            cin.ignore(10000,'\n'); //skips the the current characters
        }
        else break; //if no issues it breaks out loop
    }
    while (true); //loops infinitely

    return 0;
}
#include "Test.h"

Test::Test()
{
    //ctor
}

Test::~Test()
{
    //dtor
}
