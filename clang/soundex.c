#include<stdio.h>
#include<ctype.h>
#define Max 100
char *soundex(char a[],int temp);
char code(char c);

int main(void){
   char name[Max]={0};
   char new[Max];
   int i = 0, j =0, temp;
   scanf("%s", name);
   printf("Name is %s \n", name);
   temp = name[0];
   name[0] = tolower(name[0]);
   while(name[i]!='\0'){
        if (i!=0 && (name[i]=='h'||name[i] =='w')){
	 new[j++]=code(name[i]);
	 i++;
      }else{
	 new[j++]=code(name[i]);
      }
      i++;
   }
   printf("Soundex is %s \n",soundex(new, temp));
   return 0;
}
char *soundex(char a[], int temp){
   static char new[Max];
   int i=0,j=0;
   while(a[i] && j!=4){
      if(a[i]=='0' & i!=0){
	 i++;
      }else if(a[i]==a[i+1]){
	 new[j++] = a[i++];
	 i++;
      }else if(a[i-1]==a[i]){
	 i ++;
      }
      else
	 new[j++]=a[i++];
   }
   while(j!=4){
      new[j++] = '0';
   }
   new[j]= '\0';
   new[0] =temp;
   return new;
}
char code(char c){
   char array[26] = {'0','1','2','3','0','1','2','0','0','2','2','4','5','5','0','1','2','6','2','3','0','1','0','2','0','2'};
   char num;
   if(isupper((int)c)){
      num = array[tolower((int)c)-'a'];
   }else{
      num = array[c-'a'];
   }
   return num;
}
