#include<stdio.h>
#include<stdlib.h>

void new_array(int *p, int n);
void print_array(int p[], int n);
void sort(int p[], int n);
void swap(int *p, int *q);
int main(void){
   int num;
   int *c;
   c = (int *)malloc(sizeof(int));
   printf("How many numbers do you wish to enter \n ");
   scanf("%d", &num);
   printf("Enter %d real numbers \n", num);
   new_array(c, num);
   print_array(c, num);
   sort(c, num);
   print_array(c, num);
   printf("MAX is %d \n", c[num-1]);
   return 0 ;


}

void new_array(int *p, int n){
   int i;
   for (i = 0; i<n; i++){
      printf("Enter %d number \n", i);
      scanf("%d", p);
      while (*p%2 == 0){
	 printf("%d is even. You can only enter odd \n ", *p);
	 scanf("%d",p);
      }
      p++;
   }
}
void print_array(int p[], int n){
   int i ;
   printf("[");
   for (i = 0; i<n; i++){
      printf("%d ",p[i]);
   }
   printf("] \n");

}
void sort(int p[], int n){
   int i,change;
   do{
      change = 0;
      for(i = 0; i<n-1 ; i++){
	 if (p[i]>p[i+1]){
	    swap(&p[i],&p[i+1]);
	    change++;
	 }
      }
   }while (change);
}
void swap(int *p, int *q){
   int temp;
   temp = *p;
   *p = *q;
   *q = temp;
}
