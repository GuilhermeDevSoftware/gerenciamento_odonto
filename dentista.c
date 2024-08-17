#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CLIENTES 100

void menu();
void cadastro_Cliente();

typedef struct Servico {
    char nome[50];
    float valor;
    char data[10];
    struct Servico *esquerda;
    struct Servico *direita;
} Servico;

typedef struct {
    char nome[50];
    char genero[2];
    char bairro[150];
    char nascimento[10];
    int id;
}Pessoa;

typedef struct {
    Pessoa dado_cliente;
    Servico *historico_servicos;
} Cliente;

int contador_cadastro = 0;
Pessoa clientes[MAX_CLIENTES];

void cadastro_Cliente(Pessoa *pessoa) {
    int retorno;
    printf("=============================================\n");
    printf("--------------- Odonto Risos ----------------\n");
    printf("=============================================\n");
    printf("Cadastro de novo cliente. \n");

    getchar();
    printf("\nDigite seu nome: ");
    fgets(pessoa->nome, sizeof(pessoa->nome), stdin);
    pessoa->nome[strcspn(pessoa->nome, "\n")] = 0;

    printf("\nDigite sua data de nascimento: ");
    scanf("%s", pessoa->nascimento);

    getchar();
    printf("\nDigite sua Rua e numero: ");
    fgets(pessoa->bairro, sizeof(pessoa->bairro), stdin);
    pessoa->bairro[strcspn(pessoa->bairro, "\n")] = 0;

    printf("\nDigite seu genero. [M] Masculino - [F] Feminino: ");
    scanf(" %c", pessoa->genero);

    pessoa->id = contador_cadastro +1;

    if (contador_cadastro < MAX_CLIENTES) {
        clientes[contador_cadastro].dado_cliente = *pessoa;
        clientes[contador_cadastro].historico_servicos = NULL;
        contador_cadastro++;
    } else {
        printf("Limite de clientes atingido!\n");
    }

    printf("\n\nAperte qualquer tecla para retornar ao MENU.");
    getchar();
    getchar();
    menu();
}

void exibirClientes() {
    system("cls");
    printf("\nClientes cadastrados:\n");
    for (int i = 0; i < contador_cadastro; i++) {
        printf("\nCliente %d:", i + 1);
        printf("\nNome: %s", clientes[i].nome);
        printf("\nGenero: %s", clientes[i].genero);
        printf("\nBairro: %s", clientes[i].bairro);
        printf("\nData de nascimento: %s", clientes[i].nascimento);
        printf("\n");
    }
    printf("\n\nAperte qualquer tecla para retornar ao MENU.");
    getchar();
    getchar();
    menu();
}

void servicos(){
    system("cls");
    printf("\n[1] - Limpeza dentaria = R$195,00");
    printf("\n[2] - Cirurgia de remocao dentaria = R$700.00");
    printf("\n[3] - Obturacao = R$515,00");
    printf("\n[4] - Canal = R$400,00");

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
    printf("[3]: Servicos disponiveis.\n");    
    printf("[4]: Clientes cadastrados: \n");
    printf("[5]: Sair");
    printf("\n\nInsira sua opcao: ");
    scanf("%d", & escolha);

    switch (escolha)
    {
    case 1:
        cadastro_Cliente(&pessoa);
        break;
    case 2:
        selecionar_cliente();
        break; 
    case 3:
        servicos();
        menu();
        break;
    case 4:
        exibirClientes();
        menu();
        break;
    case 5:
        system("cls");
        printf("\n\nFECHANDO SISTEMA.");
        break;
    }
    
}

int main(){
    menu();
    return 0;
}