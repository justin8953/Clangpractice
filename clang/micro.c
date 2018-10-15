#include<stdio.h>

int min_press(int num);
int main(void){
   int num, min;
   printf("Type the time required \n ");
   while(scanf("%d", &num)==1){
      min = min_press(num);
      printf("Number of buttons press = %d \n", min);
   }
   return 0;
}

int min_press(int num){
   int btn []={1,6,60};
   int press, total;
   press = (int)((float)num / 10 + 0.5);
   if (press>btn[2]){
      if (press%btn[2]>btn[1]){
	 total = press/btn[2] + (press%btn[2])/btn[1]+(press%btn[2])%btn[1];
      }else{
	 total = press/btn[2]+ press%btn[2];
      }
   }else if(press>btn[1] && press<btn[2]){
	 total = press/btn[1]+press%btn[1];

   }else{
	 total = press;
   }
   return total;
}
