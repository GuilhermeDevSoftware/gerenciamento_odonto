#include<stdio.h>
#include<stdlib.h>

void menu(){
    int escolha;
    printf("=============================================\n");
    printf("--------------- Odonto Risos ----------------\n");
    printf("=============================================\n");
    printf("\nSelecione a opcao desejada: \n");
    printf("\n[1]: Cadastrar novo cliente.\n");
    printf("[2] Selecionar cliente.\n");
    printf("[3] Fatura mensal.\n");
    printf("[4] Servicos disponiveis.\n");
    printf("[5] Funcionarios.\n");

    switch (escolha)
    {
    case 1:
        cadastro();
        break;
    case 2:
        selecionar();
        break;
    case 3:
        fatura();
        break;    
    default:
        break;
    }
}




int main(){
    menu();



    return 0;
}