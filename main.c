#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Uma struct do tipo paragem para formar uma lista duplamente ligada das paragens do autocarro
struct paragem{
    char * nome;//nome
    int tempo;//tempo demorado para chegar nessa paragem
    struct paragem * next;//Ponteiro para proxima paragem
    struct paragem * prev;//Ponteiro para paragem anterior
}*head, *last;

// Uma struct do tipo pessoa para formar uma lista de pessoas á entrar e sair do autocarro
struct pessoa{
    int tempoEntrada;
    int tempoSaida;//tempo demorado para chegar nessa paragem
    struct pessoa *next;//Ponteiro para paragem anterior
};

// Uma struct do tipo pessoa para formar uma lista de pessoas á entrar e sair do autocarro
struct relatorio{
    char *nomeConduct;//
    int totalPessoas;// número total de pessoas transportadas
    int tempoTotal;// duração total da viagem (ida e volta)
    struct relatorio *topo;//Ponteiro apontando para null no topo da pilha
};



// Funcao do tipo paragem, que permite a entrada de novas paragens de acordo como a locacao de memoria 
struct paragem *entra_paragem(char *nome, int tempoChegada, int n){
    struct paragem *loc;//ponteiro que referencia paragem 
    loc = (struct paragem*)malloc(sizeof(struct paragem));// aloca espaço na memoria
    head = (struct paragem*)malloc(sizeof(struct paragem));// aloca espaço na memoria
    if(loc == NULL){// verificar se o espaço foi alocado ou nao 
        printf("Erro de alocação.\nFim de execução\n");
        exit(1);
    };
    if (n==0){
        head->nome = nome;
        head->tempo = tempoChegada;
        head->next = NULL;
        head->prev = NULL;

        last = head;
    }
    else{
        loc->nome = nome;
        loc->tempo = tempoChegada;
        loc->prev = last;
        loc->next = NULL;
        

        last->next = loc;
        last = loc;
    }
    
}

// Funcao do tipo pessoa, que permite a entrada de pessoas para a lista, defenindo o seu tempo de
// entrada e saida de pessoas, equivalente á 3s 
struct pessoa *entra_pessoas(){
    struct pessoa *loc;//ponteiro que referencia pessoa 
    loc = (struct pessoa*)malloc(sizeof(struct pessoa));// aloca espaço na memoria
    if(loc == NULL){// verificar se o espaço foi alocado ou nao 
        printf("Erro de alocação.\nFim de execução\n");
        exit(1);
    };
    loc->tempoEntrada = 3;
    loc->tempoSaida = 3;
    loc->next = NULL;
}

// Funcao do tipo paragem, que permite a entrada de novas paragens de acordo como a locacao de memoria 
struct relatorio *eleboracao_doc(char *nomeConduct, int totalPessoas, int tempoTotal){
    struct relatorio *loc;//ponteiro que referencia paragem 
    loc = (struct relatorio*)malloc(sizeof(struct relatorio));// aloca espaço na memoria
    if(loc == NULL){// verificar se o espaço foi alocado ou nao 
        printf("Erro de alocação.\nFim de execução\n");
        exit(1);
    };
    loc->nomeConduct = nomeConduct;
    loc->totalPessoas= totalPessoas;
    loc->topo = NULL;

}

// Menu de apresentação
int introPainelMenu(){
    int esc;
    system("cls");
    system("clear");
    printf("\n                    Gestão de trafico de autocarros");
    printf("\n\t");
    printf("\n  Escolha uma das funcionalidades do sistema que pretende realizar: ");
    printf("\n\n\t< 1 > Iniciar dia de serviço");
    printf("\n\t< 2 > Terminar dia de serviço");
    printf("\n\t< 3 > Ver progressos do dia em tempo real");
    printf("\n\t< 4 > Validar Relatórios");
    printf("\n\t< 5 > Terminar programa");
    printf("\n\n  Digite a sua escolha: ");
    scanf("%d",&esc);

    return esc;
}

// Esta função é para permitir que o programa aguarde o tempo que o utilizador quiser
// para poder este visualizar o resultado da funcionalidade selecionada e so depois prossegir
void pauseMenuControl(){
    char esc;
    printf("\n\n Digite qualquer coisa para continuar: ");
    scanf("%s", &esc);
}
// gera valores de 10 a 20s relativo ao tempo de deslocamento de uma paragem a outra 
int busRandomTimeGenerator(){
    return  10 + rand()%20;;
}

// Gera valores de 0 á 30 relativamente ao numero de pessoas que entram/saem no autocarro
int personNumberRandomGenerator(int pessoasDentro){
    return  0 + rand()%30, 0 + rand()%pessoasDentro;
}

// Ativa o estado "on" dos serviços caso o mesmo se encontra no estado "off", e virse-versa
bool controloServico(bool state){
    if (state){
        return false;
    }
    return true;
}

void listarParagems(struct paragem * loc, int n_proc ){
    int tempo; char * nome;
    struct paragem *control ;
    control = loc;

    while(control != NULL){
        printf("%d, %s\n", control->tempo, control->nome);
        control = control -> next;
    }
}
void listarParagems1(struct paragem * loc, int n_proc ){
    int tempo; char * nome;
    struct paragem *control ;
    control = loc;

    while(control != NULL){
        printf("%d, %s\n", control->tempo, control->nome);
        control = control -> next;
    }
    // prev<-control;
    // while(control != NULL){
    //     printf("%d, %s\n", control->tempo, control->nome);
    //     control = control <- prev;
    // }
}

void reverseList(struct paragem *loc){

    struct paragem *current, *temp;
    
    // current = loc;

    current = head;
    while(current != NULL)
    {
        /*
         * Swap the previous and next address fields of current node
         */
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;

        /* Move the current pointer to next node which is stored in temp */
        current = temp;
    }
    
    /* 
     * Swap the head and last pointers
     */
    temp = head;
    head = last;
    last = temp;
    // printf("dd");
}

int main(){
    int esc;
    char *paragensAPriori[10];
    int nrParagems = 5;
    char *nameDriver="Artur Fonseca";
    struct paragem *paragem_proc, *auxiliar;
    bool state=false;//variavel de controlo do estado ativo ou nao do serviço
    srand(time(NULL));   // Só deve ser chamada uma única vez

    // Atribuindo valores a priori de paragems de autocarro
    paragensAPriori[0]="Cruz"; paragensAPriori[1]="Mederalzinho";paragensAPriori[2]="T Alecrin";
    paragensAPriori[3]="Lajinha";paragensAPriori[4]="Praça Estrela"; paragensAPriori[5]="Praça Regala";

    // colocando as paragems ja pre estabelecidas no lista de paragems
    for (int i=0; i<= nrParagems; i++){
        if (paragensAPriori[i]!= NULL){
            if (i==0){
                paragem_proc = entra_paragem(paragensAPriori[i],busRandomTimeGenerator(), i);
            }
            else if (i==1){
                paragem_proc ->next = entra_paragem(paragensAPriori[i],busRandomTimeGenerator(), i);
                auxiliar = paragem_proc->next;
            }
            else if(i==nrParagems-1){
                auxiliar->next = entra_paragem(paragensAPriori[i],busRandomTimeGenerator(), i);
            }
            else{
                auxiliar-> next= entra_paragem(paragensAPriori[i],busRandomTimeGenerator(), i);
                auxiliar=auxiliar->next;

            }

        }
    }

    do{
        esc = introPainelMenu(); // para pegar a ascolha do utilizador

        //  Utiliza-se uma expressão de condição switch pra controlar e fazer a relação entre a escolha 
        //  do utilizador com a funcionalidade ligada a esta escolha.
        switch(esc) {

            case 1:
                printf("%d", esc);
                state = controloServico(state);
                printf("\n\tO dia de serviço foi começado.\n\n");
                pauseMenuControl();
                break;

            case 2:
                printf("%d", esc);
                state = controloServico(state);
                printf("\n\tO dia de serviço foi terminado.\n\n");
                listarParagems(paragem_proc, 4);
                reverseList(paragem_proc); 
                listarParagems(paragem_proc, 4);

                pauseMenuControl();
                break;

            case 3:
                printf("%d", esc);
                pauseMenuControl();
                break;

            case 4:
                printf("%d", esc);
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