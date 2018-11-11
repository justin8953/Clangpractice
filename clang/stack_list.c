#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #define STACKSIZE 200

struct stackelem
{
    int i;
    struct stackelem *prev;
};
typedef struct stackelem Elem;

struct thestack
{
    Elem *tp;
};
typedef struct thestack Stack;

void InitialiseStack(Stack *s);
void Push(Stack *s, int n);
int Pop(Stack *s);

int main(void)
{ 
    Stack s;
    InitialiseStack(&s);

    Push(&s, 12);
    Push(&s, 117);
    Push(&s, 13);
    Push(&s, 15);
    printf("Pop : %d \n",Pop(&s));
    printf("Pop : %d \n",Pop(&s));
    printf("Pop : %d \n",Pop(&s));
    printf("Pop : %d \n",Pop(&s));
    printf("Pop : %d \n",Pop(&s));
    return 0 ;

}

void InitialiseStack(Stack *s)
{
    s->tp = (Elem *)calloc(1, sizeof(Elem));
    s->tp->prev = NULL;
}
void Push(Stack *s, int n)
{ 
    Elem *e;
    e = (Elem *)calloc(1, sizeof(Elem));
    e->prev = s->tp; 
    s->tp->i = n;
    s->tp = e;
}
int Pop(Stack *s)
{
    s->tp = s->tp->prev;
    assert(s->tp!=NULL);
    return s->tp->i;
}


// This is seqential stack

// struct stackelem
// {
//     int i;
// };
// typedef struct stackelem ELEM;

// struct thestack
// {
//     ELEM stk[STACKSIZE];
//     int top;
// };
// typedef struct thestack Stack;


// void InitialiseStack(Stack *s);
// void Push(Stack *s, int n);
// int Pop(Stack *s);

// int main(void)
// { 
//     Stack s;
//     InitialiseStack(&s);

//     Push(&s, 12);
//     Push(&s, 117);
//     Push(&s, 13);
//     Push(&s, 15);
//     printf("Pop : %d \n",Pop(&s));
//     printf("Pop : %d \n",Pop(&s));
//     printf("Pop : %d \n",Pop(&s));
//     printf("Pop : %d \n",Pop(&s));
//     printf("Pop : %d \n",Pop(&s));
//     return 0 ;

// }

// void InitialiseStack(Stack *s)
// {
//     s->top = 0;
// }
// void Push(Stack *s, int n)
// {
//     /*Make sure stack doese overflow*/
//     assert(s->top < STACKSIZE);
//     s->stk[s->top].i = n;
//     s->top = s->top + 1;
// }
// int Pop(Stack *s)
// {
//     assert(s->top>0);
//     s->top = s->top - 1;
//     return s->stk[s->top].i;
// }
