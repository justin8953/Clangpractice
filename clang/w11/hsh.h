#ifndef __HSH__H__
#define __HSH__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 40000
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
enum bool {false, true};
typedef enum bool bool;
typedef struct dictype {char* word; struct dictype *next;} dictype;
typedef struct dictinary 
{
   dictype *p;
   int sz; 
} dic;

/* Cretate empty dict */
dic* dic_init(int size);
dictype *chain_initi(char *v);
bool check_table_full(dic *s);
int hash(char *s,int tablesize);

/* Add one element into the dict */
void dic_insert(dic*s, char *v);

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic*s, char *v);

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void dic_free(dic **s);


#endif
