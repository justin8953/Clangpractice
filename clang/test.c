#include "sold.h"

/*-------------*/
/*- function -*/
/*-----------*/

bool test_jump_up(char bd[HEIGHT][WIDTH],int i, int j)
{
    if(jump_up_Isvalid(bd, i, j))
    {
        bd[i][j]=EMPTY;
        bd[i-1][j]=EMPTY;
        bd[i-2][j]=PEG;
        return true;
    }
    return false;
}
bool test_jump_right(char bd[HEIGHT][WIDTH],int i, int j)
{
    if(jump_right_Isvalid(bd, i, j))
    {
        bd[i][j]=EMPTY;
        bd[i][j+1]=EMPTY;
        bd[i][j+2]=PEG;
        return true;
    }
    return false;
}
bool test_jump_left(char bd[HEIGHT][WIDTH],int i, int j)
{
    if(jump_left_Isvalid(bd, i, j))
    {
        bd[i][j]=EMPTY;
        bd[i][j-1]=EMPTY;
        bd[i][j-2]=PEG;
        return true;
    }
    return false;
}

void test_all()
{
    char bd[HEIGHT][WIDTH];
    Initialiseboard(bd);
    assert(test_jump_up(bd, 5, 1)==true);
    assert(test_jump_up(bd, 5, 2)==true);
    assert(test_jump_right(bd, 3, 1)==true);
    assert(test_jump_left(bd,4,4)==true);
}
