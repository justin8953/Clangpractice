#include <stdio.h>
#include<time.h>
#define EMTPY ' '
#define FILLED '*'
#define SIZE 33
#define CARPET 27
void sierpinski_square (char block[SIZE][SIZE],int x, int y , int size);
void print_array (char block[SIZE][SIZE]);
void print_carpet(char block[CARPET][CARPET]);
void initialiseblock (char block[SIZE][SIZE]);
void sierpinski_carpet (char block[CARPET][CARPET], int x, int y , int size);
void initialisecarpet (char block[CARPET][CARPET]);

int main(void)
{
	static char block[SIZE][SIZE]; 
	static char carpet[CARPET][CARPET]; 
	initialiseblock(block);
	sierpinski_square(block, SIZE/2, SIZE/2, SIZE/2);
	print_array(block);
	printf("\n");
	initialisecarpet(carpet);
	sierpinski_carpet(carpet,CARPET/3, CARPET/3, CARPET/3);
	print_carpet(carpet);
	return 0;
}


void initialiseblock (char block[SIZE][SIZE])
{
	int i, j;
	for (i = 0 ; i<SIZE; i++)
	{
		for (j=0; j<SIZE; j++)
		{
			block[i][j]= EMTPY;
		}
	}
}
void initialisecarpet (char block[CARPET][CARPET])
{
	int i, j;
	for (i = 0 ; i<CARPET; i++)
	{
		for (j=0; j<CARPET; j++)
		{
			block[i][j]= FILLED;
		}
	}
}
void print_carpet (char block[CARPET][CARPET]){
	int i, j;
	for (i = 0 ; i<CARPET; i++)
	{
		for (j=0; j<CARPET; j++)
		{
			printf("%c",block[i][j]);
		}
		printf("\n");
	}
}
void print_array (char block[SIZE][SIZE]){
	int i, j;
	for (i = 0 ; i<SIZE; i++)
	{
		for (j=0; j<SIZE; j++)
		{
			printf("%c",block[i][j]);
		}
		printf("\n");
	}
}
void sierpinski_square (char block[SIZE][SIZE], int x, int y , int size)
{
	int mid;
	mid = size/2;
	if (size==1)
	{
		block[y][x-1]= FILLED;
		block[y][x+1]= FILLED;
		block[y-1][x]= FILLED;
		block[y][x] = FILLED;
		block[y+1][x]= FILLED;
		block[y+1][x-1] = FILLED;
		block[y+1][x+1] = FILLED;
		return;
	}
	sierpinski_square (block,x , y - mid , mid);
	sierpinski_square (block,x - mid , y +mid , mid);
	sierpinski_square (block,x + mid , y + mid , mid);

}
void sierpinski_carpet (char block[CARPET][CARPET], int x, int y , int size)
{
	int i , j;
	int mid = size/3;
	if (size == 0)
	{	
		return ;
	}
	for (i = y; i<y+size;i++)
	{
		for (j= x ; j<x+size; j++)
		{
			block[i][j] = EMTPY;
		}
	}
	sierpinski_carpet(block, x- 2*mid, y-2*mid, size/3);
	sierpinski_carpet(block, x- 2*mid, y+mid, size/3);
	sierpinski_carpet(block, x- 2*mid, y+4*mid, size/3);
	sierpinski_carpet(block, x+ mid, y-2*mid, size/3);
	sierpinski_carpet(block, x+ 4*mid, y-2*mid, size/3);
	sierpinski_carpet(block, x+ 4*mid, y+ mid, size/3);
	sierpinski_carpet(block, x+ 4*mid, y+4*mid, size/3);
	sierpinski_carpet(block, x+ mid, y+4*mid, size/3);

}