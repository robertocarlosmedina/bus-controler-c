#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


#define CAPACIDADE 31    // máxima capacidade do autocarro


/* defenição estrutura pessoa */
typedef struct pessoa
{
    int id;
    struct pessoa * next;
} Fila;    // Fila é uma typedef da struct pessoa

/* para controlar quantas pessoas estão no autocarro */
unsigned int nrPessoasAutocarro = 0;


int enqueue(Fila ** rear, Fila ** front, int id);
int dequeue(Fila ** front);
int isEmpty();
int isFull();


int main()
{
    int ch, id,nrPessoasEntrada, nrPessoasSaida, i;
    Fila *rear, *front;

    rear  = NULL;
    front = NULL;
    srand(time(NULL));  

    /* Run indefinitely until user manually terminates */
    while (1)
    {
        /* Queue menu */
        printf("--------------------------------------------\n");
        printf("  QUEUE LINKED LIST IMPLEMENTATION PROGRAM  \n");
        printf("--------------------------------------------\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Size\n");
        printf("4. Get Rear\n");
        printf("5. Get Front\n");
        printf("0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Select an option: ");

        scanf("%d", &ch);

        
        /* Menu control switch */
        switch (ch)
        {
            case 1:
                nrPessoasEntrada = 0 + rand()%(CAPACIDADE-nrPessoasAutocarro);                
                
                // Enqueue function returns 1 on success
                // otherwise 0
                if (!isFull()){
                    for(i=0; i<nrPessoasEntrada; i++){
                        if (enqueue(&rear, &front, nrPessoasAutocarro+1))
                            printf("Element added to queue.");
                        else
                            printf("Queue is full.");
                    }
                }
                break;

            case 2:
                if(!isEmpty()){
                    nrPessoasSaida = 0 + rand()%(nrPessoasAutocarro);  
                    // on success dequeue returns element removed
                    // otherwise returns INT_MIN
                
                    for(i=0; i<nrPessoasSaida; i++){
                        id = dequeue(&front);
                        if (id == INT_MIN)
                            printf("Queue is empty.");
                        else
                            printf("Data => %d", id);
                    }
                }
                
                break;

            case 0:
                printf("Exiting from app.\n");
                exit(0);
        
            default:
                printf("Invalid choice, please input number between (0-5).");
                break;
        }

        printf("\n\n");
    }
}



/**
 * Enqueues/Insert an element at the rear of a queue.
 * Function returns 1 on success otherwise returns 0.
 */
int enqueue(Fila ** rear, Fila ** front, int id)
{
    Fila * newNode = NULL;

    // Check queue out of capacity error
    if (isFull())
    {
        return 0;
    }

    // Create a new node of queue type
    newNode = (Fila *) malloc (sizeof(Fila));

    // Assign data to new node
    newNode->id = id;

    // Initially new node does not point anything
    newNode->next = NULL;

    // Link new node with existing last node 
    if ( (*rear) )
    {
        (*rear)->next = newNode;
    }
    

    // Make sure newly created node is at rear
    *rear = newNode;

    // Link first node to front if its NULL
    if ( !( *front) )
    {
        *front = *rear;
    }

    // Increment quque size
    nrPessoasAutocarro++;

    return 1;
}


/**
 * Dequeues/Removes an element from front of the queue.
 * It returns the element on success otherwise returns 
 * INT_MIN as error code.
 */
int dequeue(Fila ** front)
{
    Fila *toDequque = NULL;
    int id = INT_MIN;

    // Queue empty error
    if (isEmpty())
    {
        return INT_MIN;
    }

    // Get element and data to dequeue
    toDequque = *front;
    id = toDequque->id;

    // Move front ahead
    *front = (*front)->next;

    // Decrement size
    nrPessoasAutocarro--;

    // Clear dequeued element from memory
    free(toDequque);

    return id;
}


/**
 * Checks, if queue is empty or not.
 */
int isEmpty()
{
    return (nrPessoasAutocarro <= 0);
}


/**
 * Checks, if queue is within the maximum queue capacity.
 */
int isFull()
{
    return (nrPessoasAutocarro >= CAPACIDADE);
}