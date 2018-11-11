//
//  ex_6-1.c
//  
//
//  Created by justin on 07/11/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NUM 25
#define CSEC (double)(CLOCKS_PER_SEC)

double execution_time(clock_t start, clock_t end);
int main(void)
{
    int num_words, i,j;
    char word[MAX_NUM][MAX_NUM], tmp[MAX_NUM];
    clock_t start, end;
    start = clock();
    printf("How many words you want to enter \n");
    scanf("%d", &num_words);
    printf("Please enter %d words \n", num_words);
    for(i=0; i<=num_words; i++)
    {
        gets(word[i]);
    }
    for(i=0; i<=num_words; i++)
    {
        for(j = i+1; j<=num_words; j++)
        {
            if(strcmp(word[i],word[j])>0)
            {
                strcpy(tmp,word[i]);
                strcpy(word[i],word[j]);
                strcpy(word[j],tmp);
            }
        }
    }
    for(i=0; i<=num_words;i++)
    {
        puts(word[i]);
    }
    end = clock();
    printf("Execution time is %lf \n", execution_time(start,end));
    return 0;
}
double execution_time(clock_t start, clock_t end)
{
    double spend_time;
    spend_time = (double)(start-end)/CSEC;
    return spend_time;
}
