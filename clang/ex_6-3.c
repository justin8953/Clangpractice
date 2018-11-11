//
//  ex_6-2.c
//  
//
//  Created by justin on 07/11/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_Length 25
#define CSEC (double)(CLOCKS_PER_SEC)

struct words_list
{
    char word[MAX_Length];
    struct words_list *next;
};

typedef struct words_list WordList;
WordList *AllocateNode(char *s);
void AlphabetSort(WordList *l, char *word);
void PrintfList(WordList *l);
int Findword(WordList *l, char *word);
double execution_time(clock_t start, clock_t end);
int main(void)
{
    int num_words, i;
    char word[MAX_Length], newWord[MAX_Length];
    WordList *start_node;
    
    clock_t start, end;
    start = clock();
    printf("How many words you want to enter \n");
    scanf("%d", &num_words);
    printf("Please enter %d words \n", num_words);
    for (i=0;i<=num_words;i++)
    {
        scanf("%s",word);
        if (i ==0)
        {
            start_node=AllocateNode(word);
        }
        else
        {
            AlphabetSort(start_node,word);
        }
    }
    PrintfList(start_node);
    scanf("%s", newWord);
    if(Findword(start_node, newWord))
    {
        printf("find the word \n");
    }else
    {
        printf("no this word \n");
    }
    end = clock();
    printf("Execution time is %lf \n", execution_time(start,end));
    return 0;
}
int Findword(WordList *l, char *word)
{
    while (l->next != NULL)
    {
        l = l->next;
        if (strcmp(l->word,word)==0)
        {
            return 1;
        }
    }
    return 0;
}
void AlphabetSort(WordList *l, char *word)
{
    WordList *new_node;
    while(l->next!=NULL && strcmp(l->word, word)>0)
    {
        l = l->next;
    }
    new_node = AllocateNode(word);
    new_node->next = l->next;
    l->next = new_node;
}
WordList *AllocateNode(char *s)
{
    WordList *p;
    p = (WordList *)malloc(sizeof(WordList));
    if (p==NULL)
    {
        printf("Cannot Allocate Node \n");
        exit(2);
    }
    strcpy(p->word, s);
    p->next = NULL;
    return p;
}
void PrintfList(WordList *l)
{
    printf("\n");
    do{
        printf("Word: %s \n", l->word);
        l = l->next;
    }while (l!=NULL);
    printf("END\n");
}

double execution_time(clock_t start, clock_t end)
{
    double spend_time;
    spend_time = (double)(start-end)/CSEC;
    return spend_time;
}