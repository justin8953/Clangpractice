#include<iostream>
#define FALSE 0
#define TRUE 1
using namespace std;

int Enqueue(Q *q, int data);

int Dequeue(Q *q, int *p);

typedef struct Queue{
   int data;
   struct Queue *next;
}Q;



Q *front, *rear; 
front = new Q;
rear = new Q;
rear->next = front;

int main(void)
{
   

}

int Enqueue(Q *q, int data)
{
   if(q->next==front){
      return FALSE;   
   }
   q->next = q->next+1;
   q->data = data;
   return TRUE;
}
int Dequeue(Q *q, int *p){
   if(q->next==front)
   {
      return FALSE;
   }
   q->next = q->next+1;
   *p = q->data;
   return TRUE;
}



