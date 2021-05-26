#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/*
 * Paragem structure
 */
struct paragem {
    int data;
    char name[1][200];
    struct paragem * prev;
    struct paragem * next;
}*head, *last;

/*
 * Functions used in this program
 */
void criarListaParagems();
void listarParagems();
void reverterLista();
void adicionarParagem();
int gerarTempoRandom();

int main()
{
    int n, data, choice=1;

    head = NULL;
    last = NULL;
    srand(time(NULL));    

    while(choice != 0)
    {
        printf("============================================\n");
        printf("DOUBLY LINKED LIST PROGRAM\n");
        printf("============================================\n");
        printf("1. Create List\n");
        printf("2. Reverse List\n");
        printf("3. Display list\n");
        printf("4. Add to list\n");
        printf("0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice : ");

        scanf("%d", &choice);
        

        switch(choice)
        {
            case 1:
                criarListaParagems();
                break;
            case 2:
                reverterLista();
                break;
            case 3:
                listarParagems();
                break;
            case 4:
                adicionarParagem();
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
// gera valores de 10 a 20s relativo ao tempo de deslocamento de uma paragem a outra 
int gerarTempoRandom(){
    return  10 + rand()%20;;
}

/**
 * cria uma lista duplamente ligada com paragems ja previamente defenidades
 */
void criarListaParagems()
{
    int i;
    struct paragem *newNode;
    char paragensAPriori[3][20];
    stpcpy(paragensAPriori[0], "Cruz");
    stpcpy(paragensAPriori[1], "Lajinha");
    stpcpy(paragensAPriori[2], "Mederalzinho");
    stpcpy(paragensAPriori[3], "Regala");
    stpcpy(paragensAPriori[3], "Estrela");

    /*
     * Criar um link no nó head
     */
    head = (struct paragem *)malloc(sizeof(struct paragem));
    head->data =10 + rand()%10;
    strcpy(head->name[0], paragensAPriori[0]);
    head->prev = NULL;
    head->next = NULL;
    last = head;

    /*
     * Criar e linkar o resto dos n-1 nós
     */
    
    for(i=1; i<=3; i++)
    {   
        newNode = (struct paragem *)malloc(sizeof(struct paragem));
        newNode->data=10 + rand()%10;
        strcpy(newNode->name[0], paragensAPriori[i]);
        
        newNode->prev = last; // Linkar o novo nó com o anterior
        newNode->next = NULL;
        last->next = newNode; // Linkar o nó anterior como novo nó
        last = newNode; // Fazer com que o novo nó seja o ultimo/anterior nó
    }
    // printf("\nLista criada\n");
}
/**
 * Adicionar uma nova paragem a lista
 */
void adicionarParagem()
{
    int i;
    struct paragem *newNode;

    newNode = (struct paragem *)malloc(sizeof(struct paragem));

    newNode->data=10 + rand()%10;
    printf("Digite o nome da paragem: ");
    scanf("%s", newNode->name[0]);
    
    newNode->prev = last; // Linkar o novo nó com o anterior
    newNode->next = NULL;
    last->next = newNode; // Linkar o nó anterior como novo nó
    last = newNode; // Fazer com que o novo nó seja o ultimo/anterior nó

    printf("\nParagem Adicionada com sucesso.\n");

}

/**
 * Mostar os cnoteudos da lista no ecrã
 */
void listarParagems()
{
    struct paragem * temp;
    int n = 1;

    if(head == NULL)
    {
        printf("A lista esta vazia.\n");
    }
    else
    {
        temp = head;
        printf("Paragems:\n");

        while(temp != NULL)
        {
            printf("\nParagem número: %d, Localização: %s, tempo: %d ", n, temp->name, temp->data);

            n++;

            /* Mover o ponteiro para o proximo nó */
            temp = temp->next;
        }
    }
}

// Esta função ira reverter a lista duplamente ligada
void reverterLista()
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

}