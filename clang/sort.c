#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_array(int a[], int length);
void swapped(int *num1, int *num2);
void bubble_sort(int a[], int length);
void selection_sort(int a[], int length);
void insert_sort(int a[], int length);
void merge_sort(int a[], int tmp[] ,int l, int r);
int main(void){
   int *p, *q, i,length;
   srand(time(0));
   printf("請輸入想要的陣列大小\n");
   scanf("%d",&length);
   p = (int*)malloc(length);
   printf("正在產生陣列.... \n");
   for(i = 0; i<length-1; i++){
      p [i] = rand()%100;
   } 
   print_array(p, length);
/*  
   printf("使用bubble sort \n");
   bubble_sort(p, length);
   printf("使用 selection sort \n");
   selection_sort(p,length);
   printf("使用insert sort \n");
   insert_sort(p, length);
*/
   q = (int*)malloc(length);
   merge_sort(p,q,0,length-1);
   print_array(p, length);
   free(p);
   free(q);
   return 0 ;

}

void print_array(int a[], int length){
   int i;
   printf("[");
   for (i=0; i<length-1; i++){
      printf("%d\t",a[i]);
   }
   printf("] \n");
}
void swapped(int *num1, int *num2){
   int temp = *num2;
   *num2 = *num1;
   *num1 = temp;
}
void bubble_sort(int a[], int length){
   int i,j ;
   for(j=length-1; j>0; j--){
      printf("%d \n", j);
      for (i=0; i<j; i++){
	 if (a[i]>a[i+1]){
	    swapped(&a[i],&a[i+1]);
	    print_array(a,length);
	    printf("swapped \n");
	 }else{
	    print_array(a,length);
	 }
	 
      }

   }
}
void selection_sort(int a[], int length){
   int i, j,min;
   for (i= 0; i<length-1; i++){
	 min = i;
	 for (j = i+1; j<length-1; j++ ){
	    if (a[min]>a[j]){
	       min = j;
	    } 
	 }
	 swapped(&a[i],&a[min]);
	 print_array(a,length);
   }
}

void insert_sort(int a[], int length){
   int i, j; 
   for (i=0; i < length-1; i ++){
      j = i+1;
      while(j>0){
	 if (a[j]<a[j-1]){
	    swapped(&a[j-1],&a[j]);
	    printf("swapped \n");
	    print_array(a, length);
	 }
	 j--;
      }
      print_array(a, length);
   }
}
/*
void merge(int a[], int b[],int c [], int length1, int length2){
   int i=0, j=0, k=0;
   while ((i<length1-1)&&(j<length2-1)){
      if(a[i]>=b[j]){
	 c[k]=b[j];
	 j++;
	 k++;
      }else{
	 c[k]=a[i]
	 i++;
	 k++;
      }
   }
   while (i< length-1){
      c[k]= a[i];
      i++;
      k++;
   }
   while (j<length-1){
      c[k] = b[j];
      k++;
   }
}
*/
void merge_sort(int a[], int tmp[] ,int l, int r){
   int i, j, k, m, n;
   if(l<r){
      m = (l+r)/2;
      merge_sort(a,tmp, l, m);/* merge_sort  左半部*/
      merge_sort(a,tmp ,m+1, r);/*merge sort 右半部*/
      i=l ;/* i=l 指向左邊的第一個資料*/
      j = m+1;/*j 指向右邊的第一個資料*/
      k = l;/*k 指向temp 第一個資料*/
      n = r-l+1; /*n為正在合併的個數*/
      while(i<=m && j<=r){
	 if (a[i]<=a[j]){
	    tmp[k] = a[i];
	    i++;
	    k++;
	 }
	 else{
	    tmp[k] = a[j];
	    k++;
	    i++;
	 }
      }
      while(i<=m){
	 tmp[k] = a[i];
	 i++;
	 k++;
      }
      while(j<=r){
	 tmp[k]= a[j];
	 k++;
	 j++;
      }
      for(i=0; i<n ; i++){
	 a[r] = tmp[r];
	 r--;
      }
   }
}
