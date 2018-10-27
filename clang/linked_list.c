#include<stdio.h>
#include<stdlib.h>
#define TRUE 1 
#define FALSE 0
typedef struct tagListNode
{
   int data; 
   struct tagListNode*next;
}ListNode;
ListNode *GetPreNode(ListNode *head, ListNode *OldNode);
int DeleteNode(ListNode *head, ListNode *OldNode);
int InsertAfter(ListNode *p, int value);
int InsertTail(ListNode *head, int value);
void ListTraverse(ListNode *head);
int ListLength(ListNode *head);
int ListConnect(ListNode *listA, ListNode *listB);
int main(void){
   ListNode *head;
   head = (ListNode *)malloc(sizeof(ListNode));
   head->next=NULL;
   InsertTail(head, 20);
   InsertTail(head, 40);
   InsertTail(head, 10);
   InsertTail(head, 50);
   ListTraverse(head);
   printf("Length is %d \n",ListLength(head));
   return 0; 

}

ListNode *GetPreNode(ListNode *head, ListNode *OldNode){
   ListNode *p, *q;
   p = head;/* node */
   q = head->next; /*下一個指標*/
   while((q!=NULL)&&(q!=OldNode)){
      p =q;
      q = q->next;
   }
   if(q!=NULL){
      return p;
   }else
      return NULL;
}
int DeleteNode(ListNode *head, ListNode *OldNode){
   ListNode *PreNode;
   if (head == OldNode)
      return FALSE;
   PreNode = GetPreNode(head, OldNode);
   PreNode->next = OldNode->next;
   free(OldNode);
   return TRUE;
}
int InsertAfter(ListNode *p, int value){
   ListNode *NewNode;
   NewNode = (ListNode *)malloc(sizeof(ListNode));
   if (NewNode==NULL){
      return FALSE;
   }
   NewNode->data = value;
   NewNode->next = p->next ;
   p->next = NewNode;
   return TRUE;
}
int InsertTail(ListNode *head, int value){
   ListNode *NewNode, *p = head;
   NewNode = (ListNode *)malloc(sizeof(ListNode));
   if (NewNode == NULL){
      return FALSE;
   }
   NewNode->data = value;
   NewNode->next = NULL;
   while(p->next != NULL){
      p = p->next;
   }
   p->next =NewNode;
   return TRUE;
}
void ListTraverse(ListNode *head){
   ListNode *p = head;
   p = p->next ;
   while(p){
      printf("\n %d ", p->data);
      p = p->next;
   }
   printf("\n");
}
int ListLength(ListNode *head){
   int counter = 0;
   ListNode *p = head->next;
   while(p!=NULL){
      counter ++;
      p = p->next;
   }
   return counter;
}

int ListConnect(ListNode *listA, ListNode *listB){
   ListNode *p = listA;
   while (p->next!= NULL){
      p = p->next; 
   }
   p ->next = listB->next;
}
