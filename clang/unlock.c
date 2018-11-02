#include <stdio.h>
#define height 3
#define width 3
void initial(int lock[height][width]);
void print_arr(int lock[height][width]);
int go_right(int lock[height][width], int i, int j, int num, int end);
int go_left(int lock[height][width], int i, int j, int num, int end);
int go_up(int lock[height][width], int i, int j, int num, int end);
int go_buttom(int lock[height][width], int i, int j, int num, int end);
void start_game_2(int lock[height][width],int num);
void start_game_1(int lock[height][width],int num);
int main(void)
{
    int lock[height][width];
    start_game_1(lock,10);
    // start_game_2(lock,10);
    // start_game_1(lock,8);
    
    return 0;
}
// void start_game_3(int lock[height][width],int num)
// {
//     int i=j=0;
//     int start_num = 1;
//     initial(lock);
//     lock[i][j]= start_num++;
//     go_up(lock,i,j,start_num);
//     printf("\n");
//     start_num = 1;
//     initial(lock);
//     lock[i][j]= start_num++;
//     go_right(lock,i,j,start_num);
// }
void start_game_1(int lock[height][width],int num)
{
    int i=0,j=0;
    int start_num = 1;
    initial(lock);
    lock[i][j]= start_num++;
    go_up(lock,i,j,start_num,num);
    printf("\n");
    start_num = 1;
    initial(lock);
    lock[i][j]= start_num++;
    go_right(lock,i,j,start_num,num);
}
void start_game_2(int lock[height][width],int num)
{
    int i=1,j=0;
    int start_num = 1;
    initial(lock);
    lock[i][j]= start_num++;
    go_buttom(lock,i,j,start_num,num);
    printf("\n");
    start_num = 1;
    initial(lock);
    lock[i][j]= start_num++;
    go_right(lock,i,j,start_num,num);
    printf("\n");
    start_num = 1;
    initial(lock);
    lock[i][j]= start_num++;
    go_up(lock,i,j,start_num,num);
}
void initial(int lock[height][width])
{
    int i, j;
    for (i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            lock[i][j]=0;
        }
    }
}
void print_arr(int lock[height][width])
{   int i, j ;
    for (i = 0; i<height; i++)
    {
        for(j=0;j<width;j++)
        {
            printf("%2d",lock[i][j]);
        }
        printf("\n");
    }
}
void copy(int lock[height][width], int temp[height][width])
{
    int i,j;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            temp[i][j]=lock[i][j];
        }
    }

}
int go_right(int lock[height][width], int i, int j, int num, int end)
{
    int temp [height][width] , temp2 [height][width], temp3 [height][width];
    if(num==end){
        printf("success \n");
        print_arr(lock);
    }
    if(lock[i][j+1]==0&&(j+1)<width)
    {   
        copy(lock,temp);
        temp[i][j+1] = num;
        go_right(temp,i,j+1,num+1,end);
    }
    if(lock[i-1][j]==0&&(i-1)>=0)
    {   
        copy(lock,temp2);
        temp2[i-1][j]= num;  
        go_buttom (temp2,i-1, j, num+1,end);
    
    }
    if(lock[i+1][j]==0&&(i+1)<height)
    {   
        copy(lock,temp3);
        temp3[i+1][j] = num;
        go_up(temp3,i+1,j,num+1,end); 
    }else{
        return 0;
    }
    return 1; 
}
int go_left(int lock[height][width], int i, int j, int num, int end)
{
    int temp [height][width] , temp2 [height][width], temp3 [height][width];
    if(num==end){
        printf("success \n");
        print_arr(lock);
    }
    if(lock[i+1][j]==0&&(i+1)<height)
    {   
        copy(lock,temp);
        temp[i+1][j] = num;
        go_up(temp,i+1,j,num+1,end);
    
    }
    if(lock[i][j-1]==0&&(j-1)>=0)
    {   
        copy(lock,temp2);
        temp2[i][j-1] = num;
        go_left(temp2,i,j-1,num+1,end);
    }
    if(lock[i-1][j]==0&&(i-1)>=0)
    {   

        copy(lock,temp3);
        temp3[i-1][j]= num;
        go_buttom (temp3,i-1, j, num+1,end);
    }else{
        return 0;
    }
    return 1;
    
}
int go_up(int lock[height][width], int i, int j, int num, int end)
{
    int temp [height][width] , temp2 [height][width], temp3 [height][width];

    if(num==end){
        printf("success \n");
        print_arr(lock);     
    }
    if(lock[i+1][j]==0&&(i+1)<height)
    {   
        copy(lock,temp);
        temp[i+1][j] = num;
        go_up(temp,i+1,j,num+1,end);
    }
    if(lock[i][j+1]==0&&(j+1)<width)
    {   
        copy(lock,temp2);
        temp2[i][j+1]= num;
        go_right (temp2,i, j+1, num+1,end); 
    }
    if(lock[i][j-1]==0&&(j-1)>=0)
    {   

        copy(lock,temp3);
        temp3[i][j-1] = num;
        go_left(temp3,i,j-1,num+1,end);  
    }else{
        return 0;
    }
    return 1;
}
int go_buttom(int lock[height][width], int i, int j,int num, int end)
{
    int temp [height][width] , temp2 [height][width], temp3 [height][width];

    if(num==end){
        printf("success \n");
        print_arr(lock);
    }
    if(lock[i-1][j]==0&&(i-1)>=0)
    {   
        copy(lock,temp);
        temp[i-1][j] = num;
        go_buttom(temp,i-1,j,num+1,end);
      
    }
    if(lock[i][j-1]==0&&(j-1)>=0)
    {   
        copy(lock,temp2);
        temp2[i][j-1] = num;
        go_left(temp2,i,j-1,num+1,end);   
    }
    if(lock[i][j+1]==0&&(j+1)<width)
    {   
        copy(lock,temp3);
        temp3[i][j+1]= num;
        go_right (temp3,i, j+1, num+1,end);
    }else{
        return 0;
    }
    return 1;
}
