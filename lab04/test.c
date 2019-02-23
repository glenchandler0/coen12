#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "deque.c"

int main(void)
{
	DEQUE *list = createDeque();
	addFirst(list, 999);
	addFirst(list, 101);
	printf("First: %d\n", getFirst(list));
	removeFirst(list);
	printf("First: %d\n", getFirst(list));
}
