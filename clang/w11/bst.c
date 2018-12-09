#include "bst.h"

/* 
   1.Intialise the dictionary 
   2.Set up the node with no element
   3.Left and right node set up with NULL
*/

dic* dic_init(int size)
{
   dic * dict;
   dict = (dic*)calloc(1, sizeof(dic));
   if (dict==NULL)
   {
      ON_ERROR("Creation of Dictionary Failed");
   }
   dict->word = (char *)calloc(1,size);
   if (dict->word==NULL)
   {
      ON_ERROR("Creation of Word Failed");
   }
   dict->left = NULL;
   dict->right = NULL;
   return dict;
}
/* 
   1.Create a newnode and initialse it 

*/
void dic_insert(dic*s, char *v)
{
   dic* NewNode;
   if (s ==NULL|| strcmp(v,s->word)==0)
   {
      return ;
   }
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

void dic_free(dic **s)
{
   if (s != NULL)
   {
      dic *p = *s;
      if (p->left!=NULL)
      {
         dic_free(&(p->left));
      }else if(p->right!=NULL)
      {
         dic_free(&(p->right));
      }else
      {
         free(p->word);
         free(p);
         s = NULL;
      }
   }
}

