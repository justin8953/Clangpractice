#include<stdio.h>
#include<ctype.h>
int is_vowel(char c);

int main(void){
   int c;
   while ((c= getchar())!= EOF){
      if(is_vowel(c)){
	 c = toupper(c);
      }	else
	 c = tolower(c);
      putchar(c);
   }
   return 0;
}

int is_vowel(char c){
   if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u')
      return 1;
   else
      return 0;
}
