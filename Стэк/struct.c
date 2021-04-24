#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

struct elem {
	long tel;
	char* name;
	struct elem *prev;
} *sa, *temp_sa;

int counter = 0;

int push(long tel, char* name) {
	struct elem *new = (struct elem*)malloc(sizeof(struct elem));
	if (counter != 0)
		 new->prev = sa;
	sa = new;
	counter++;
	new->tel = tel;
	new->name = name;
	/*
	printf("sa: %x\n", sa);
	printf("new->prev: %x\n", new->prev);
	printf("counter: %d\n", counter);
	*/
	return 0;
}

int pop() {
	if (counter != 0) {
		printf("Telephone: %d\n", sa->tel);
		printf("Username:  %s\n\n", sa->name);
		
		temp_sa = sa->prev;
		free(sa);
		sa = temp_sa;
		counter--;
	}
	else printf("Stack is empty\n");
	return 0;
}	
	
int main() {
	push(5550101, "Alex");
	push(5550202, "Boris");
	push(5550303, "Peter");
	push(5550404, "Gleb");
	pop();
	pop();
	pop();
	pop();
	return 0;
}
