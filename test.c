#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * Paragem structure
 */
struct paragem {
    int data;
    char name[200];
    struct paragem * prev;
    struct paragem * next;
}*head, *last;



/*
 * Functions used in this program
 */
void createList(int n);
void displayList();
void reverseList();


int main()
{
    int n, data, choice=1;

    head = NULL;
    last = NULL;

    /*
     * Runs forever until user chooses 0
     */
    while(choice != 0)
    {
        printf("============================================\n");
        printf("DOUBLY LINKED LIST PROGRAM\n");
        printf("============================================\n");
        printf("1. Create List\n");
        printf("2. Reverse List\n");
        printf("3. Display list\n");
        printf("0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice : ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter the total number of nodes in list: ");
                scanf("%d", &n);
                createList(n);
                break;
            case 2:
                reverseList();
                break;
            case 3:
                displayList();
                break;
            case 0:
                break;
            default:
                printf("Error! Invalid choice. Please choose between 0-3");
        }

        printf("\n\n\n\n\n");
    }

    return 0;
}


/**
 * Creates a doubly linked list of n nodes.
 * @n Number of nodes to be created
 */
void createList(int n)
{
    int i;
    struct paragem *newNode;

    if(n >= 1)
    {
        /*
         * Create and link head node
         */
        head = (struct paragem *)malloc(sizeof(struct paragem));

        printf("\nEnter data of 1 node: ");
        scanf("%d", &head->data );
        printf("Enter name of 1 node: ");
        scanf("%s%*c", &head->name);

        head->prev = NULL;
        head->next = NULL;

        last = head;

        /*
         * Create and link rest of the n-1 nodes
         */
        
        for(i=2; i<=n; i++)
        {   
            newNode = (struct paragem *)malloc(sizeof(struct paragem));

            printf("\nEnter data of %d node: ", i);
            scanf("%d", &newNode->data);
            printf("Enter name of %d node: ", i);
            scanf("%s%*c", &newNode->name);
            
            newNode->prev = last; // Link new node with the previous node
            newNode->next = NULL;

            last->next = newNode; // Link previous node with the new node
            last = newNode; // Make new node as last/previous node
        }

        printf("\nDOUBLY LINKED LIST CREATED SUCCESSFULLY\n");
    }
}


/**
 * Mostar os cnoteudos da lista no ecrã
 */
void displayList()
{
    struct paragem * temp;
    int n = 1;

    if(head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    {
        temp = head;
        printf("DATA IN THE LIST:\n");

        while(temp != NULL)
        {
            printf("\nDATA of %d node = %d, nome: %s", n, temp->data, temp->name);

            n++;

            /* Move pointer to next node */
            temp = temp->next;
        }
    }
}

// Esta função ira reverter a lista duplamente ligada
void reverseList()
{
    struct paragem *current, *temp;

    current = head;
    while(current != NULL)
    {
        /*
         * moda o endereço do anterior e o seguinte do nó
         */
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;

        /* Moda  o current ponteiro para o proximo no que esta guardado em temp*/
        current = temp;
    }
    
    /* 
     * troca o head e o last d posição
     */
    temp = head;
    head = last;
    last = temp;

    printf("LIST REVERSED SUCCESSFULLY.\n");
}