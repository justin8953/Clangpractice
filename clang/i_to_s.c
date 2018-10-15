#include<stdio.h>
void to_s(char s[], int num);

int main(void){
   int i; 
   char s[256];
   scanf("%d", &i);
   to_s(s, i);
   printf("%s \n", s);
   return 0;
}
void to_s(char s[],int num){
   *s = num; 
}

