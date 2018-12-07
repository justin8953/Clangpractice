#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 5000

void merge_sort(int *src,  int *spare, int l, int r);
void merge  (int *src,  int *spare, int l,int m, int r);

int main(void)
{
   
   return 0;
}

void merge_sort(int *src,  int *spare, int l, int r)
{
   int m; 
   if (l!=r)
   {
      m = (l+r)/2;
      merge_sort(src, spare, l, m);
      merge_sort(src, spare, m+1, r);
      merge(src, spare, l, m ,r);
   }
}
void merge  (int *src,  int *spare, int l,int m, int r)
{
   int s1, s2, d;
   s1 = l; /* left array first one */
   s2 = m+1; /* right array first one */
   d = l; /* New array index */
   do 
   {
      /* compare with left and right array and put the smaller one into new array */
      if (src[s1]<src[s2])
      {
         spare[d++] = src[s1++];
      }
      else
      {
         spare[d++] = src[s2++];
      }
   }while((s1<=m)&&(s2<=r));
   /* */
   if (s1>m)
   {
      memcpy(&spare[d], &src[s2], sizeof(spare[0])*(r-s2+1));
   }
   else
   {
      memcpy(&spare[d], &src[s1], sizeof(spare[0])*(m-s1+1));
   }
   memcpy(&spare[l], &src[l], sizeof(spare[0])*(r-l+1));
}