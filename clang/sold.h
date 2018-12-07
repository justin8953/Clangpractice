#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define MAX 3499999
#define WIDTH 7
#define HEIGHT 8
#define EMPTY '.'
#define PEG '*'
#define MAXUSERINPUT 3

enum bool {false, true};
typedef enum bool bool;

/* Create a structure which contains one 2D board and its parent number */
struct boardelem
{
    char bd[HEIGHT][WIDTH];
    int parent;
};
typedef struct boardelem Elem;

/* Create a nested sturcture which is 1D array which stores each 2D board, and structure also has a counter stores every 2D board index */
struct boardlist
{
    Elem bdlist[MAX];
    int count;
};
typedef struct boardlist BOARDLIST;

/*----------------*/
/*- Declaration -*/
/*--------------*/

/* Casting command line input to integer */
int CharToInt(char before);

/*------------------------*/
/*- Initialisd function -*/
/*----------------------*/

/* Initialise the 2D board */
void Initialiseboard(char bd[HEIGHT][WIDTH]);
/* Initialise the 1D big board */
void InitialiseboardList(BOARDLIST *s);

/*------------------------*/
/*- Board game function -*/
/*----------------------*/

int start_game(BOARDLIST *s, int x_end, int y_end);
bool check_has_solution(BOARDLIST*s, int x_end, int y_end);

/*
Check each cell in 2D board. If cell can jump, 
then create a new board and copy origin board into new board, 
moving the cell in the new board
*/

void check_each_cell(BOARDLIST *s, char tmp_board[HEIGHT][WIDTH], int num_cell);

/* Jump Function */
void jump_up (char tmp_board[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s);
void jump_left (char tmp_board[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s);
void jump_right (char tmp_board[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s);

/* Check the peg can be avaliable to move */
bool jump_up_Isvalid(char bd[HEIGHT][WIDTH], int i, int j);
bool jump_right_Isvalid(char bd[HEIGHT][WIDTH], int i, int j);
bool jump_left_Isvalid(char bd[HEIGHT][WIDTH], int i, int j);

/* Print the solution  */
void print_parent(BOARDLIST *s, int parent_num);

void print_array(char bd[HEIGHT][WIDTH]);
void copy_array(char bd1[HEIGHT][WIDTH], char bd2[HEIGHT][WIDTH]);

/*---------------------*/
/*- Testing function -*/
/*-------------------*/
void test_all();
bool test_jump_left(char bd[HEIGHT][WIDTH],int i, int j);
bool test_jump_right(char bd[HEIGHT][WIDTH],int i, int j);
bool test_jump_left(char bd[HEIGHT][WIDTH],int i, int j);
