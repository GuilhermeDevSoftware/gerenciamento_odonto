#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CLIENTES 100

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
    Pessoa dados_cliente;
    Servico *historico_servicos;
} Cliente;

int contador_cadastro = 0;
Cliente clientes[MAX_CLIENTES];

void exibirHistorico(Servico *raiz);
void gerarNotaFiscal(Servico *raiz, Pessoa cliente);
void menu();
void cadastro_Cliente();
void servicos(int cliente_id);
void selecionarCliente();
void exibirClientes();
void adicionarServicoParaCliente();

Servico* adicionarServico(Servico *raiz, char nome[], float valor, char data[]) {
    if (raiz == NULL) {
        Servico *novo = (Servico*)malloc(sizeof(Servico));
        strcpy(novo->nome, nome);
        novo->valor = valor;
        strcpy(novo->data, data);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = adicionarServico(raiz->esquerda, nome, valor, data);
    } else {
        raiz->direita = adicionarServico(raiz->direita, nome, valor, data);
    }
    return raiz;
}

void exibirHistorico(Servico *raiz) {
    if (raiz != NULL) {
        exibirHistorico(raiz->esquerda);
        printf("\nServico: %s\nValor: R$%.2f\nData: %s\n", raiz->nome, raiz->valor, raiz->data);
        exibirHistorico(raiz->direita);
    }
}

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
        clientes[contador_cadastro].dados_cliente = *pessoa;
        clientes[contador_cadastro].historico_servicos = NULL;
        contador_cadastro++;
    } else {
        printf("Limite de clientes atingido!\n");
    }

    printf("\nCadastro realizado com sucesso! Seu ID é %d\n", pessoa->id);
    printf("\n\nAperte qualquer tecla para retornar ao MENU.");
    getchar();
    getchar();
    menu();
}

void selecionarCliente() {
    int id;
    exibirClientes(); 
    printf("\nSelecione o ID do cliente: ");
    scanf("%d", &id);
    id--;  

    if (id >= 0 && id < contador_cadastro) {
        printf("\nHistorico de servicos de %s (ID: %d):\n", clientes[id].dados_cliente.nome, clientes[id].dados_cliente.id);
        exibirHistorico(clientes[id].historico_servicos);
        printf("\n\nDeseja adicionar um novo servico para este cliente? (1 para Sim, 0 para Nao): ");
        int adicionar;
        scanf("%d", &adicionar);
        if (adicionar == 1) {
            servicos(id);
        }
    } else {
        printf("\nID invalido!\n");
    }

    printf("\n\nAperte qualquer tecla para retornar ao MENU.");
    getchar();
    getchar();
    menu();
}

void exibirClientes() {
    printf("\nClientes cadastrados:\n");
    for (int i = 0; i < contador_cadastro; i++) {
        printf("\nCliente ID %d:", clientes[i].dados_cliente.id);
        printf("\nNome: %s", clientes[i].dados_cliente.nome);
        printf("\nGenero: %s", clientes[i].dados_cliente.genero);
        printf("\nBairro: %s", clientes[i].dados_cliente.bairro);
        printf("\nData de nascimento: %s", clientes[i].dados_cliente.nascimento);
        printf("\n");
    }
}

void servicos(int cliente_id){
    int opcao;
    char data[10];
    printf("\nSelecione o servico: \n");
    printf("\n[1] - Limpeza dentaria = R$195,00");
    printf("\n[2] - Cirurgia de remocao dentaria = R$700,00");
    printf("\n[3] - Obturacao = R$515,00");
    printf("\n[4] - Canal = R$400,00");

    printf("\n\nEscolha uma opcao: ");
    scanf("%d", &opcao);

    printf("\nDigite a data de realizacao (dd/mm/aaaa): ");
    scanf("%s", data);

    switch(opcao) {
        case 1:
            clientes[cliente_id].historico_servicos = adicionarServico(clientes[cliente_id].historico_servicos, "Limpeza dentaria", 195.00, data);
            break;
        case 2:
            clientes[cliente_id].historico_servicos = adicionarServico(clientes[cliente_id].historico_servicos, "Cirurgia de remocao dentaria", 700.00, data);
            break;
        case 3:
            clientes[cliente_id].historico_servicos = adicionarServico(clientes[cliente_id].historico_servicos, "Obturacao", 515.00, data);
            break;
        case 4:
            clientes[cliente_id].historico_servicos = adicionarServico(clientes[cliente_id].historico_servicos, "Canal", 400.00, data);
            break;
        default:
            printf("Opcao invalida!\n");
            break;
    }

    printf("\n\nServico adicionado ao historico!\n\nDeseja gerar a nota fiscal? (1 para Sim, 0 para Nao): ");
    int gerarNota;
    scanf("%d", &gerarNota);

    if (gerarNota == 1) {
        gerarNotaFiscal(clientes[cliente_id].historico_servicos, clientes[cliente_id].dados_cliente);
    }

    printf("\n\nAperte qualquer tecla para retornar ao MENU.");
    getchar();
    getchar();
    menu();
}

void adicionarServicoParaCliente() {
    int id;
    printf("\nDigite o ID do cliente para adicionar um servico: ");
    scanf("%d", &id);
    id--; 

    if (id >= 0 && id < contador_cadastro) {
        servicos(id);
    } else {
        printf("\nID invalido!\n");
    }

    printf("\n\nAperte qualquer tecla para retornar ao MENU.");
    getchar();
    getchar();
    menu();
}

void gerarNotaFiscal(Servico *raiz, Pessoa cliente) {
    float total = 0.0;
    printf("\n=============================================\n");
    printf("                 NOTA FISCAL                 \n");
    printf("=============================================\n");
    printf("Cliente: %s\n", cliente.nome);
    printf("ID do Cliente: %d\n", cliente.id);
    printf("Servicos Realizados:\n");

    Servico *temp = raiz;
    while (temp != NULL) {
        printf(" - %s: R$%.2f em %s\n", temp->nome, temp->valor, temp->data);
        total += temp->valor;

        if (temp->esquerda != NULL) {
            temp = temp->esquerda;
        } else {
            temp = temp->direita;
        }
    }

    printf("\n---------------------------------------------\n");
    printf("Total a pagar: R$%.2f\n", total);
    printf("=============================================\n\n");
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
        selecionarCliente();
        break; 
    case 3:
        adicionarServicoParaCliente();
        break;
    case 4:
        exibirClientes();
        printf("\n\nAperte qualquer tecla para retornar ao MENU.");
        getchar();
        getchar();
        menu();
        break;
    case 5:
        system("cls");
        printf("\n\nFECHANDO SISTEMA.");
        break;
    default:
        printf("\nOpcao invalida!\n");
        menu();
        break;        
    }
    
}

int main(){
    menu();
    return 0;
}