#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Menu de apresentação
int introPainelMenu(){
    int esc;
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

void busRandomGenerator(){
    printf("Ok");
}

int main(){
    int esc;
    char *bus[20];
    srand(time(NULL));   // Só deve ser chamada uma única vez
    int r = 1 + rand()%10; // gerando nr aleatorios de 1:10
    printf("%d",r);
    // char bus={"sv-31-ad", "sv-43-dt", "sv-43-tr", "sv-21-ew"};
    // strcpy(bus, "iwfiu");
    // bus[4]->"hihiu";
    do{
        esc = introPainelMenu(); // para pegar a ascolha do utilizador

        //  Utiliza-se uma expressão de condição switch pra controlar e fazer a relação entre a escolha 
        //  do utilizador com a funcionalidade ligada a esta escolha.
        switch(esc) {

            case 1:
                printf("%d", esc);
                pauseMenuControl();
                break;

            case 2:
                printf("%d", esc);
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

    system("clear");
    printf("\nPrograma encerrado.\n\n");

    return 0;
}