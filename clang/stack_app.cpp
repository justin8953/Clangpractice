#include<iostream>
/*if ... return 1 else return 0  ?1:0*/
#define MAX_OP 5
#define operators(ch) (ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')?1:0
#define operands(ch) ((ch>='a')&& (ch<='z'))?1:0
#define MAX_SIZE 100
using namespace std;
int priority(char ch);
void in_to_post(char *infix, char *postfix);
void Push(int x);
void Pop(int *x);
typedef struct stk{
   char item[MAX_SIZE];
   int top ;
}stk;

stk S;
char op[MAX_OP]={ '(', '+', '-', '*', '/'};
int prio[MAX_OP]= {0, 1, 1, 2, 2};
int main(void){


   return 0 ;
}
void Push(int x )
{
   if (S.top<MAX_SIZE-1)
   {
      S.top++;
      S.item[S.top]=x;
   }
}
void Pop (int *x)
{
   if (S.top>=0)
   {
      *x = S.item[S.top];
      S.top--;
   }
}
int priority(char ch)
{
   int i;
   for (i=0; i<MAX_OP; i++)
   {
      if (op[i]== ch)
	 return (prio[i]);
   }
   return (-1);
}
void in_to_post(char *infix, char *postfix)
{
   int i, j, element;
   char token;
   i = j = 0;
   while((token = infix[i])!='\0')
   {
      i = i+1;
      if (operands(token))/*operator sends to postfix */
	 postfix[j++]=token;
      else if (token =='(')
	 Push(token);
      else if(token ==')')
      {
	 while(S.top>=0){
	    Pop(&element);
	    if (element == '(')
	       break;
	    postfix[j++] = element;
	 }
      }
      else if (operators(token))
      {
	 while(S.top>=0)
	 {
	    element = S.item[S.top];
	    if (priority(token)<= priority(element))
	    {
	       Pop(&element);
	       postfix[j++] = element;
	    }
	    else
	       break;
	 }
	 Push(token);
      }
      while (S.top>=0)
      {

	 Pop(&element);
	 postfix[j++]= element;
      }
      postfix[j]='\0';

   }

}
