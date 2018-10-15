#include<stdio.h>
#define N 20
int main(void){

   int i,j,k;
   for (i = N; i>0; i--)
   {
      for (j = i; j>0;j--){
	 printf("*");
      }
      printf("\n");
   }
   printf("\n");
   for (i = N; i>0; i--){
      for(k = i; k < N; k++ ){
	 printf(" ");
      }
      for (j = 0; j< 2*i-1; j++){
	 printf("*");
      }
      printf("\n");

   }
   for (i=0;i<N;i++){
      k = 0;
      while(k<(N-i-1)){
	 printf(" ");
	 k++;
      }
      j=0;
      while(j<(2*i+1)){
	 printf("*");
	 j++;
      }
      printf("\n");
   }
   return 0;
}

