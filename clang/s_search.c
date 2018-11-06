#include<stdio.h>
#include<strings.h>

#define NUMPEOPLE 6


typedef struct key {
   char *name;
   int age; 
} Key;


int FindAge(char *name, Key *l, int n);


int main(void)
{
   int i, j;
   Key a[NUMPEOPLE]={
      {"Ackertby",21},
      {"Bloggs",25},
      {"Chumley",26},
      {"Dalton",25},
      {"Eggsoon",22},
      {"Fulton",41}
   };
   i = FindAge("Eggsoon", a, NUMPEOPLE);
   printf("%d \n", i);
   return 0;
}

int FindAge(char *name, Key *l, int n)
{
   int j; 
   for (j = 0; j<n; j++)
   {
      if(strcmp(name, l[j].name))
	 return l[j].age;
   }
   return -1;
}
