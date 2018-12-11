#ifndef __BST__H__
#define __BST__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

enum bool {false, true};
typedef enum bool bool;

/* BST structure dictionary */
typedef struct dictionary 
{
   char *word;
   struct dictionary *left;
   struct dictionary *right;
} dic;

/* Cretate empty dict */
dic* dic_init(int size);

/* Add one element into the dict */
void dic_insert(dic*s, char *v);

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic*s, char *v);

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void dic_free(dic *s);

#endif
