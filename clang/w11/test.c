#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "bst.h"

int main(void)
{
   dic * root;
   char head[50];
   char words[50];
   printf("Test Start....... \n");
   assert(scanf("%s",head)==1);
   root = dic_init(strlen(head));
   strcpy(root->word,head);
   while(scanf("%s", words)==1)
   {
      dic_insert(root,words);
   }
   assert(dic_isin(root,"justin")==true);
   assert(dic_isin(root,"ben")==true);
   dic_free(&root);
   printf("Test End....... \n");
   /* code */
   return 0;
}
