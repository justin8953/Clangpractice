#include<stdio.h>
#include<stdlib.h>
#define Max_item 5 
#define TRUE 1 
#define FALSE 0
typedef struct tagStack{
   int data; 
   struct tagStack *Top; 
} Stack;
int Push (Stack *head , int value );
int Pop(Stack *head);
void initialize(Stack *head);
int main(void){
   Stack *head;
   initialize(head);
   Push(head, 100);
   Push(head, 50);
   Push(head, 30);
   Push(head, 10);
   Push(head, 20);
   Pop(head);

   return 0 ; 
}
void initialize(Stack *head){
   head = (Stack *)malloc(sizeof(Stack));
   head ->Top = NULL;
}
int Push (Stack *head , int value ){
   Stack *p;
   p = (Stack*)malloc(sizeof(Stack));
   if (p==NULL)
   {
      printf("Failed\n");
      return FALSE;
   }
   p->data = value;
   p->Top  = head ->Top;
   head->Top = p;
   printf("Push in %d \n", p->data);
   return TRUE;

}

int Pop(Stack *head){
   Stack *current;
   current = head->Top;
   printf("%d \n", current->data);
   if (current ==NULL)
   {
      printf("empty now \n");
      return FALSE;
   }
   printf("%d is poped \n", current->data);
   head->Top = current->Top;
   return TRUE;

}

