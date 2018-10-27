#include<stdio.h>
#define N 50000
int hail(int n );
int hail_max(int n );

int main(void){
int i, num ,max, count,max_num=0,  maxcnt=0;
for(i=2; i<N; i++){
   count = hail(i);
   max = hail_max(i);
   if (max>max_num){
      max_num = max;
   }
   if (count>maxcnt)
      maxcnt = count;
}
printf("max num is %d \n", max_num);
printf("max step is %d \n", maxcnt);
return 0;
}
int hail(int n){
   int step=0;
   while(n!=1){
      if(n%2==0){
	 n = n/2;
      }else
	 n =  3*n+1;
      step++;
   }
   return step;
}
int hail_max(int n){
   int max=0;
   while(n!=1){
      if(n%2==0){
	 n = n/2;
      }else
	 n =  3*n+1;
      if(n>max){
	 max = n;
      }
   }
   return max;


}
