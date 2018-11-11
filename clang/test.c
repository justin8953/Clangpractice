#include<stdio.h>
#include<assert.h>
#include<time.h>
#define TOTAL_SIZE 1000
#define SINGLE_WIDTH 3
#define SINGLE_HEIGHT 4

/* 2D Board with its parent number*/
struct single_board
{
	char board[SINGLE_HEIGHT][SINGLE_WIDTH];
	int parent;
};
typedef struct single_board SINGLEBOARD;

/* Big 1D Board which stores each 2D board */
struct board_list
{
	SINGLEBOARD boards[TOTAL_SIZE];
	int count;
};
typedef struct board_list BOARDLIST;


void Delay(unsigned int secs);
void print_array(char board[SINGLE_HEIGHT][SINGLE_WIDTH]);
void Initialiseboard(char board[SINGLE_HEIGHT][SINGLE_WIDTH]);
void InitialiseboardList(BOARDLIST *s);
void copy(char board[SINGLE_HEIGHT][SINGLE_WIDTH],char tmp[SINGLE_HEIGHT][SINGLE_WIDTH]);
int game_start (BOARDLIST *s, int p, int q);

/*Test jump function */
void test_jump ();
int jump_up (char board[SINGLE_HEIGHT][SINGLE_WIDTH], int i, int j);
int jump_left (char board[SINGLE_HEIGHT][SINGLE_WIDTH], int i, int j);
int jump_right (char board[SINGLE_HEIGHT][SINGLE_WIDTH], int i, int j);

int main(void)
{
    test_jump();
	
}

int game_start (BOARDLIST *s, int p, int q)
{
	int i, j;
	char tmp[SINGLE_HEIGHT][SINGLE_WIDTH];
	/* reach the location of user inputs */
	if (s->boards[s->count].board[p][q]=='*')
	{
		printf("Sucess \n");
		return 1;
	}
	copy(s->boards[s->count].board,tmp);
	for (i=0; i<SINGLE_HEIGHT; i++)
	{
		for(j = 0; j<SINGLE_WIDTH; j++ )
		{
			if(tmp[i][j]=='*')
			{
				/* if the tile jumps, put the 2d array into next address in big board  */
				if (tmp[i-1][j]=='*'&& tmp[i-2][j]=='.'&& (i-1)>=0)
				{
					s->count++;
					s->boards[s->count].parent = s->count;
					tmp [i][j]='.';
					tmp[i-1][j]= '.';
					tmp[i-2][j]= '*';
					copy(tmp,s->boards[s->count].board);
					game_start(s, p, q);
				}
				if(tmp[i][j+1]=='*'&& tmp[i][j+2]=='.')
				{
					s->count++;
					s->boards[s->count].parent = s->count;
					tmp [i][j]='.';
					tmp[i][j+1]= '.';
					tmp[i][j+2]= '*';
					copy(tmp,s->boards[s->count].board);
					game_start(s, p, q);
				}
				if(tmp[i][j-1]=='*'&& tmp[i][j-2]=='.'&& (j-1)>0)
				{
					s->count++;
					s->boards[s->count].parent = s->count;
					tmp [i][j]='.';
					tmp[i][j-1]= '.';
					tmp[i][j-2]= '*';
					copy(tmp,s->boards[s->count].board);
					game_start(s, p, q);
				}
			}
		}
	}
	return 0 ;
}

/* copy array */
void copy(char board[SINGLE_HEIGHT][SINGLE_WIDTH],char tmp[SINGLE_HEIGHT][SINGLE_WIDTH])
{
	int i, j;
	for (i = 0; i<SINGLE_HEIGHT; i++)
	{
		for (j = 0; j<SINGLE_WIDTH; j++)
		{
			tmp[i][j] = board[i][j];
		}
	}	
}
/* print array */
void print_array(char board[SINGLE_HEIGHT][SINGLE_WIDTH])
{
	int i, j;
	for (i = 0; i<SINGLE_HEIGHT; i++)
	{
		for (j = 0; j<SINGLE_WIDTH; j++)
		{
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
/* set 1 sec delay */
void Delay(unsigned int secs)
{
   unsigned int Time = time(0) + secs;
   while(time(0)<Time);
}
/*set up first board*/
void Initialiseboard(char board[SINGLE_HEIGHT][SINGLE_WIDTH])
{
	int i, j;
	for (i = 0; i<SINGLE_HEIGHT/2; i++)
	{
		for (j = 0; j<SINGLE_WIDTH; j++)
		{
			board[i][j] = '.';
		}
	}
	for (i = SINGLE_HEIGHT/2 ; i< SINGLE_HEIGHT; i++)
	{
		for(j = 0; j< SINGLE_WIDTH; j++)
		{
			board[i][j]= '*';
		}
	}
}

/*store the initilised board into  Big board 1st address  */
void InitialiseboardList(BOARDLIST *s)
{
    char bd[SINGLE_HEIGHT][SINGLE_WIDTH]; 
	s->count = 0;
    Initialiseboard(bd);
    print_array(bd);
    copy(bd,s->boards[s->count].board);
    s->boards[s->count].parent = 0;
}

/* these are testing function */
void test_jump ()
{
    char board[SINGLE_HEIGHT][SINGLE_WIDTH];
    Initialiseboard(board);
	assert(jump_up(board, 5,4));
	assert(jump_up(board, 5,5));
	assert(jump_right(board, 3,4));
	assert(jump_up(board, 5,0));
	assert(jump_up(board, 5,1));
	assert(jump_right(board, 3,0));
}

int jump_up (char board[SINGLE_HEIGHT][SINGLE_WIDTH], int i, int j)
{
	if (board[i-1][j]=='*'&& board[i-2][j]=='.')
	{
		board [i][j]='.';
		board[i-1][j]= '.';
		board[i-2][j]= '*';
		print_array(board);
		return 1;
	}	
	return 0;	
}
int jump_right (char board[SINGLE_HEIGHT][SINGLE_WIDTH], int i, int j)
{
	if (board[i][j+1]=='*'&& board[i][j+2]=='.')
	{
		board [i][j]='.';
		board[i][j+1]= '.';
		board[i][j+2]= '*';
		print_array(board);
		return 1;
	}
	return 0;	
}
int jump_left(char board[SINGLE_HEIGHT][SINGLE_WIDTH], int i, int j)
{
	if (board[i][j-1]=='*'&& board[i][j-2]=='.')
	{
		board [i][j]='.';
		board[i][j-1]= '.';
		board[i][j-2]= '*';
		print_array(board);
		return 1;
	}	
	return 0;	
}
