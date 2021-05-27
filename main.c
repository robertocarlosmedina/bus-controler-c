#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>     // para INT_MIN

#define SIZE 50
#define CAPACIDADE 31    // máxima capacidade do autocarro

//  Declaração de variaveis a sem utilizados
int condutorServico = 0;

/* ____________ Variaveis e metedos a serem utilizados na pilha de relatorios ____________*/

// Estrutura de dados para ser utilizado na pilha de relatorios
typedef struct relatorio{
    int totalTranspor;
    int duracao;
    char * nomeCondutor[30];
} relatorio;

// criar uma pilha com capacidade para 50 relatorios
relatorio stack[SIZE];
bool visto=false;
// inicializando a pilha vazia
int top = -1;
/* assinatura das funções a serem utilizadas para os relatórios */
void colocarElemento(int pessoasTrans, char * nomeCondu, int duracao);
int  verificarFimDia();

// _______________________________________________________________________________________
/* ____________ Variaveis e metedos a serem utilizados nas filas de pessoas ____________*/

/* defenição estrutura pessoa */
typedef struct pessoa
{
    int id;
    struct pessoa * next;
} Fila;    // Fila é uma typedef da struct pessoa

/* para controlar quantas pessoas estão no autocarro */
unsigned int nrPessoasAutocarro = 0;
// assinatura das funções a serem utilizados para as filas de pessoas
void entradaFila(Fila ** ultimo, Fila ** primeiro, int id);
void saidaFila(Fila ** primeiro);
int estaVazia();
int estaCheia();

// _______________________________________________________________________________________
/* ____________ Variaveis e metedos a serem utilizados nas listas duplamente ligadas de paragems ____________*/

/*
 * definiçºao de uma estrutura tipo paragem
 */
struct paragem {
    int data;
    char name[1][200];
    struct paragem * prev;
    struct paragem * next;
}*head, *last;

char paragensAPriori[20][30];
int nrparagems=5;

/*
 * assinatura das funções a serem utilizadas para a listas de paragems
 */
void criarListaParagems();
void listarParagems();
void reverterLista();
void adicionarParagem();
int gerarTempoRandom();

// _______________________________________________________________________________________
/* ____________ Variaveis e metedos a serem utilizados no controlo do programa ____________*/

char condutores[4][30];

// assinatura de todos os metedos auxiliares do programa
int introPainelMenu();
void pauseMenuControl();
void fazerDiaServico();
void inicializandoDados();

int main(){
    int esc=0,i;

    head = NULL;
    last = NULL;

    inicializandoDados();
    srand(time(NULL));

    do{
        esc = introPainelMenu(); // para pegar a ascolha do utilizador

        //  Utiliza-se uma expressão de condição switch pra controlar e fazer a relação entre a escolha 
        //  do utilizador com a funcionalidade ligada a esta escolha.
        switch(esc) {

            case 1:
                printf("\nServiço inicializado.\n");
                fazerDiaServico();
                pauseMenuControl();
                break;

            case 2:
                adicionarParagem();
                pauseMenuControl();
                break;

            case 3:
                listarParagems();
                pauseMenuControl();
                break;

            case 4:
                for(i=0;i<=SIZE+top;i++){
                    int data = verificarFimDia();
                }
                pauseMenuControl();
                break;

            default :
                printf("\nErro de escolha: Não existe essa opção no sistema.\n Digite uma opção valida.");
        }
    }while(esc != 5);// se for introduzido 5 o programa para a execução

    system("cls");
    printf("\nPrograma encerrado.\n\n");

    return 0;
}
//  inicilizando a lista e o nume de alguns condutores alguns dados
void inicializandoDados(){
    stpcpy(condutores[0], "Antonio Varela");
    stpcpy(condutores[1], "Rilton Silva");
    stpcpy(condutores[2], "Joana Pires");
    stpcpy(condutores[3], "Pedro Lopes");
    stpcpy(condutores[4], "Armindo Lopes");

    stpcpy(paragensAPriori[0], "Cruz");
    stpcpy(paragensAPriori[1], "Lajinha");
    stpcpy(paragensAPriori[2], "Mederalzinho");
    stpcpy(paragensAPriori[3], "Praca");
    stpcpy(paragensAPriori[4], "Estrela");
    stpcpy(paragensAPriori[5], "Estrela");
    criarListaParagems();
}
// Menu de apresentação
int introPainelMenu(){
    int esc;
    system("cls");
    system("clear");
    printf("\n                    Gestão de trafico de autocarros");
    printf("\n\t");
    printf("\n  Escolha uma das funcionalidades do sistema que pretende realizar: ");
    printf("\n\n\t\t< 1 > Iniciar dia de serviço");
    printf("\n\t\t< 2 > Incerir nova paragem");
    printf("\n\t\t< 3 > Listar paragems registradas");
    printf("\n\t\t< 4 > Validar Relatórios");
    printf("\n\t\t< 5 > Terminar programa");
    printf("\n\n--------------------------------------------------------------------");
    printf("\n\n  Digite a sua escolha: ");
    scanf("%d",&esc);

    return esc;
}
void fazerDiaServico(){
    struct paragem * temp;
    int n = 1, volta=0, i, f;
    int pessoasTransportadas=0;

    int ch, id,nrPessoasEntrada, nrPessoasSaida;
    Fila *ultimo, *primeiro;

    ultimo  = NULL;
    primeiro = NULL;


    for(i=0; i<=4;i++){
        for(volta = 0;volta<2;volta++){
            temp = head;
            while(temp != NULL){
                // printf("\nParagem número: %d, Localização: %s, tempo: %d ", n, temp->name, temp->data);
                if (!estaCheia()){
                    nrPessoasEntrada = 0 + rand()%(CAPACIDADE-nrPessoasAutocarro);                
                    for(f=0; f<nrPessoasEntrada; f++){
                        entradaFila(&ultimo, &primeiro, nrPessoasAutocarro+1);
                        // printf("added\n");
                    }
                    pessoasTransportadas=pessoasTransportadas+nrPessoasEntrada;
                }
                if(!estaVazia()){
                    nrPessoasSaida = 0 + rand()%(nrPessoasAutocarro);  
                    for(f=0; f<nrPessoasSaida; f++){
                        saidaFila(&primeiro);
                        // printf("removed\n");
                    }
                }
                // n++;
                /* Mover o ponteiro para o proximo nó */
                temp = temp->next;
            }
        }
        colocarElemento(pessoasTransportadas, condutores[i],pessoasTransportadas*6);
        pessoasTransportadas = 0;
    }
}

// Esta função é para permitir que o programa aguarde o tempo que o utilizador quiser
// para poder este visualizar o resultado da funcionalidade selecionada e so depois prossegir
void pauseMenuControl(){
    char esc;
    printf("\n\n Digite qualquer coisa para continuar: ");
    scanf("%s", &esc);
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
    int i=0, menorTempo=stack[0].duracao, maisTranspor=0;
    char conduMenorTempo[30], conduMaisTranspor[30];

    // verificar se a pilha se encontra vazia.
    if (top < 0)
    {
        return INT_MIN;
    }
    if (!visto){
        printf("\n\tTodos os condutores:\n\n");
        for(;i<=top;i++){
            if (stack[i].duracao<menorTempo){
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

/**
 * cria uma lista duplamente ligada com paragems ja previamente defenidades
 */
void criarListaParagems()
{
    int i;
    struct paragem *newNode;
    

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
    
    for(i=1; i<=nrparagems; i++)
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
    nrparagems++;
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