#include "sold.h"

int main(int argc, char **argv)
{
    static BOARDLIST s;
    int x_end, y_end;
    test_all();
    InitialiseboardList(&s);
    if (argc == 3)
    {
        /*User First input number */
        x_end = CharToInt(*argv[1]);
        /*User Second input number */
        y_end = CharToInt(*argv[2]);
        if(!check_has_solution(&s, x_end,y_end)){
            printf("It exceeds memory maximum size. No solution \n");
        }
    }
    else
    {
        printf("Please type 2 variable (x, y) \n");
    }
    
    return 1;

}

/*-------------*/
/*- function -*/
/*-----------*/


/* Casting character to integer */

int CharToInt(char before)
{
    int after;
    after = (int)before - '0';
    return after;
}

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
    copy_array(board,s->bdlist[s->count].bd);
    s->bdlist[s->count].parent = 0;
}

/* ---------------------------------------------------------  */

/* start game */
int start_game(BOARDLIST *s, int x_end, int y_end)
{
    int num_cell;
    char tmp_board[HEIGHT][WIDTH];
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
        check_each_cell(s,tmp_board,num_cell);
        num_cell ++;
    }while(num_cell!=0 && s->count<MAX);
    return false;
}

/* check the location user want to reach has solution and doesn't exceed memory size*/
bool check_has_solution(BOARDLIST*s, int x_end, int y_end)
{
    int num;
    if((num = start_game(s, x_end,y_end)))
    {
        print_parent(s,num);
        return true;
    }
    return false;
}

/* check each cell. if it can be available to jump, it does jump*/
void check_each_cell(BOARDLIST *s, char tmp_board[HEIGHT][WIDTH], int num_cell)
{
    int i, j;
    for(i = 0; i<HEIGHT; i++)
    {
        for(j = 0;j<WIDTH; j++)
        {
            if (s->bdlist[num_cell].bd[i][j]==PEG)
            {
                if(jump_up_Isvalid(s->bdlist[num_cell].bd, i, j))
                {
                    jump_up(tmp_board,i,j,num_cell, s);
                }
                if(jump_right_Isvalid(s->bdlist[num_cell].bd, i, j))
                {
                    jump_right(tmp_board,i,j,num_cell, s);
                }
                if(jump_left_Isvalid(s->bdlist[num_cell].bd, i, j))
                {
                    jump_left(tmp_board,i,j,num_cell, s);
                }
            }
        }
    }
}

/* Jump function: if tile can jump, copy origin board to 
tempory board. Then,  change the board and copy to new board 
*/

void jump_up(char tmp_board[HEIGHT][WIDTH], int i, int j,int num_cell, BOARDLIST *s)
{
    copy_array(s->bdlist[num_cell].bd, tmp_board);
    s->count++;
    s->bdlist[s->count].parent = num_cell;
    tmp_board[i][j]=EMPTY;
    tmp_board[i-1][j]=EMPTY;
    tmp_board[i-2][j]=PEG;
    copy_array(tmp_board,s->bdlist[s->count].bd);    
}

void jump_left (char tmp_board[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s)
{
    copy_array(s->bdlist[num_cell].bd, tmp_board);
    s->count++;
    s->bdlist[s->count].parent = num_cell;
    tmp_board[i][j]=EMPTY;
    tmp_board[i][j-1]=EMPTY;
    tmp_board[i][j-2]=PEG;
    copy_array(tmp_board,s->bdlist[s->count].bd);
}
void jump_right (char tmp_board[HEIGHT][WIDTH], int i, int j, int num_cell, BOARDLIST *s)
{
    copy_array(s->bdlist[num_cell].bd, tmp_board);
    s->count++;
    s->bdlist[s->count].parent = num_cell;
    tmp_board[i][j]=EMPTY;
    tmp_board[i][j+1]=EMPTY;
    tmp_board[i][j+2]=PEG;
    copy_array(tmp_board,s->bdlist[s->count].bd);
}

/* check that the peg can be avaliable to move  */
bool jump_up_Isvalid(char bd[HEIGHT][WIDTH], int i, int j)
{
    if (bd[i-1][j]==PEG&& bd[i-2][j]==EMPTY&&(i-2)>0)
    {
        return true;
    }
    return false;
}

bool jump_left_Isvalid(char bd[HEIGHT][WIDTH], int i, int j)
{
    if (bd[i][j-1]==PEG&& bd[i][j-2]==EMPTY&&(j-2)>0)
    {
        return true;
    }
    return false;
}
bool jump_right_Isvalid(char bd[HEIGHT][WIDTH], int i, int j)
{
    if (bd[i][j+1]==PEG&& bd[i][j+2]==EMPTY&&(j+2)<WIDTH)
    {
        return true;
    }
    return false;
}

/* ---------------------------------------------------------  */

void copy_array(char bd1[HEIGHT][WIDTH],char bd2[HEIGHT][WIDTH])
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
