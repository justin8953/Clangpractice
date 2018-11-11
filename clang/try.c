#include<stdio.h>
#include<assert.h>
#include<time.h>
#define TOTAL_SIZE 1000
#define SINGLE_WIDTH 7
#define SINGLE_HEIGHT 8


struct single_board
{
	char board[SINGLE_HEIGHT][SINGLE_WIDTH];
	int parent;
};
typedef struct single_board SINGLEBOARD;
struct board＿list
{
	SINGLEBOARD boards[TOTAL_SIZE];
	int count;
};
typedef struct board＿list BOARDLIST;

void Initialiseboard(BOARDLIST *s);
void copy(char board[SINGLE_HEIGHT][SINGLE_WIDTH],char tmp[SINGLE_HEIGHT][SINGLE_WIDTH]);
void initial(char board[SINGLE_HEIGHT][SINGLE_WIDTH]);
void print_array(char board[SINGLE_HEIGHT][SINGLE_WIDTH]);

int main(void)
{
    BOARDLIST *p;
    Initialiseboard(p);
    print_array(p->boards[0].board);
    return 0 ;
}
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
void initial(char board[SINGLE_HEIGHT][SINGLE_WIDTH])
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
void Initialiseboard(BOARDLIST *s)
{
    char *b, bd[SINGLE_HEIGHT][SINGLE_WIDTH]; 
    initial(bd);
    print_array(bd);
    copy(bd,s->boards[0].board);
    // s->boards[0].board = initial(b);
    s->boards[0].parent = 0;

}

