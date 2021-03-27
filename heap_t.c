    #include<stdio.h>
    #include<limits.h>

    int heap[512], size;

    void create() {

        size = 0;

        heap[0] = -INT_MAX;

    }

     

    /*push an element into the heap */

    void push(int element) {

        size++;

        int pos = size;

        while (heap[pos / 2] > element) {

            heap[pos] = heap[pos / 2];

            pos /= 2;

        }

        heap[pos] = element;

    }

     

    int pop() {

        int min, max, child, pos;

        min = heap[1];

        max = heap[size--];

        for (pos = 1; pos * 2 <= size; pos = child) {

            child = pos * 2;

            if (child != size && heap[child + 1] < heap[child]) {

                child++;

            }

            if (max > heap[child]) {

                heap[pos] = heap[child];

            } else

            {

                break;

            }

        }

        heap[pos] = max;

        return min;

    }

     

    int main() {

        int number_of_elements;

        printf("Program to demonstrate Heap:\nEnter the number of elements: ");

        scanf("%d", &number_of_elements);

        int iter, element;

        create();

        printf("Enter the elements: ");

        for (iter = 0; iter < number_of_elements; iter++) {

            scanf("%d", &element);

            push(element);

        }

        for (iter = 0; iter < number_of_elements; iter++) {

            printf("%d ", pop());

        }

        printf("\n");

        return 0;

    }