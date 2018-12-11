#include "hsh.h"

/* Hashing function*/
int hash(char *s, int size)
{
   unsigned long hash = HASHNUM;
   int c;
   while ((c=(*s++)))
   {
      hash = HASHMUTINUM* hash^c;
   }
   return (int)(hash%size);
}

/* DIC initialise
   1.Intialise the dictionary 
   2.Initialise the hash table
   3.Intialise the cell in hash talbe
   4.Set the size 
   5.Set the number of element = 0 
*/
dic* dic_init(int size)
{
   dic *dict;
   int i ;
   dict = (dic*)malloc(sizeof(dic));
   if (dict==NULL)
   {
      ON_ERROR("Creation of Dictionary Failed \n");
   }
   dict -> sz = size;
   dict -> num = 0;
   dict->table = (dictype **)calloc(size,sizeof(dictype));
   if (dict->table==NULL)
   {
      ON_ERROR("Creation of Table Failed \n");
   }
   for (i=0 ; i< dict -> sz; i++)
   {
      dict->table[i] = EMPTY;
   }
   return dict;
}
/*  Intialise the separate chain */
dictype *chain_initi(char *v)
{
   dictype *node;
   node = (dictype *)malloc(sizeof(dictype));
   node->word = (char *)malloc(sizeof(char)*(strlen(v)+1));
   return node;
}
/* Grow Table
      1. Create New Dict and Initialise 
         it size with 2 times large
      2. Rehash previous Dict and Insert
         into new Dict
      3. Store old dic in tempory place
         and Swap old and new dictionary
      4. free the old dictionary 
*/
void grow(dic *s)
{     
      dic *NewDict, tmp;
      dictype *p;
      int i;
      NewDict = dic_init(s->sz*GROWFACT);
      for (i=0; i<s->sz; i++)
      {

            p = s->table[i];
            while(p!=EMPTY)
            {
                  dic_insert(NewDict,p->word);
                  p = p->next;
                  
            }
      }
      tmp = *s;
      *s = *NewDict;
      *NewDict = tmp;
      dic_free(&NewDict);
      
}

/* 
   1. if number of element is over a factor 0.6 of 
      table size, then grow the table.
   2. get the index from hashing function. 
   3. Create new node and initialise it. 
      s->table[set_index] point to Next new node
      New node point back to the s->table[set_index] 
   4. number of element ++
*/
void dic_insert(dic*s, char *v)
{
   int set_index;
   dictype *Newnode;
   Newnode = chain_initi(v);
   strcpy(Newnode->word,v);
   set_index = hash(v,s->sz);
   Newnode ->next = s->table[set_index];
   s->table[set_index] = Newnode;
   s->num++;
   if (s->num >= s->sz*GROWCON)
   {
         grow(s);
   }
}
/* 
   1. get the index from hashing function 
   2. point to the cell, check if the word is the same
      return true. Else check the chain list.
*/
bool dic_isin(dic*s, char *v)
{
   int find_index;
   dictype *p;
   find_index = hash(v,s->sz); 
   p = s->table[find_index];
   while(p!=EMPTY)
   {
         if(strcmp(p->word,v)==0)
         {
            return true;
         }
         p = p->next;

   }
   return false;
}
/* 
   1. go into each cell in the table
   2. if cell is not empty, go into each chain
      and free the space.
   3. free the table and dict
*/
void dic_free(dic **s)
{
      int i;
      dic *pointer=*s;
      dictype *p,*next;
      for (i=0; i<pointer->sz;i++)
      {
            p = pointer->table[i];
            while(p!=EMPTY)
            {
                  next = p->next;
                  free(p->word);
                  free(p);
                  p = next;
            }
      }
      free(pointer->table);
      free(pointer);
}







