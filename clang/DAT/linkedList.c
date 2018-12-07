#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXNAME 20

struct node
{
	 char name[MAXNAME];
	 struct node *next;
};

typedef struct node Node;

Node *AllocateNode(char *s);
void PrintList(Node *l);
Node *DeleteNode(Node *start, char *s)
Node *InListRescursive(Node *n, char *s);
void PrintListRecursive(Node *l);

int main(void)
{
	 char name[MAXNAME];
	 Node *start, *current;
	 
	 printf("Enter the first name : \n");
	 if (scanf("%s", name)==1)
	 {
		  start = current = AllocateNode(name);
	 }
	 else
	 {
		  return 1;
	 }
	 printf("Enter more name: \n ");
	 while (scanf("%s", name)==1)
	 {
		  current->next = AllocateNode(name);
		  current = current->next;
	 }
	 PrintList(start);
	 return 0 ;
}

Node *AllocateNode(char *s)
{
	 Node *p;
	 p = (Node *)malloc(sizeof(Node));
	 if(p == NULL)
	 {
		  printf("Cannot Allocate Node \n");
		  exit(2);
	 }
	 strcpy(p->name, s);
	 p->next = NULL;
	 return p ; 
}

void PrintList(Node *l)
{
	 printf("\n");
	 do
	 {
		  printf("Name : %s \n", l->name);
		  l = l->next; 
	 }while(l!=NULL);
	 printf("END \n");
}
Node *InList(Node *n, char *s)
{
	 do
	 {
		  if(strcmp(n->name,s)==0)
		  {
				return n;
		  }
		  n = n->next;
	 }while(n!= NULL);
	 return NULL;
}

Node *DeleteNode(Node *start, char *s)
{
	Node *prev, *l;
	/*First in list ?*/
	if (!strcmp(start->name, s))
		return start->next;
	l = start ; 
	do 
	{
		prev = l;
		l = l->next; 
		if (strcmp(l->name, s)==0)
		{
			prev ->next = l->next; 
			return start;
		}
	}while (l!=NULL)
	return start; 
}

void PrintListRecursive(Node *l)
{
	/*Recusive Base-Case*/
	if (l==NULL) return ;
	printf("Name : %s \n", l->name);
	PrintListRecursive(l->next);
}

Node *InListRescursive(Node *n, char *s)
{
	/*Recursive Base-Case*/
	if (n==NULL) return NULL;
	if (strcmp(n->name, s)==0) return n;
	return InListRecursive(n->next, s);
}

