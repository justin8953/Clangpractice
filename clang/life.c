
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <assert.h>
#define TALL 62
#define WIDE 82
enum bool {False, True};
typedef enum bool bool; 

void test_game(char board[TALL][WIDE]);
void test_all();
int test_1(char board[TALL][WIDE]);/* small explorder */
int test_2(char board[TALL][WIDE]);/*  explorder */
int test_3(char board[TALL][WIDE]);/* row  */
void start_game(char board[TALL][WIDE]);
void law(char board[TALL][WIDE],char temp[TALL][WIDE]);/* use birth, survive and death law */
int check_surround(char a[TALL][WIDE], int i, int j);/* check cell surrounding and count how many cells are inhabited in its surrounding*/
void intial(char board[TALL][WIDE]); /* set 60*80 every cell has 1 in 5 inhabit */
void intial_array(char a[TALL][WIDE]);/* set all elements in array to _ */
void print_array(char board[TALL][WIDE]); /* print array*/
int birth(char a[TALL][WIDE], int i, int j); /* if one cell is empty and surrounding cells have three inhabited cells, it can be inhabited*/
/* 
if one cell is inhabited and surrounding cells have more than three inhabited cells or less than two, it will be death.
else one cell is inhabited and surrounding cells have three or  two inhabited cells, it will survive
*/
int death(char a[TALL][WIDE], int i, int j); /*the board is identical then stop the game, calculate how many cells are the same*/
void copy(char board[TALL][WIDE],char temp[TALL][WIDE]);
int stop(char board[TALL][WIDE], char temp[TALL][WIDE]);
void Delay(unsigned int secs);

int main(void)
{
	char board [TALL][WIDE];
	srand(time(0)); 
	intial_array(board);
	test_all(board);
	intial(board);
	start_game(board);
	return 0;
}

void test_game(char board[TALL][WIDE])
{
   static char temp[TALL][WIDE];
   law(board, temp);
}
void test_all(char board [TALL][WIDE])
{
	assert(test_1(board)==True);
	assert(test_2(board)==True);
	assert(test_3(board)==True);
}
int test_1(char board[TALL][WIDE])
{
   board[32][40] = '*'; 
   board[31][39] = '*';
   board[31][41] = '*';
   board[30][40] = '*';
   board[30][39] = '*';
   board[30][41] = '*';
   board[29][40] = '*';
   test_game(board);
   return True;
}
int test_2(char board[TALL][WIDE])
{
   board[28][40] = '*';
   board[32][40] = '*';
   board[28][38] = '*'; 
   board[29][38] = '*';
   board[30][38] = '*';
   board[31][38] = '*';
   board[32][38] = '*';
   board[28][42] = '*'; 
   board[29][42] = '*';
   board[30][42] = '*';
   board[31][42] = '*';
   board[32][42] = '*';
   test_game(board);
   return True;
}
int test_3(char board[TALL][WIDE])
{
   board[30][37]='*';
   board[30][38]='*';
   board[30][39]='*';
   board[30][40]='*';
   board[30][41]='*';
   board[30][42]='*';
   board[30][43]='*';
   test_game(board);
   return True;  
}

void start_game(char board[TALL][WIDE])
{
   static char temp[TALL][WIDE];
   int start = 0;
   print_array(board);
   while(start!=(TALL*WIDE))
   {
   	law(board, temp);
   	print_array(board);
   	start = stop(board, temp);
   	Delay(1);
   }
}
void law(char board[TALL][WIDE],char temp[TALL][WIDE])
{
	int i, j;
	copy(board, temp);   
	for (i = 1; i<TALL-1; i++)
	{
        for (j = 1; j<WIDE-1; j++)
        {
            if(birth(temp,i,j)==1)
            {
                board[i][j]='*';
            }else if(death(temp,i,j)==1)
            {
                board[i][j]='_';
                
            }
            
        }
        
    }
}
int check_surround(char a[TALL][WIDE], int i, int j)
{
   int cnt=0;

   if(a[i-1][j-1]=='*')
   {
      cnt++;
   }
   if(a[i-1][j]=='*')
   {
      cnt++;
   }
   if(a[i-1][j+1]=='*')
   {
      cnt++;
   }
   if(a[i][j-1]=='*')
   {
      cnt++;
   }
   if(a[i][j+1]=='*')
   {
      cnt++;
   }
   if(a[i+1][j-1]=='*')
   {
      cnt++;
   }
   if(a[i+1][j]=='*')
   {
      cnt++;
   }
   if(a[i+1][j+1]=='*')
   {
      cnt++;
   }
   return cnt;
}
void intial(char board[TALL][WIDE])
{
   int num; 
   int row, col;

   for(row=1; row<TALL-1; row++)
   {
      for (col=1; col<WIDE-1;col++ )
      {
	 num = rand()%5;
	 if (num==4)
	 {
	    board[row][col] = '*';
	 }
	 else
	 {
	    board[row][col]='_';
	 }
      }      
   }
}
void intial_array(char a[TALL][WIDE])
{
   int i, j;
   for (i=0; i<TALL; i++){
      for (j = 0; j < WIDE; j++)
      {
         a[i][j]='_';   
      }
   }
}
void print_array(char board[TALL][WIDE])
{
   int i, j;

   for (i=0;i<TALL;i++)
   {
      for (j=0; j<WIDE; j++)
      {
      printf("%c", board[i][j]);
      }
      printf("\n");
   }
}
int birth(char a[TALL][WIDE], int i, int j)
{
   if (a[i][j]=='_')
   {
      if(check_surround(a,i,j)==3)
      {
      return 1;
      }
   }
   return 0;
}
int death(char a[TALL][WIDE], int i, int j)
{
   if(a[i][j]=='*')
   {
      if(check_surround(a,i,j)>3||check_surround(a,i,j)<2)
      {
         return 1;
      }
   }
   return 0;
}
void copy(char board[TALL][WIDE],char temp[TALL][WIDE])
{
   int i, j;

   for (i = 0; i<TALL;i++)
   { 
     for (j=0;j<WIDE;j++)
      {
      temp[i][j]=board[i][j];
    }
   }
} 
int stop(char board[TALL][WIDE], char temp[TALL][WIDE])
{
   int i, j,stop=0;   
   for(i=0; i<TALL; i++)
   {
      for(j=0;j<WIDE;j++)
      {
      if(board[i][j]==temp[i][j])
      {
         stop++;
      }
      }
   }
   return stop;
}
void Delay(unsigned int secs)
{
   unsigned int Time = time(0) + secs;
   while(time(0)<Time);
}

