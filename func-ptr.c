#include<stdio.h>

int max(int x, int y);

void main(void) {
	int d;
	/* p 是函数指针 */	
	int (*p)(int,int) = max;
	d = p(1,2);
	printf("%d\n", d);
}

int max(int x, int y){
	return x > y ? x : y;
}
