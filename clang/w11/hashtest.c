#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "hsh.h"

int main(void)
{
   dic * root;
   printf("Test Start....... \n");
   dic_insert(root,"root");
   dic_insert(root,"justin");
   dic_insert(root,"bem");
   dic_insert(root,"shein");
   dic_insert(root,"sline");
   dic_insert(root,"saae");
   assert(dic_isin(root,"justin")==true);
   assert(dic_isin(root,"ben")==true);
   
   dic_free(&root);
   assert(root==NULL);
   printf("Test End....... \n");
   /* code */
   return 0;
}
