#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define MAX 3499999
#define WIDTH 7
#define HEIGHT 8
#define EMPTY '.'
#define PEG '*'

/* A structure which contains one 2D board and its parent number */
struct boardselem
{
    char bd[HEIGHT][WIDTH];
    int parent;
};
typedef struct boardselem Elem;

/* Big 1D array's board which stores each 2D board and the count store every 2D board index */
struct boardlist
{
    Elem bdlist[MAX];
    int count;
};
typedef struct boardlist BOARDLIST;

/* -----------------------------------------------------------------------------------------------------  */
/* Declaration */

/* star the game, and if the function finds the solution, it will return the final board's parent number' */
int start(BOARDLIST *s, int x_end, int y_end);
/*
chech each cell in 2D board. if cell can jump, then add a new board and copy origin board into new board, 
moving the cell in the new board
*/
void check_each_cell(BOARDLIST *s, char tmp[HEIGHT][WIDTH], int num_cell);

/* jump function */
void jump_up (char tmp[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s);
void jump_left (char tmp[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s);
void jump_right (char tmp[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s);

/* check that the peg can be avaliable to move  */
int jump_up_valid(char bd[HEIGHT][WIDTH], int i, int j);
int jump_right_valid(char bd[HEIGHT][WIDTH], int i, int j);
int jump_left_valid(char bd[HEIGHT][WIDTH], int i, int j);

/* print the solution  */
void print_parent(BOARDLIST *s, int parent_num);

/* Initialise the 2D board */
void Initialiseboard(char bd[HEIGHT][WIDTH]);
/* Initialise the 1D big board */
void InitialiseboardList(BOARDLIST *s);

void print_array(char bd[HEIGHT][WIDTH]);
/* copy board */
void copy(char bd1[HEIGHT][WIDTH], char bd2[HEIGHT][WIDTH]);
/* testing function */
void test_all();
int test_start();
int test_jump_left(char bd[HEIGHT][WIDTH],int i, int j);
int test_jump_right(char bd[HEIGHT][WIDTH],int i, int j);
int test_jump_left(char bd[HEIGHT][WIDTH],int i, int j);

/* -----------------------------------------------------------------------------------------------------  */

int main(void)
{
    static BOARDLIST s;
    int x_end, y_end, num;
    test_all();
    InitialiseboardList(&s);
    printf("Please input the location (col,row) you want to reach \n");
    scanf("%d %d", &x_end,&y_end);
    if((num =start(&s, x_end,y_end))==0)
    {
        printf("It exceeds memory maximum size. No solution \n");
    }
    else
    {
        print_parent(&s,num);
    }
    return 1;

}
/* -----------------------------------------------------------------------------------------------------  */

/* Initialised function */

/*set up first board*/
void Initialiseboard(char bd[HEIGHT][WIDTH])
{
	int i, j;
	for (i = 0; i<HEIGHT/2; i++)
	{
		for (j = 0; j<WIDTH; j++)
		{
			bd[i][j] = EMPTY;
		}
	}
	for (i = HEIGHT/2 ; i< HEIGHT; i++)
	{
		for(j = 0; j< WIDTH; j++)
		{
			bd[i][j]= PEG;
		}
	}
}

/*store the initilised board into  Big board 1st address  */
void InitialiseboardList(BOARDLIST *s)
{
    char board[HEIGHT][WIDTH]; 
	s->count = 0;
    Initialiseboard(board);
    copy(board,s->bdlist[s->count].bd);
    s->bdlist[s->count].parent = 0;
}

/* -----------------------------------------------------------------------------------------------------  */
/* start game */
int start(BOARDLIST *s, int x_end, int y_end)
{
    int num_cell;
    char tmp[HEIGHT][WIDTH];
    /* check the 2D board that is available to jump from the first cell in boardlist */
    num_cell = s->count;
    do
    {
        /* if 2D board reach the goal, it return its parent */
        if (s->bdlist[num_cell].bd[y_end][x_end]==PEG)
        {
            printf("reach\n");
            print_array(s->bdlist[num_cell].bd);
            return s->bdlist[num_cell].parent;
        }
        /* check each cell in the 2D board  */
        check_each_cell(s,tmp,num_cell);
        num_cell ++;
    }while(num_cell!=0 && s->count<MAX);
    return 0;
}
/* check each cell. if it can be available to jump, it does jump*/
void check_each_cell(BOARDLIST *s, char tmp[HEIGHT][WIDTH], int num_cell)
{
    int i, j;
    for(i = 0; i<HEIGHT; i++)
    {
        for(j = 0;j<WIDTH; j++)
        {
            if (s->bdlist[num_cell].bd[i][j]==PEG)
            {
                if(jump_up_valid(s->bdlist[num_cell].bd, i, j))
                {
                    jump_up(tmp,i,j,num_cell, s);
                }
                if(jump_right_valid(s->bdlist[num_cell].bd, i, j))
                {
                    jump_right(tmp,i,j,num_cell, s);
                }
                if(jump_left_valid(s->bdlist[num_cell].bd, i, j))
                {
                    jump_left(tmp,i,j,num_cell, s);
                }
            }
        }
    }
}
/* Jump function: if tile can jump, copy origin board to tempory board. Then,  change the board and copy to new board */
void jump_up (char tmp[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s)
{
    copy(s->bdlist[num_cell].bd, tmp);
    s->count++;
    s->bdlist[s->count].parent = num_cell;
    tmp[i][j]=EMPTY;
    tmp[i-1][j]=EMPTY;
    tmp[i-2][j]=PEG;
    copy(tmp,s->bdlist[s->count].bd);    
}
void jump_left (char tmp[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s)
{
    copy(s->bdlist[num_cell].bd, tmp);
    s->count++;
    s->bdlist[s->count].parent = num_cell;
    tmp[i][j]=EMPTY;
    tmp[i][j-1]=EMPTY;
    tmp[i][j-2]=PEG;
    copy(tmp,s->bdlist[s->count].bd);
}
void jump_right (char tmp[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s)
{
    copy(s->bdlist[num_cell].bd, tmp);
    s->count++;
    s->bdlist[s->count].parent = num_cell;
    tmp[i][j]=EMPTY;
    tmp[i][j+1]=EMPTY;
    tmp[i][j+2]=PEG;
    copy(tmp,s->bdlist[s->count].bd);
}

/* check that the peg can be avaliable to move  */
int jump_up_valid(char bd[HEIGHT][WIDTH], int i, int j)
{
    if (bd[i-1][j]==PEG&& bd[i-2][j]==EMPTY&&(i-2)>0)
    {
        return 1;
    }
    return 0;
}
int jump_left_valid(char bd[HEIGHT][WIDTH], int i, int j)
{
    if (bd[i][j-1]==PEG&& bd[i][j-2]==EMPTY&&(j-2)>0)
    {
        return 1;
    }
    return 0;
}
int jump_right_valid(char bd[HEIGHT][WIDTH], int i, int j)
{
    if (bd[i][j+1]==PEG&& bd[i][j+2]==EMPTY&&(j+2)<WIDTH)
    {
        return 1;
    }
    return 0;
}

/* -----------------------------------------------------------------------------------------------------  */
/* copy array */
void copy(char bd1[HEIGHT][WIDTH],char bd2[HEIGHT][WIDTH])
{
	int i, j;
	for (i = 0; i<HEIGHT; i++)
	{
		for (j = 0; j<WIDTH; j++)
		{
			bd2[i][j] = bd1[i][j];
		}
	}	
}
/* print array */
void print_array(char bd[HEIGHT][WIDTH])
{
	int i, j;
	for (i = 0; i<HEIGHT; i++)
	{
		for (j = 0; j<WIDTH; j++)
		{
			printf("%c", bd[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* print the solution  */
void print_parent(BOARDLIST *s, int parent_num)
{
    do{
        print_array(s->bdlist[parent_num].bd);
        parent_num = s->bdlist[parent_num].parent;
    }while(parent_num != 0);
}
