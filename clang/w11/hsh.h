#ifndef __HSH__H__
#define __HSH__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum bool {false, true};
typedef enum bool bool;
/* dictionary hash table type :
   1 cell can store word and linked list
   for solving collision. 
*/
struct dictype {
   char *word; 
   struct dictype *next;
};
typedef struct dictype dictype;

/* dictionary hash table 
   sz is the size of the dictionary
   num number of element in dictionary
*/
struct dictinary 
{
   dictype **table;
   int num;
   int sz; 
};
typedef struct dictinary dic;

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
