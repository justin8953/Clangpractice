#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#define max_length 100


int isogram(char *s);


int main(void)
{
   FILE *p;
   char word[max_length], *temp_word;
   int c,i;
   unsigned long temp_num=0;
   assert(isogram("programming")==0);  
   assert(isogram("housewarmings")==0);
   assert(isogram("abductions")==1);
   assert(isogram("housewarming")==1);
   assert(isogram("hydromagnetics")==1);
   assert(isogram("uncopyrightable")==1);
   if((p = fopen("iso.txt","r"))==NULL)
   {
      printf("no file \n");
      return 1;
   }
   i = 0;
   while((c=getc(p))!=EOF)
   {
       if (c=='\n')
       {
           i = 0;
           if (isogram(word))
           {   
               if(strlen(word)>temp_num)
               {
                   temp_num = strlen(word);
                   temp_word = word;
               }
               
           }
       }else{
            word[i]=c;
            i++;
       }
   }
   fclose(p);
   printf("%s (%lu) \n", temp_word, temp_num);
   return 0 ;
}




int isogram(char *s)
{
   int len,i,j, current_word,repeat;
   len = strlen(s);
   for(i=0;i<len;i++){
      current_word = s[i];
      repeat = 0;
      for (j=0;j<len;j++)
      {
	 if(s[j]==current_word){
	    repeat++;
	 }
      }
      if(repeat>1){
	 return 0;
      }
   }
   return 1;
}
