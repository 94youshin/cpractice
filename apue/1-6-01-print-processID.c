#include "apue.h"

int main(void) {
	printf("hello world from process ID %1d\n", getpid());
	printf("hello world from process ID %1d\n", getppid());
}
