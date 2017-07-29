#ifndef CUBESTATE_H
#define CUBESTATE_H

class CubeState
{
public:
    CubeState();
    virtual ~CubeState();

    //tiles getter and setter
    int* Gettiles()
    {
        return tiles;
    }
    void Settiles(int* val)
    {
        tiles = val;
    }

    int callManip(int mov, int dir); //calls manip with proper moves
    int* solvedCube(void); //returns a solved cube array
protected:
private:
    int* tiles;
    void turn(int* tiles[4], int dir); //takes an array of 4 pointers and swaps them around based on second int variable
    void manip(int** tiles[4], int dir); //takes an array of pointer arrays and calls turn using the int passed in for each element of the array
};

#endif // CUBESTATE_H
