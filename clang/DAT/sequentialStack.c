#include<stdio.h>
#include<assert.h>

#define STACKSIZE 200

struct stackelem
{
	int i;
};
typedef struct stackelem Elem;

struct thestack
{
	Elem stk[STACKSIZE];
	int top; 
};
typedef struct thestack Stack;

void InitialiseStack(Stack *s);
void Push(Stack *s, int n);
int Pop (Stack *s);

int main(void)
{
	Stack s;
	InitialiseStack (&s);
	Push(&s,12);
	Push(&s, 117);
	Push(&s, 13);
	Push(&s, 15);
	printf("%d \n", Pop(&s));
	printf("%d \n", Pop(&s));
	printf("%d \n", Pop(&s));
	printf("%d \n", Pop(&s));
	printf("%d \n", Pop(&s));
}

void InitialiseStack(Stack *s)
{
	s->top = 0;
}
void Push (Stack *s, int n)
{
	/*Make sure stack doesn't overflow*/
	assert(s->top < STACKSIZE);
	s->stk[s->top].i = n;
	s->top = s->top + 1; 
}
int Pop (Stack *s)
{
	/*Can't pop empty stack*/
	assert(s->top>0);
	s->top = s->top -1;
	return s->stk[s->top].i;
}

