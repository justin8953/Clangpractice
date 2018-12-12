#include "bst.h"

/* 
   1.Intialise the dictionary 
   2.Set up the node with no element
   3.Intialise the word to with WORDSIZE
   4.Left and right node set up with NULL
*/
dic* dic_init(int size)
{
   dic * dict;
   dict = (dic*)calloc(1, sizeof(dic));
   if (dict==NULL)
   {
      ON_ERROR("Creation of Dictionary Failed");
   }
   dict->word = (char *)calloc(1,size*sizeof(char));
   if (dict->word==NULL)
   {
      ON_ERROR("Creation of Word Failed");
   }
   dict->left = NULL;
   dict->right = NULL;
   return dict;
}
/* 
   1. if word is already inside, do nothing.
   2. if the string is larger than the present
      node, then it's compared with the right 
      node word. Else it's compared with left one.
   3. when the next node is NULL,Create a newnode 
      and initialse it.
   4. if the string is larger than the string
      in the node, the string is put on right.
      Else it's put on left.  
*/
void dic_insert(dic*s, char *v)
{
   dic* NewNode;
   if (s !=NULL|| strcmp(v,s->word)!=0)
   {
      if (strcmp(v, s->word)>0)
      {
            if (s->right == NULL)
            {
                  NewNode = dic_init(strlen(v)+1);
                  strcpy(NewNode->word, v);
                  s->right = NewNode;
            }else
            {
                  dic_insert(s->right,v);
            }
      }else{
            if (s->left == NULL)
            {
                  NewNode = dic_init(strlen(v)+1);
                  strcpy(NewNode->word, v);
                  s->left = NewNode;
            }else
            {
                  dic_insert(s->left,v);
            }
      }
   } 
}
/* 
   1. check from the root. 
   2. go through right handside, and if the word is
      found return true. Else if go through left handside,
      if the word is found return true. else return false.
*/
bool dic_isin(dic*s, char *v)
{
   if (s!=NULL)
   {
      if (strcmp(s->word,v)==0)
      {
         return true;
      }
      if (strcmp(v,s->word)>0)
      {
         return dic_isin(s->right,v);
      }else{
         return dic_isin(s->left,v);
      }
   }
   return false;
}
/* 
   1. find the last child and if left side has child,
      free the left side first. Then, check right side, 
      if child exist, free rigth side 
   2. go to upper level, and check again. 
*/

void dic_free(dic **s)
{
      if (s != NULL)
      {
            dic *p = *s ;
            if (p->left==NULL && p->right == NULL)
            {
                  free(p);
                  s = NULL;
            }
      else if (p->left!=NULL)
      {
         dic_free(&(p->left));
      }else if(p->right!=NULL)
      {
         dic_free(&(p->right));
      }
   }
}

