#include<stdio.h>


int main(int argc, char *argv[])
{
	int x, y,z,p;
	x = '1';
	printf("%d \n", x);
	y = (int)*argv[1];
	p = (int)*argv[2];
	z = *argv[1];
	printf("%d %d %d %c\n",x, y, p, z );
	return 0;
}