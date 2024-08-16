#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include<string.h>

void menu();

typedef struct {
    char nome[50];
    char genero[2];
    char bairro[150];
    char nascimento[10];
}Pessoa;

void cadastro(Pessoa *pessoa) {
    int retorno;
    printf("=============================================\n");
    printf("--------------- Odonto Risos ----------------\n");
    printf("=============================================\n");
    printf("Cadastro de novo cliente. \n");

    getchar();
    printf("\nDigite seu nome: ");
    fgets(pessoa->nome, sizeof(pessoa->nome), stdin);

    
    printf("\nDigite sua data de nascimento: ");
    scanf("%s", pessoa->nascimento);

    getchar();
    printf("\nDigite sua Rua e numero: ");
    fgets(pessoa->bairro, sizeof(pessoa->bairro), stdin);


    printf("\nDigite seu genero. [M] Masculino - [F] Feminino: ");
    scanf(" %c", pessoa->genero);

    printf("\n\nAperte qualquer tecla para retornar ao MENU.");
    getchar();
    getchar();
    menu();
}

void menu(){
    system("cls");
    Pessoa pessoa;
    int escolha;
    printf("=============================================\n");
    printf("--------------- Odonto Risos ----------------\n");
    printf("=============================================\n");
    printf("\nSelecione a opcao desejada: \n");
    printf("\n[1]: Cadastrar novo cliente.\n");
    printf("[2]: Selecionar cliente.\n");
    printf("[3]: Fatura mensal.\n");
    printf("[4]: Servicos disponiveis.\n");
    printf("[5]: Funcionarios.\n");
    scanf("%d", & escolha);

    switch (escolha)
    {
    case 1:
        cadastro(&pessoa);
        break;
    }
}

int main(){
    menu();
    return 0;
}