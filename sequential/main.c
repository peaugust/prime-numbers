#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    struct node *previousNode;
	int primeNumber;
	struct node *nextNode;
}node;

bool isPrime(int number) {
    for (int i = 2; i <= number / 2; i++) {
        // condition for non-prime
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    // If the user execute the program with a wrong argument throw the message bellow and interrupt the program
	if (argc != 2) {
		printf("Invalid Argument! Please, call './main [limit]' >> e.g. './main 10' \n");
		return 0;
	}

    // Type casting the char argument to an int
    int limit = atoi(argv[1]);

    // If the limit is less than 2, print the message below and interrupt the program
    if (limit < 2) {
        printf("\n This limit doesn't have prime numbers");
        return 0;
    }

    printf("\n Analyzing numbers until this limit: %d \n", limit);
 
    // Creating a linked list with the first item as the number 2
    node *first = (node*)malloc(sizeof(node*));
    first->previousNode = NULL;
    first->primeNumber = 2;

    // Creating a pointer to the previous pointer
    node *previous = first;
    

    for (int i = 3; i <= limit; i++) {
        if (isPrime(i)) {
            node *next = (node*)malloc(sizeof(node*));
            next->primeNumber = i;
            next->previousNode = previous;
            previous->nextNode = next;
            previous = next;
        }
    }

    printf("Prime numbers found: \n");
    bool hasNext = true;
    node *linkedList = first;
    while (hasNext) {
        printf("%d \n", linkedList->primeNumber);
        if (linkedList->nextNode != NULL) {
            linkedList = linkedList->nextNode;
        } else {
            hasNext = false;
        }
    }
    free(first);
    free(previous);
    free(linkedList);   
}