#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int check(int a[], int num, int length);
void swapped(int *p, int*q);
void sort(int a[], int length);
int main(void){
   int num,i,r;
   int *song;
   srand(time(0));
   printf("How many songs required ? \t");
   scanf("%d", &num);
   song = (int *)malloc(sizeof(int));
   for (i= 0; i<num; i++){
      r = rand()%num+1;
      while(check(song,r, num)==1){
	 r =rand()%num+1;
      }
      song[i] = r;
   }
   for (i=0; i<num;i++){
      printf("%d \n", song[i]);
   }
   sort(song, num);
   for (i=0; i<num;i++){
      printf("%d \n", song[i]);
   }
   free(song);
   return 0;
}
int check(int *a,int num,int length){
   int i,  ans=0;
     for (i=0; i<length-1; i++){
      if (num==a[i]){
	 return 1;
      }
   }
   return 0;
}
void swapped(int *p, int *q){
   int temp;
   temp = *p;
   *p = *q;
   *q = temp;
}
void sort(int a[],int length){
   int i, change;
   do{
      change = 0;
      for (i=0;i<length-1; i++){
	 if(a[i]>a[i+1]){
	    swapped(&a[i],&a[i+1]);
	    change++;
	 }
      }
   }while(change);
}
