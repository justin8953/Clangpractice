#include<stdio.h>
#define height 20
#define width 20
void print_arr(char maze[height][width]);
void intitial(char maze[height][width]);
int check(char maze[height][width], int i , int j);
int upper_route(char maze[height][width], int i, int j);
int lower_route(char maze[height][width], int i, int j);
int left_route(char maze[height][width], int i, int j);
int right_route(char maze[height][width], int i, int j);
int end(char maze[height][width], int i, int j);
int main(void)
{
   FILE *fp;
   char maze[height][width];
   int i,j=0,k=0 ;
   intitial(maze);
   fp = fopen("maze.txt","r");
   if (fp==NULL)
   {
      printf("Cannot open \n");
      return 1;
   }
   while ((i= getc(fp))!=EOF)
   {
      if (i == '\n')
      {
          k=0;
          j++;
      }
      maze[j][k]= i;
      k++;
   }
   maze[10][10] = '\0';
   print_arr(maze);
   j =2 ; k=0;
   right_route(maze, j,k);
   print_arr(maze);
   return 0 ;
}

void intitial(char maze[height][width])
{
   int i, j;
   for (i=0;i<height;i++)
   {
      for(j=0;j<width;j++)
      {
          maze[i][j]=' ';
      }
   }
}
void print_arr(char maze[height][width])
{
   int i, j;
   for (i=0;i<height;i++)
   {
      for (j=0; j<width;j++)
      {
          printf("%c",maze[i][j]);
      }
   }
   printf("\n");
}
// int find_route(char maze[height][width], int i , int j)
// {


// }
// int check(char maze[height][width], int i , int j)
// {
//     if (maze[i][j+1]=='#'){
//         return 0;
//     }else if (maze[i+1][j]='#'){
//         return 0;
//     }else if (maze[i-1][j]='#'){
//         return 0;
//     }else
//         return 1;
// }
// int check(char maze[height][width], int i , int j)
// {
//     if (end (maze, i , j)){
//         return 1;
//     }
//     if (maze[i][j+1]==' '){
//         printf("maze[%d][%d] have route \n", i, j+1);
//         return check(maze, i, j+1);
//     }
//     if (maze[i+1][j]==' '){
//         printf("maze[%d][%d] have route \n", i+1, j);
//         return check(maze, i+1, j);
//     }
//     if (maze[i-1][j]==' '){
//         printf("maze[%d][%d] have route \n", i-1, j);
//         return check(maze, i-1, j);
//     }
//     else{
//         printf("maze has no route \n");
//         return 0;
//     }
// }
int upper_route(char maze[height][width], int i, int j)
{
    if (end(maze, i, j))
    {
        
        printf("success escape \n");
        return 1;
    }
    if (maze[i+1][j]==' '){
        maze[i+1][j]='.';
        printf("maze[%d][%d] have route \n", i+1, j);
        return upper_route(maze, i+1, j);
    }
    if (maze[i][j-1]==' '){
        maze[i][j-1] = '.';
        printf("maze[%d][%d] have route \n", i, j-1);
        return left_route(maze, i, j-1);
    }
    if (maze[i][j+1]==' '){
        maze[i][j+1] = '.';
        printf("maze[%d][%d] have route \n", i, j+1);
        return right_route(maze, i, j+1);
    }else{
        printf("no  route \n");
        return 0 ;
    }
}
int lower_route(char maze[height][width], int i, int j)
{
    if (end(maze, i, j))
    {
        printf("success escape \n");
        return 1;
    }
    if (maze[i-1][j]==' '){
        maze[i-1][j]='.';
        printf("maze[%d][%d] have route \n", i-1, j);
        return lower_route(maze, i-1, j);
    }
    if (maze[i][j+1]==' '){
        maze[i][j+1]='.';
        printf("maze[%d][%d] have route \n", i, j+1);
        return right_route(maze, i, j+1);
    }
    if (maze[i][j-1]==' '){
        maze[i][j-1]='.';
        printf("maze[%d][%d] have route \n", i, j-1);
        return left_route(maze, i, j-1);
    }else{
        printf("no  route \n");
        return 0 ;
    }
}
int left_route(char maze[height][width], int i, int j)
{
    if (end(maze, i, j))
    {
        printf("success escape \n");
        return 1;
    }
    if (maze[i][j-1]==' '){
        maze[i][j-1]='.';
        printf("maze[%d][%d] have route \n", i, j-1);
        return left_route(maze, i, j-1);
    }
    if (maze[i+1][j]==' '){
        maze[i+1][j]='.';
        printf("maze[%d][%d] have route \n", i+1, j);
        return upper_route(maze, i+1, j);
    }
    if (maze[i-1][j]==' '){
        maze[i-1][j]='.';
        printf("maze[%d][%d] have route \n", i-1, j);
        return lower_route(maze, i-1, j);
    }else{
        printf("no  route \n");
        return 0 ;
    }
}
int right_route(char maze[height][width], int i, int j)
{
    if (end(maze, i, j))
    {
        printf("success escape \n");
        return 1;
    }
    if (maze[i][j+1]==' '){
        maze[i][j+1]='.';
        printf("maze[%d][%d] have route \n", i, j+1);
        return right_route(maze, i, j+1);
    }
    if (maze[i-1][j]==' '){
        maze[i-1][j]='.';
        printf("maze[%d][%d] have route \n", i-1, j);
        return lower_route(maze, i-1, j);
    }
    if (maze[i+1][j]==' '){
        maze[i+1][j]='.';
        printf("maze[%d][%d] have route \n", i+1, j);
        return upper_route(maze, i+1, j);
    }else{
        printf("no  route \n");
        return 0 ;
    }
}
int end(char maze[height][width], int i, int j)
{
    if (maze[i][j+1]=='\0'){
        printf("maze[%d][%d] have solved \n", i, j+1);
        return 1;
    }
    if (maze[i+1][j]=='\0'){
        printf("maze[%d][%d] have solved \n", i+1, j);
        return 1;
    }
    if (maze[i-1][j]=='\0'){
        printf("maze[%d][%d] have solved \n", i-1, j);
        return 1;
    }
    if (maze[i][j-1]=='\0'){
        printf("maze[%d][%d] have solved \n", i-1, j);
        return 1;
    }
    return 0;
}

