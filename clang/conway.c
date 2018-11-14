#include<stdio.h>
#include<assert.h>
#include<time.h>
#define MAX 1000000000
#define WIDTH 7
#define HEIGHT 8
#define EMPTY '.'
#define PEG '*'

struct boardselem
{
	char bd[HEIGHT][WIDTH];
	int parent;
};
typedef struct boardselem Elem;

/* Big 1D Board which stores each 2D board */
struct boardlist
{
	Elem bdlist[MAX];
	int count;
};
typedef struct boardlist BOARDLIST;



/* check that the peg can be avaliable to move  */
int jump_up_valid(char bd[HEIGHT][WIDTH], int i, int j);
int jump_right_valid(char bd[HEIGHT][WIDTH], int i, int j);
int jump_left_valid(char bd[HEIGHT][WIDTH], int i, int j);

/* print the solution  */
void print_parent(BOARDLIST *s, int parent_num);

void print_array(char bd[HEIGHT][WIDTH]);
/* Initialise the 2D board */
void Initialiseboard(char bd[HEIGHT][WIDTH]);
/* Initialise the 1D big board */
void InitialiseboardList(BOARDLIST *s);
/* copy board */
void copy(char bd1[HEIGHT][WIDTH], char bd2[HEIGHT][WIDTH]);
int start(BOARDLIST *s, int x_end, int y_end);

int main(void)
{
    static BOARDLIST s;
    int x_end, y_end, num;
    InitialiseboardList(&s);
    x_end= 3;
    y_end =1;
    num =start(&s, x_end,y_end);
    printf("%d \n", num);
    print_parent(&s,num);
    return 1;

}




/*------------------------------------------------------------- */
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

/*------------------------------------------------------------- */

int start(BOARDLIST *s, int x_end, int y_end)
{
    int num_cell, i, j;
    char tmp[HEIGHT][WIDTH];
    /* check the 2D board that is available to jump from the first cell in boardlist */
    num_cell = s->count;
    do
    {
        /* if 2D board reach the goal, it return its parent */
        if (s->bdlist[num_cell].bd[y_end][x_end]==PEG)
        {
            printf("reach\n");
            printf("count is %d ", s->count);
            print_array(s->bdlist[num_cell].bd);
            return s->bdlist[num_cell].parent;
        }
        /* check each cell in the 2D board  */
        for(i = 0; i<HEIGHT; i++)
        {
            for(j = 0;j<WIDTH; j++)
            {
                if (s->bdlist[num_cell].bd[i][j]==PEG)
                {
                    if(jump_up_valid(s->bdlist[num_cell].bd, i, j))
                    {
                        copy(s->bdlist[num_cell].bd, tmp);
                        s->count++;
                        s->bdlist[s->count].parent = num_cell;
                        tmp[i][j]=EMPTY;
                        tmp[i-1][j]=EMPTY;
                        tmp[i-2][j]=PEG;
                        copy(tmp,s->bdlist[s->count].bd);
                    }
                    if(jump_right_valid(s->bdlist[num_cell].bd, i, j))
                    {
                        copy(s->bdlist[num_cell].bd, tmp);
                        s->count++;
                        s->bdlist[s->count].parent = num_cell;
                        tmp[i][j]=EMPTY;
                        tmp[i][j+1]=EMPTY;
                        tmp[i][j+2]=PEG;
                        copy(tmp,s->bdlist[s->count].bd);
                    }
                    if(jump_left_valid(s->bdlist[num_cell].bd, i, j))
                    {
                        copy(s->bdlist[num_cell].bd, tmp);
                        s->count++;
                        s->bdlist[s->count].parent = num_cell;
                        tmp[i][j]=EMPTY;
                        tmp[i][j-1]=EMPTY;
                        tmp[i][j-2]=PEG;
                        copy(tmp,s->bdlist[s->count].bd);
                    }

                }
            }
        }
        num_cell ++;
    }while(num_cell!=0);
    return 0;
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

/*------------------------------------------------------------- */
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
