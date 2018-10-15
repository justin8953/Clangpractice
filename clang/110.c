#include<stdio.h>
#include<stdlib.h>
#define N 1000
int next(int a[], int i);
int main(void){

int *a,i;
a = (int *)malloc(N);
a [0] = 0;
a [1] = 1;
a [2] = 0;
for (i=0; i<N; i++){
   a[i+3] = next(a,i);
}
printf("[");
for (i=0; i<N ; i++){
   printf("%d",a[i]);
}
printf("]");
free(a);
return 0;
}


int next(int a[], int i){
   if(a[i]==1 && a[i+1]==1 && a[i+2]==1)
       return 0;
   else if(a[i]==1 && a[i+1]==1 && a[i+2]==0)
       return 1;
   else if(a[i]==1 && a[i+1]==0 && a[i+2]==1)
       return 1;
   else if(a[i]==1 && a[i+1]==0 && a[i+2]==0)
       return 0;
   else if(a[i]==0 && a[i+1]==1 && a[i+2]==1)
       return 1;
   else if(a[i]==0 && a[i+1]==1 && a[i+2]==0)
       return 1;
   else if(a[i]==0 && a[i+1]==0 && a[i+2]==1)
       return 1;
   else
       return 0;
}
