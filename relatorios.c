#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>     // para INT_MIN

#define SIZE 50


typedef struct relatorio{
    int totalTranspor;
    int duracao;
    char * nomeCondutor[30];
} relatorio;


// criar uma pilha com capacidade para 100 elementos
relatorio stack[SIZE];
unsigned visto=false;

// inicializando a pilha vazia
int top = -1;


/* funções a serem utilizadas pera os relatórios */
void colocarElemento(int pessoasTrans, char * nomeCondu, int duracao);
int  verificarFimDia();


int main()
{
    int choice, data, i;


    while(1)
    {
        /* Menu */
        printf("------------------------------------\n");
        printf("    STACK IMPLEMENTATION PROGRAM    \n");
        printf("------------------------------------\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch(choice) 
        {
            case 1: 
                printf("Enter data to push into stack: ");
                scanf("%d", &data);
                
                // colocar elementos na pilha
                colocarElemento(data, "José ne", 20);
                break;

            case 2: 
                for(i=0;i<=SIZE+top;i++){
                    data = verificarFimDia();
                }
                break;

            default: 
                printf("Invalid choice, please try again.\n");
        }

        printf("\n\n");
    }


    return 0;
}



/**
 * colocar elemento no topo da pilha
 */
void colocarElemento(int pessoasTrans, char * nomeCondu, int duracao)
{
    // Verificar se a pilha ja esta cheia
    if (top >= SIZE)
    {
        printf("\nALERTA: Pilha de relatórios se encontra cheia.\n");
        return;
    }

    // Increase element count in stack
    top++;

    // Push element in stack
    stack[top].totalTranspor = pessoasTrans;
    strcpy(stack[top].nomeCondutor, nomeCondu);
    stack[top].duracao = duracao;

    // printf("dados colocados na pilha\n");
}


/**
 * Ver os relatórios e esvaziar a pilha.
 */
int verificarFimDia()
{
    int i=0, menorTempo=0, maisTranspor=0;
    char conduMenorTempo[30], conduMaisTranspor[30];

    // verificar se a pilha se encontra vazia.
    if (top < 0)
    {
        return INT_MIN;
    }


    if (!visto){
        printf("\n\tTodos os condutores:\n\n");
        for(;i<=top;i++){
            if (stack[i].duracao>menorTempo){
                stpcpy(conduMenorTempo, stack[i].nomeCondutor);
                menorTempo=stack[i].duracao;
            }
            if (stack[i].totalTranspor>maisTranspor){
                stpcpy(conduMaisTranspor, stack[i].nomeCondutor);
                maisTranspor=stack[i].totalTranspor;
            }
            printf("Condutor: %s, tempo: %d, pessoasTrans: %d\n", stack[i].nomeCondutor, stack[i].duracao, stack[i].totalTranspor);
        }
        printf("\n\tDestaques do dia: \n");
        printf("\nCondutor que fez menos tempo: %s, tempo de: %d: ", conduMenorTempo, menorTempo);
        printf("\nCondutor que Transportou mais pessoas: %s, numero pessoas: %d: ", conduMaisTranspor, maisTranspor);
        printf("\nNumero voltas feitas pelo autocarro: %i", i);
        visto = true;
    }
    
    
    // returnar o valor de topo da pilha decrementa o top eliminando o elemento de top
    return stack[top--].totalTranspor;
}