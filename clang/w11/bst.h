#ifndef __BST__H__
#define __BST__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

enum bool {false, true};
typedef enum bool bool;

typedef struct dictinary 
{
   char *word;
   struct dictinary *left;
   struct dictinary *right;
   int dict_size;
} dic;

/* Cretate empty dict */
dic* dic_init(int size);

/* Add one element into the dict */
void dic_insert(dic*s, char *v);

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic*s, char *v);

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void dic_free(dic **s);

#endif
