#include<stdio.h>
#include<stdlib.h>

void new_array(float *p, int n);
void print_array(float p[], int n);
void sort(float p[], int n);
void swap(float *p, float *q);
int main(void){
   int num;
   float *c;
   c = (float *)malloc(sizeof(float));
   printf("How many numbers do you wish to enter \n ");
   scanf("%d", &num);
   printf("Enter %d real numbers \n", num);
   new_array(c, num);
   print_array(c, num);
   sort(c, num);
   print_array(c, num);
   printf("MAX is %.3f \n", c[num-1]);
   return 0 ;


}

void new_array(float *p, int n){
   int i;
   for (i = 0; i<n; i++){
      printf("Enter %d number \n", i);
      scanf("%f", p);
      p++;
   }
}
void print_array(float p[], int n){
   int i ;
   printf("[");
   for (i = 0; i<n; i++){
      printf("%.3f ",p[i]);
   }
   printf("] \n");

}
void sort(float p[], int n){
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
void swap(float *p, float *q){
   float temp;
   temp = *p;
   *p = *q;
   *q = temp;
}
