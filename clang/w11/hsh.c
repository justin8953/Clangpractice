#include "hsh.h"

/* This is hashing function:
   % talbesize to get string index
*/
int hash(char *s, int tablesize)
{
   unsigned long hash = HASHNUM;
   int c;
   while ((c=(*s++)))
   {
      hash = HASHMUTINUM* hash^c;
   }
   return (int)(hash%tablesize);
}

bool table_isFulled(dic *s)
{
   int i ;
   for (i= 0 ; i<s->sz;i++)
   {
      if (strcmp(s->table[i].word,EMPTY)==0)
      {
         return false;
      }
   }
   return true;
}
/* 
   1.Intialise the dictionary 
   2.Initialise the hash table
   3.Intialise the cell in hash talbe with WORDSIZE
   4.Set the size with MAXSIZE 
*/
dic* dic_init(int size)
{
   dic * dict;
   int i ;
   dict = (dic*)calloc(1, sizeof(dic));
   if (dict==NULL)
   {
      ON_ERROR("Creation of Dictionary Failed");
   }
   dict->table = (dictype *)calloc(MAXSIZE, sizeof(dictype));
   if (dict->table==NULL)
   {
      ON_ERROR("Creation of Dictionary Failed");
   }
   for (i=0 ; i< MAXSIZE; i++)
   {
      dict->table[i].word = (char *)calloc(1, sizeof(char)*size);
   }
   dict ->sz = MAXSIZE;
   return dict;
}
/* for solving collision
   1.Intialise the chain listed 
*/

dictype *chain_initi(char *v)
{
   dictype *node;
   node = (dictype *)calloc(1, sizeof(dictype));
   node->word = (char *)calloc(1, strlen(v)+1);
   return node;
}

dictype *resize(dic *s, char *v)
{
      dictype *p;
      p = (dictype *)realloc(s->table, sizeof(dictype)*(s->sz+1));
      p[s->sz].word = (char *)calloc(1, sizeof(char)*(strlen(v)+1));
      s->sz = s->sz +1;
      return p;
}

/* 
   1. if table is fulled, then reallocate 
      the table size.
   2. get the index from hashing function. 
   3. if collision occurs, create newnode
      and initialise it. Newnode chain with the 
      previous node or cell.
   4. if no collision, put the word into the table
*/
void dic_insert(dic*s, char *v)
{
   int set_index;
   dictype *p,*Newnode;
   if (table_isFulled(s))
   {
      s->table = resize(s,v);
   }
   if (s!=NULL)
   {
      set_index = hash(v,s->sz);
      p = &(s->table[set_index]);
      if(strcmp(p->word,EMPTY)!=0) 
      {
         while(p->next!=NULL)
         {
            p = p->next;
         }
         Newnode = chain_initi(v);
         Newnode->next = NULL;
         strcpy(Newnode->word,v);
         p->next = Newnode;
      }else{
         strcpy(p->word,v);
      }
   }
}
/* 
   1. get the index from hashing function 
   2. point to the cell, check if the word is the same
      return true. Else check the chain list.
   3. do the while loop, check until the cell is null
      or the word is found.
*/
bool dic_isin(dic*s, char *v)
{
   int find_index;
   dictype *p;
   find_index = hash(v,s->sz); 
   p = &(s->table[find_index]);
   if(strcmp(p->word,v)!=0)
   {
      while(p->next!=NULL)
      {
         if(strcmp(p->next->word,v)==0)
         {

            return true;
         }
         p = p->next;
      }
      return false;
   }
   return true;
}

void dic_free(dic **s)
{
   if (s != NULL)
   {
      dic *point = *s;
      free(point->table);
      free(point);
      *s = NULL;
   }
}







