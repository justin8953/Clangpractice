#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct Tree {
   int data;
   struct Tree *left;
   struct Tree *right;
}Tree

int main(void){
   Tree * tree;
   tree = createbinaryTree();
   return 0;
}

Tree *createbinaryTree(void){
   Tree *p;
   char data;
   data = getche();
   if (data =='0')
      return NULL;
   p = (Tree *)malloc (sizeof(Tree));
   p -> data = data;
   p -> left = createbinaryTree();
   p -> right = createbinaryTree();
   return p;
}
