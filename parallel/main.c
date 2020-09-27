#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct node {
    struct node *previousNode;
	int primeNumber;
	struct node *nextNode;
}node;

struct verifyIntervalArguments {
    int start;
    int end;
    int threadIndex;
};

node **resultsVector;
int resultsVectorSize;

bool isPrime(int number) {
    for (int i = 2; i <= number / 2; i++) {
        // condition for non-prime
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

void *verifyInterval(void *args) {
    struct verifyIntervalArguments *arguments = args;
    int start = arguments->start;
    int end = arguments->end;
    int threadIndex = arguments->threadIndex;
    // Creating the root node of my linked list with the first item as the number 0
    node *first = (node*)malloc(sizeof(node*));
    first->previousNode = NULL;
    first->primeNumber = 0;

    // Creating a pointer to the previous pointer
    node *previous = first;
    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            node *next = (node*)malloc(sizeof(node*));
            next->primeNumber = i;
            next->previousNode = previous;
            previous->nextNode = next;
            previous = next;
        }
    }
    resultsVector[threadIndex] = first->nextNode;
}

void printNumbers() {
    printf("Prime numbers found: \n");
    
    for(int i = 0; i < resultsVectorSize; i++) {
        bool hasNext = true;    
        while (hasNext) {
            if (resultsVector[i] != NULL) {
                printf("%d \n", resultsVector[i]->primeNumber);
                if (resultsVector[i]->nextNode != NULL) {
                    resultsVector[i] = resultsVector[i]->nextNode;
                } else {
                    hasNext = false;
                }
            } else {
                hasNext = false;
            }   
        }
    }
    free(resultsVector);
}

void createResultsVector(int totalOfItems) {
    node* link[totalOfItems];
    for(int q = 0; q < totalOfItems; q++) {
        link[q] = malloc(sizeof(node*));
    }
    resultsVector = link;
    resultsVectorSize = totalOfItems;    
}

int main(int argc, char *argv[]) {
    // If the user execute the program with a wrong argument throw the message bellow and interrupt the program
	if (argc != 3) {
		printf("Invalid Argument! ./ssdsdsse, call './main [limit] [num of threads]' >> e.g. './main 10000 5' \n");
		return 0;
	}

    // Type casting the char arguments to int
    int limit = atoi(argv[1]);
    int numOfThreads = atoi(argv[2]);
    
    // If the limit is less than 2, print the message below and interrupt the program
    if (limit < 2) {
        printf("\n This limit doesn't have prime numbers");
        return 0;
    } else if (numOfThreads > limit) {
        printf("\n The number of threads should be less or equal the limit");
        return 0;
    } else {
        printf("\n Analyzing numbers until this limit: %d \n", limit);
        pthread_t threads[numOfThreads]; 
        float xlimitPerThread = limit / numOfThreads;
        int start = 2;
        int end = limitPerThread;
        int rc;
        resultsVector = malloc(numOfThreads * sizeof(node*));
        resultsVectorSize = numOfThreads;

        struct verifyIntervalArguments arguments[numOfThreads];
        for(int i = 0; i < numOfThreads; i++) {
            printf("Arguments: %d, %d, %d \n", start, end, i);
            arguments[i].start = start;
            arguments[i].end = end;
            arguments[i].threadIndex = i;
            rc = pthread_create(&threads[i], NULL, verifyInterval, (void *)&arguments[i]);
            if (rc){
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }

            start = end+1;
            end = end + limitPerThread;
        }

        for(int j=0; j<numOfThreads; j++){
            pthread_join(threads[j], NULL);
        }

        printNumbers();
    }  
}