#include "stdio.h"
#include "limits.h"

int heap[512] = {0};
int size;

void create() {
	
	heap[0] = INT_MIN;
	size = 0;

}

void push(int value) {
	
	size++;
	int pos = size;
	
	heap[pos] = value;
	
	while ((heap[pos / 2] < value) && (pos / 2) > 0) {
		
		heap[pos] = heap[pos / 2];
		heap[pos / 2] = value;
		pos /= 2;
		
        }
}

int pop() {
	
	int max = heap[1];
	int child;
	int value;
	int pos = 1;
	
	printf("size: %d\n", size);
	
	heap[pos] = heap[size - 1];
	heap[size - 1] = 0;
	
	child = pos * 2;
	
	while (heap[child] > heap[pos]) {
		
		value = heap[pos];
		heap[pos] = heap[child];
		heap[child] = value;
		
		pos *= 2;
		child = pos * 2;
		
	}
	
	size--;
}
		

int main() {
	
	create();
	push(1);
	push(2);
	push(4);
	push(5);
	push(6);
	push(8);
	push(9);
	push(10);
	push(11);
	push(16);
	
	int i = 1;
	while (i < 16) {
		printf("%d ", heap[i]);
		i++;
	}
	
	printf("\n");
	
	pop();
	pop();
	pop();
	pop();
	
	i = 1;
	while (i < 16) {
		printf("%d ", heap[i]);
		i++;
	}
		
}