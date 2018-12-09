#include<stdio.h>
#include<stdlib.h>



int hash(char *s, int size);
int main(void)
{
   printf("previous index is %d, after index is %d ", hash("justin",10), hash("justin",30));
   return 0;
}

int hash(char *s, int size)
{
   unsigned long hash = 5381;
   int c;
   while ((c=(*s++)))
   {
      hash = 33* hash^c;
   }
   return (int)(hash% size);
}