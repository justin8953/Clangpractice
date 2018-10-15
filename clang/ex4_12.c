#include<stdio.h>
#include<math.h>
#define N 3000
int is_prime(int num);

int main(void){
   int i=0, cnt=0;
   while(cnt != N){
      if (is_prime(i)){
	 printf("%d \n", i);
	 cnt++;
      }
      i++;
   }
   printf("%d th prime is %d \n", cnt, i );
   return 0;

}


int is_prime(int num){
   int root,i, is_prime = 1;
   root = (int)((double)sqrt(num));
   if (num == 0 || num==1){
      is_prime = 0;
   }
   else if (num == 2){
      is_prime = 1;
   }else{
      for (i =2; i<= root; i++ ){
	 if(num%i==0){
	    is_prime = 0;
	    break;
	 }
      }
   }
   return is_prime;
}
