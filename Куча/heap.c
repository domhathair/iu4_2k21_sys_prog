#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

struct heap {
	int array[512];
	int size;
};

struct heap *create() {
	
	struct heap *hp = (struct heap*)malloc(sizeof(struct heap));
	
	hp->size = 0;
	hp->array[0] = INT_MAX;
	
	return hp;
	
}

void heal(struct heap *hp, int pos) {
	
	int lch = pos * 2;
	int rch = (pos * 2) + 1;
	int par = pos;
	
	int temp;
	
	if ((lch <= hp->size) && (hp->array[lch] > hp->array[par]))
		par = lch;
		
	if ((rch <= hp->size) && (hp->array[rch] > hp->array[par]))
		par = rch;
		
	if (par != pos) {
		temp = hp->array[pos];
		hp->array[pos] = hp->array[par];
		hp->array[par] = temp;
		heal(hp, par);
	}
	
	return;
	
}

void push(struct heap *hp, int val) {
	
	int temp;
	int size;
	
	hp->size++;
	size = hp->size;
	
	//printf("hp->size: %d\n", hp->size);
	hp->array[size] = val;
	
	while ((size > 1) && (hp->array[size / 2] < hp->array[size])) {
		temp = hp->array[size / 2];
		hp->array[size / 2] = hp->array[size];
		hp->array[size] = temp;
		size /= 2;
	}
	
	return;
	
}
		
int pop(struct heap *hp) {
	
	int max;
	
	if (hp->size == 0)
		printf("Heap is empty!\n");
		
	max = hp->array[1];
	hp->array[1] = hp->array[hp->size];
	
	hp->size--;
	//printf("hp->size: %d\n", hp->size);
	
	heal(hp, 1);
	
	hp->array[hp->size + 1] = 0;
	
	return max;
	
}
	
int main() {
	
	struct heap *set = create();
	
	int size;
	
	printf("\nEnter number of values: \n");
	scanf("%d", &size);
	
	printf("\nFilling array with: \n");
	
	for (int i = 1; i < size + 1; i++) {
		int j = i * 2;
		push(set, j);
		printf("%d ", j); 
	}
	
	printf("\n\nFilled array:\n");	
	
	for (int i = 1; i < size + 1; i++)
		printf("%d ", set->array[i]);
	
	printf("\n\nPopped out values: \n");
	
	for (int i = 1; i < (size - size / 2); i++) {
		int j = pop(set);
		printf("%d ", j);
	}
		
	printf("\n\nRemaining array: \n"); 
	
	for (int i = 1; i < (size + 2 - (size - size / 2)); i++)
		printf("%d ", set->array[i]);

	printf("\n");
	
	return 0;
		
}
