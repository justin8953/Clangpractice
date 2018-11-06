#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 21
#define CSEC (double)(CLOCKS_PER_SEC)

void exe_time(clock_t c1, clock_t c2);
void print_arr(int board[N][N]);
void filled(int board[N][N]);
void swapped(int *p, int *q);
void bubble_sort(int board[N][N]);
void centre_sort(int board[N][N]);
int check(int i, int j, int p, int q);

int main(void)
{
   clock_t start, end;
   int board[N][N];
   start = clock();
   srand(time(0));
   filled(board);
   print_arr(board);
   printf("\n");
   bubble_sort(board);
   print_arr(board);
   printf("\n");
   filled(board);
   centre_sort(board);
   print_arr(board);

   end = clock();
   exe_time(start,end);
   return 0;
}
int check(int i, int j, int p, int q)
{
   int m, r1,r2;
   m  = (N-1)/2;
   r1 = (i-m)*(i-m)+(j-m)*(j-m);
   r2 = (p-m)*(p-m)+(q-m)*(q-m);
   if (r1>=r2)
      return 1;
   return 0;
}
void centre_sort(int board[N][N])
{
   int i,j, change;
   do{
      change = 0;
	 for(j=0;j<N-1;j++){
	    for(i=0;i<N-1;i++)
	    {
	       if (check(i,j,i+1,j)){
		  if (board[i][j]<board[i+1][j])
		  {
		     swapped(&board[i][j], &board[i+1][j]);
		     change++;
		  }
	       }else{
		  if (board[i][j]>board[i+1][j])
		  {
		     swapped(&board[i][j], &board[i+1][j]);
		     change++;
		  }
	       }
	    }
	 }
	 for(i=0;i<N-1; i++)
	 {
	    for(j=0;j<N-1;j++)
	    {
	       if (check(i,j,i,j+1)){
		  if (board[i][j]<board[i][j+1])
		  {
		     swapped(&board[i][j], &board[i][j+1]);
		     change++;
		  }
	       }else{
		  if (board[i][j]>board[i][j+1])
		  {
		     swapped(&board[i][j], &board[i][j+1]);
		     change++;
		  }
	       }
	    }
	 }
   }while(change);
}

void bubble_sort(int board[N][N])
{
   int i,j, change;
   do{
      change = 0;
	 for(j=0;j<N-1;j++){
	    for(i=0;i<N-1;i++){
	       if (board[i][j]>board[i+1][j])
	       {
		  swapped(&board[i][j], &board[i+1][j]);
		  change++;
	       }
	    }
	 }
	 for(i=0;i<N-1; i++)
	 {
	    for(j=0;j<N-1;j++)
	    {
	       if(board[i][j]>board[i][j+1])
	       {
		  swapped(&board[i][j], &board[i][j+1]);
		  change++;
	       }   
	    }
	 }	 
   }while(change);
}

void swapped(int *p, int *q)
{
   int temp;
   temp = *p;
   *p = *q;
   *q = temp;
}
void print_arr(int board[N][N])
{
   int i, j;
   for (i=0; i<N;i++)
   {
      for(j=0;j<N;j++)
      {
	 printf("%d", board[i][j]);
      }
      printf("\n");
   }
}
void filled(int board[N][N])
{
   int i, j, num;
   for(i=0;i<N;i++)
   {
      for(j=0;j<N;j++)
      {
	 num = rand()%10;
	 board[i][j]= num;
      }
   }
}
void exe_time(clock_t c1, clock_t c2)
{
   double time;
   time = (double)(c2-c1)/CSEC;
   printf("%f \n", time);
}
