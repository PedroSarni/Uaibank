#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcões.h"

int main(){
    srand(time(NULL));

    pessoa *banco_dados=NULL;
    int gerador_id=1;
    int escolha;
    int total_usuarios=0;

    //arquivo de registro de transferencia
    FILE *arq_trans = fopen("/home/sarni/Área de trabalho/1º Semestre/UaiBank/Projeto/data/Transferências.csv", "r+");
    fprintf(arq_trans,"ID_remetente,ID_destinatario,Valor,DataHora\n");
    if (arq_trans == NULL) {
    printf("Erro ao abrir arquivo de transferencias!\n");
    return 1;
    }

    do{
        printf("UAIBANK Menu\n");
        printf(" [1]-Adicionar Novo Usuário\n [2]-Adicionar Múltiplos Usuários\n [3]-Buscar por ID\n [4]-Realizar Transferência\n [5]-Remover Usúario\n [0]-Encerrar e Salvar\nEscolha: ");
        scanf("%d", &escolha);
        switch (escolha){
            case 1: limpa_buffer(); novo_usuario(&banco_dados, &total_usuarios, &gerador_id); break;
            case 2: multiplos_usuario(&banco_dados, &total_usuarios, &gerador_id);break;
            case 3: busca_id(banco_dados, total_usuarios); break;
            case 4: transferencia(banco_dados, total_usuarios,arq_trans); break;
            case 5: remocao_usuario(&banco_dados, &total_usuarios); break;
            case 0: salvar_encerrar(banco_dados, total_usuarios); break;
            default: printf("Opção Inválida! Tente Novamente\n");
        }
    }while(escolha!=0);
    if(banco_dados != NULL){
        free(banco_dados);
    }
    fclose(arq_trans);
    return 0;
}
