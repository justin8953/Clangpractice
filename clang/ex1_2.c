#include<stdio.h>

int twice_plus(int a, int b, int c);

int main(){
   int a, b, c;
   int ans;
   printf("Input three integers \n");
   scanf("%d%d%d", &a,&b,&c);
   ans = twice_plus(a,b,c);
   printf("Twice the sum of integers plus %d is %d \n", c, ans);
   return 0;
}

int twice_plus(int a, int b, int c){
   int sum, ans; 
   sum = a + b + c;
   ans = 2* sum + c;
   return ans;
}
/* gcc file.c  -o file  -pedantic -ansi  -Wall -Wextra -Wfloat-equal -O2 */
