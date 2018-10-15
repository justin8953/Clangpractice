#include<stdio.h>
#include<ctype.h>
int isVowel(char c);
void skip(char c);
int main(void){
   int c;
   while((c=getchar())!=EOF){
      skip(c);
   }
   return 0;



}
int isVowel(char c){
   c = tolower(c);
   if (c=='a'|| c=='e' || c=='i' || c=='o' ||c=='u'){
      return 1;
   }else
      return 0;
}
void skip(char c){
   if(isVowel(c)!=1)
      putchar(c);
}
