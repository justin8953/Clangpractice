#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>


int word_same(char word[], char input[],int length);
int word_in_list(FILE *fp, char input[],int length);
void arr(int num[],int length);
// void test_all(FILE *fp);
void print_arr(int num[], int length);
void swap(int *a, int*b);
void permute(int *a, int l, int r,char input[], char output[], FILE *fp);
void copy(char input [], char temp[], int length);

int main(void)
{
    FILE *fp;
    int *num, *pum, n ;
    char input [10], output[10];
    scanf("%s%s", input,output);

    // test_all(fp);
    n = strlen(input);
    num = (int*) malloc(n);
    arr(num,n);
    permute(num,0,n-1,input,output,fp);
    return 0;
}


void print_arr(int num[], int length)
{
    int i;
    for(i=0; i<length; i++)
    {
        printf("%d",num[i]);
    }
    printf("\n");
}


// void test_all(FILE *fp)
// {
//     assert(word_in_list(fp,"toys")==1);
//     assert(word_in_list(fp,"load")==1);
//     assert(word_in_list(fp,"and")==1);
//     // assert(word_in_list(fp,"tab")==1);
//     assert(word_in_list(fp,"arm")==1);
// }


int word_in_list(FILE *fp, char input[],int length )
{
    char *word;
    fp = fopen ("34words.txt","r");
    if (fp==NULL)
    {
        printf("open failed \n");
        return 1;
    }
    word = (char *)malloc(length);
    while(fscanf(fp,"%s\n", word)!=EOF)
    {
        if (word_same(word, input,length))
        {
            return 1;
        }
    }
    fclose(fp);
    return 0;
}


int word_same(char word[], char input[],int length )
{
    int i = 0;
    while(i!=length)
    {
        if(word[i]==input[i])
        {
            i++;
        }else{
            return 0;
        }
    }
    return 1;
}


int valid(int arr[], int length, char input[], char output[], FILE *fp)
{
    int i,pos;
    char *temp;
    temp = (char*)malloc(length);
    copy(input, temp,length);
    for (i=0;i<length; i++)
    {
        pos = arr[i];
        temp[pos] = output[pos];
        if (!word_in_list(fp, temp,length))
        {
            return 0;
        }
        
    }
    printf("%s \n",temp);
    return 1;
}


void arr(int num[],int length)
{
    int i; 
    for (i=0; i<length; i++)
    {
        num[i]= i;
    }
}


void swap(int *a, int*b)
{
    int temp = *a;
     *a = *b;
     *b = temp;    
}


void permute(int *a, int l, int r, char input[], char output[], FILE *fp)
{
    int i;
    static int num = 0;
    if (l == r)
    {
        if (valid(a,r+1,input,output,fp))
        {
            print_arr(a,r+1);
        }
    }
    for(i=l; i<=r; i++)
    {
        swap((a+l),(a+i));
        permute(a, l+1, r, input, output, fp);
        swap((a+l),(a+i));
    }
}
void copy(char input [], char temp[], int length)
{
    int i; 
    for (i=0; i<length; i++)
    {
        temp[i]= input[i];
    }
}
