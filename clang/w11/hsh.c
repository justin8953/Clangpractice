#include "hsh.h"



int hash(char *s, int tablesize)
{
   unsigned long hash = 5381;
   int c;
   while ((c=(*s++)))
   {
      hash = 33* hash^c;
   }
   return (int)(hash%tablesize);
}
bool check_table_full(dic *s)
{
   int i ;
   for (i= 0 ; i<s->sz;i++)
   {
      if (strcmp(s->p[i].word,"")==0)
      {
         return false;
      }
   }
   return true;
}
dic* dic_init(int size)
{
   dic * dict;
   int i ;
   dict = (dic*)calloc(1, sizeof(dic));
   if (dict==NULL)
   {
      ON_ERROR("Creation of Dictionary Failed");
   }
   dict->p = (dictype *)calloc(MAXSIZE, sizeof(dictype));
   if (dict->p==NULL)
   {
      ON_ERROR("Creation of Dictionary Failed");
   }
   for (i=0 ; i< MAXSIZE; i++)
   {
      dict->p[i].word = (char *)calloc(1, size);
   }
   dict ->sz = MAXSIZE;
   return dict;
}
dictype *chain_initi(char *v)
{
   dictype *p;
   p = (dictype *)calloc(1, sizeof(dictype));
   p->word = (char *)calloc(1, strlen(v)+1);
   return p;
}
void dic_insert(dic*s, char *v)
{
   int set_index;
   dictype *tmp,*pointer;
   pointer = chain_initi(v);
   pointer->next = NULL;
   strcpy(pointer->word,v);
   if (check_table_full(s))
   {
      s->p = (dictype *)realloc(s->p, sizeof(dictype)*s->sz+1);
      s->p[s->sz].word = (char *)calloc(1, strlen(v)+1);
      s->sz = s->sz +1;
   }
   if (s!=NULL)
   {
      set_index = hash(v,s->sz);
      tmp = &(s->p[set_index]);
      
      if(strcmp(tmp->word,"")!=0) 
      {
         while(tmp->next!=NULL)
         {
            tmp = tmp->next;
         }
         tmp->next = pointer;
      }else{
         strcpy(tmp->word,v);
      }
   }
}

bool dic_isin(dic*s, char *v)
{
   int find_index;
   dictype *tmp;
   find_index = hash(v,s->sz); 
   tmp = &(s->p[find_index]);
   if(strcmp(tmp->word,v)!=0)
   {
      while(tmp->next!=NULL)
      {
         if(strcmp(tmp->next->word,v)==0)
         {

            return true;
         }
         tmp = tmp->next;
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
      free(point->p);
      free(point);
      *s = NULL;
   }
}







