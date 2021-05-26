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


void entradaFila(Fila ** ultimo, Fila ** primeiro, int id);
void saidaFila(Fila ** primeiro);
int estaVazia();
int estaCheia();


int main()
{
    int ch, id,nrPessoasEntrada, nrPessoasSaida, i;
    Fila *ultimo, *primeiro;

    ultimo  = NULL;
    primeiro = NULL;
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
        printf("0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Select an option: ");

        scanf("%d", &ch);

        
        /* Menu control switch */
        switch (ch)
        {
            case 1:
                if (!estaCheia()){
                    nrPessoasEntrada = 0 + rand()%(CAPACIDADE-nrPessoasAutocarro);                
                    for(i=0; i<nrPessoasEntrada; i++){
                        entradaFila(&ultimo, &primeiro, nrPessoasAutocarro+1);
                        // printf("added\n");
                    }
                }
                break;

            case 2:
                if(!estaVazia()){
                    nrPessoasSaida = 0 + rand()%(nrPessoasAutocarro);  
                    for(i=0; i<nrPessoasSaida; i++){
                        saidaFila(&primeiro);
                        // printf("removed\n");
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
 * ensere um elemento no fim da fila
 */
void entradaFila(Fila ** ultimo, Fila ** inicio, int id)
{
    Fila * newNode = NULL;

    // Criar um novo nó para a fila
    newNode = (Fila *) malloc (sizeof(Fila));

    // assina um valor para o nó
    newNode->id = id;

    // Inicialmento o novo nó não aponta para nada
    newNode->next = NULL;

    // ligar novo nó com o ultimo no existente
    if ( (*ultimo) )
    {
        (*ultimo)->next = newNode;
    }
    

    // Certificando que o ultimo nó criado é o ultimo
    *ultimo = newNode;

    // ligar o primeiro no com o inicio se for nulo
    if ( !( *inicio) )
    {
        *inicio = *ultimo;
    }

    // incrementar o numero de pessoas no autocarro
    nrPessoasAutocarro++;
}


/**
 * remove um elemento no inicio da fila
 */
void saidaFila(Fila ** primeiro)
{
    Fila *toDequque = NULL;
    int id = INT_MIN;

    // pegar o elemento e o valor id para eliminar
    toDequque = *primeiro;
    id = toDequque->id;

    // mover o primeiro para fora
    *primeiro = (*primeiro)->next;

    // decrementar o nr pessoas no autocarro
    nrPessoasAutocarro--;

    // limpar o elemento removido da memoria
    free(toDequque);

}


/**
 * Varificar se o autocarro esta vazio
 */
int estaVazia()
{
    return (nrPessoasAutocarro <= 0);
}


/**
 * Verificar se o autocarro esta cheio
 */
int estaCheia()
{
    return (nrPessoasAutocarro >= CAPACIDADE);
}