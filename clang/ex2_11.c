#include<stdio.h>

int main(void){
   
   int a=0,b=0,c=0;
   a = ++b + ++c ; 
   printf("a is %1d b is %1d c is %1d \n",2,1,1);
   printf("a is %1d b is %1d c is %1d \n",a,b,c);
   a = b++ + ++c ;
   printf("a is %1d b is %1d c is %1d \n",3,2,2);
   printf("a is %1d b is %1d c is %1d \n",a,b,c);
   a = ++b + c++ ;
   printf("a is %1d b is %1d c is %1d \n",5,3,3);
   printf("a is %1d b is %1d c is %1d \n",a,b,c);
   a = b-- + --c ;
   printf("a is %1d b is %1d c is %1d \n",5,2,2);
   printf("a is %1d b is %1d c is %1d \n",a,b,c);
   return 0 ;
}
