#include<stdio.h>

int hailstone(int n);
int main(void){
   int n = 77;
   printf("%d ", n);
   while(n!=1){
      n = hailstone(n);
      printf("%d ", n);
   }
   return 0;
}
int hailstone(int n){
   if(n%2 == 0){
      return n/2;
   }else{
      return 3*n+1;
   }
}
