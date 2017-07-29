#ifndef HAO_H_INCLUDED
#define HAO_H_INCLUDED

using namespace std;

int getInt(string question)
{
    int num; //variable for storing input
    do //input loop
    {
        cout << question << endl; //user interface for retrieving numbers from user
        cin >> num;

        if(cin.fail()) //test to see if input is valid
        {
            cout << "Invalid Input Try Harder" << endl; //if not, the program criticizes user
            cin.clear(); //clears buffer
            cin.ignore(10000,'\n'); //skips the the current characters
        }
        else
        {
            cin.clear(); //clears buffer
            cin.ignore(10000,'\n'); //skips the the current characters
            break; //if no issues it breaks out loop
        }
    }
    while (true); //loops infinitely

    return num;
}

int getInt(string question, int lower, int upper) //function for getting input with ranges
{
    int num; //variable for storing input
    do //input loop
    {
        cout << question << endl; //user interface for retrieving numbers from user
        cin >> num;
        cin.clear(); //clears stuff up
        cin.ignore(10000,'\n'); //skips the the current characters

        if(cin.fail() || num > upper || num < lower) //test to see if input is valid
        {
            cout << "Invalid Input Try Harder" << endl; //if not, the program criticizes user
            cin.clear(); //clears stuff up
            cin.ignore(10000,'\n'); //skips the the current characters
        }
        else break; //if no issues it breaks out loop
    }
    while (true); //loops infinitely

    return num;
}

string getString(string question) //function for getting input with ranges
{
    string st; //variable for storing input
    cout << question << endl; //user interface for retrieving numbers from user
    getline(cin, st);
    return st;
}

string changeCase(string st, bool cas)
{
    for(int i = 0; i < st.length(); i++)
    {
        if(cas)
        {
            st[i] = toupper(st[i]);
        }
        else
        {
            st[i] = tolower(st[i]);
        }
    }
    return st;
}

#endif // HAO_H_INCLUDED
