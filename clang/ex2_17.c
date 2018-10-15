#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 500

int main(void){
   int i=0,rnum,diff, plus_cnt=0,minus_cnt=0, median;
   median = RAND_MAX/2;
   srand(time(0));
   while(i <N){
      rnum = rand();
      if (rnum>median)
	 plus_cnt++;
      else
	 minus_cnt++;
      diff = plus_cnt - minus_cnt;
      printf("%d : The difference is %d \n",i , diff);
      i++;
   }
   return 0 ;
}

