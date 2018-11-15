#include<stdio.h>
#include<assert.h>
#define MAX 3499999
#define WIDTH 7
#define HEIGHT 8
#define EMPTY '.'
#define PEG '*'


/* Declaration */

/* check that the peg can be avaliable to move  */
int jump_up_valid(char bd[HEIGHT][WIDTH], int i, int j);
int jump_right_valid(char bd[HEIGHT][WIDTH], int i, int j);
int jump_left_valid(char bd[HEIGHT][WIDTH], int i, int j);
void Initialiseboard(char bd[HEIGHT][WIDTH]);
void test_all();
/* testing : tile can jump  */
int test_jump_up(char bd[HEIGHT][WIDTH],int i, int j);
int test_jump_right(char bd[HEIGHT][WIDTH],int i, int j);
int test_jump_left(char bd[HEIGHT][WIDTH],int i, int j);

/* -----------------------------------------------------------------------------------------------------  */

/* Function */
int test_jump_up(char bd[HEIGHT][WIDTH],int i, int j)
{
    if(jump_up_valid(bd, i, j))
    {
        bd[i][j]=EMPTY;
        bd[i-1][j]=EMPTY;
        bd[i-2][j]=PEG;
        return 1;
    }
    return 0;
}
int test_jump_right(char bd[HEIGHT][WIDTH],int i, int j)
{
    if(jump_right_valid(bd, i, j))
    {
        bd[i][j]=EMPTY;
        bd[i][j+1]=EMPTY;
        bd[i][j+2]=PEG;
        return 1;
    }
    return 0;
}
int test_jump_left(char bd[HEIGHT][WIDTH],int i, int j)
{
    if(jump_left_valid(bd, i, j))
    {
        bd[i][j]=EMPTY;
        bd[i][j-1]=EMPTY;
        bd[i][j-2]=PEG;
        return 1;
    }
    return 0;
}

void test_all()
{
    char bd[HEIGHT][WIDTH];
    Initialiseboard(bd);
    assert(test_jump_up(bd, 5, 1)==1);
    assert(test_jump_up(bd, 5, 2)==1);
    assert(test_jump_right(bd, 3, 1)==1);
    assert(test_jump_left(bd,4,4)==1);
}
