#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char nome[101];
    int idade;
    double saldo;
}pessoa;

void novo_usuario(pessoa **banco,int *usuarios, int *gerador_id){
    char nome [101]; int idade; double saldo;
    getchar();
    printf("Nome: ");
    fgets(nome, 101, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Idade: ");
    scanf("%d", &idade);
    while(idade<18){
        printf("Idade inválida! Tente Novamente\n");
        printf("Idade: ");
        scanf("%d", &idade);
    }
    printf("Saldo: ");
    scanf("%lf", &saldo);
    while(saldo<0){
        printf("Saldo inválido! Tente Novamente\n");
        printf("Saldo: ");
        scanf("%lf", &saldo);
    }
    *banco=realloc(*banco, ((*usuarios)+1)*sizeof(pessoa));
    if (*banco == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        exit(1);}
    (*banco)[*usuarios].id = *gerador_id;
    strcpy((*banco)[*usuarios].nome, nome);
    (*banco)[*usuarios].idade = idade;
    (*banco)[*usuarios].saldo = saldo;
    printf("======================================\nUsuário inserido com o ID %d\n======================================\n\n", *gerador_id);
    (*usuarios)++;
    (*gerador_id)++;
}

void multiplos_usuario(pessoa **banco,int *usuarios, int *gerador_id){
    int qntd_usuario;
    printf("Quantos usuarios deseja cadastrar? ");
    scanf("%d", &qntd_usuario);
    for(int i=0; i<qntd_usuario;i++){
        novo_usuario(banco, usuarios, gerador_id);
    }
}

void busca_id(pessoa *banco, int usuario){
    int id_procurado;
    printf("Digite o ID para busca: ");
    scanf("%d", &id_procurado);
    for(int i=0;i<usuario;i++){
        if(id_procurado==banco[i].id){
            printf("\n======================================\n");
            printf("Nome: %s\nIdade: %d\nSaldo: %.2fR$",banco[i].nome, banco[i].idade, banco[i].saldo);
            printf("\n======================================\n\n");
            return ;
        }   
    }
    printf("\n======================================\nErro: Usúario %d não encontrado!\n======================================\n\n",id_procurado);

}

int validacao_id(pessoa *banco, int usuarios,int id_procurado){
    for(int i=0;i<usuarios;i++){
        if(id_procurado==banco[i].id){
            return i;
        }   
    }
    return -1;
}

void transferencia(pessoa *banco, int usuarios){
    if (usuarios<2){
        printf("Erro, menos de 2 usúarios! Impossivel realizar uma transferência\n");
        return;
    }
    int id;
    printf("Remetente [ID]: "); 
    scanf("%d", &id);
    int indice_remetente = validacao_id(banco, usuarios, id);
    
    while(indice_remetente == -1){
        printf("Usuario Invalido! Tente Novamente\n");
        printf("Remetente [ID]: "); 
        scanf("%d", &id);
        indice_remetente = validacao_id(banco, usuarios, id);
    }
    
    printf("Destinatario [ID]: "); 
    scanf("%d", &id);
    int indice_destinatario = validacao_id(banco, usuarios, id);
    
    while(indice_destinatario == -1 || indice_destinatario==indice_remetente){
        printf("Usuario Invalido! Tente Novamente\n");
        printf("Destinatario [ID]: "); 
        scanf("%d", &id);
        indice_destinatario = validacao_id(banco, usuarios, id);
        }
    double valor;
    printf("Valor da Transferência: R$");
    scanf("%lf", &valor);
    if(valor<0.01){
        printf("\n======================================\nTRANSFERÊNCIA NEGADA! VALOR INVÁLIDO\n======================================\n\n");
    }
    else if(valor>banco[indice_remetente].saldo){
        printf("\n=========================================\nTRANSFERÊNCIA NEGADA! SALDO INSUFICIENTE\n=========================================\n\n");
    }
    else{
        banco[indice_remetente].saldo-=valor;
        banco[indice_destinatario].saldo+=valor;
        printf("\n======================================\nTransferência feita com Sucesso!\n======================================\n\n");
    }

}
void remocao_usuario(pessoa **banco, int *usuarios){
    int id_remover;
    int indice;
    if (*usuarios == 0) {
        printf("Erro: O banco de dados esta vazio!\n");
        return;
    }
    printf("Digite o ID do usuario a ser removido: ");
    scanf("%d", &id_remover);
    indice = validacao_id(*banco, *usuarios, id_remover);
    if (indice == -1) {
        printf("\n======================================\nErro: Usuario %d nao encontrado!\n======================================\n\n", id_remover);
        return;}
    for (int i = indice; i < (*usuarios) - 1; i++) {
        (*banco)[i] = (*banco)[i + 1];
    }
    (*usuarios)--;
    if (*usuarios == 0) {
        free(*banco);
        *banco = NULL;
    } else {
        *banco = realloc(*banco, (*usuarios) * sizeof(pessoa));
        if (*banco == NULL) {
            printf("Erro Critico: Falha ao realocar memoria.\n");
            exit(1);
        }
    }
    printf("\n======================================\nUsúario %d removido com sucesso!\n======================================\n\n", id_remover);
}

void salvar_encerrar(pessoa *banco, int usuarios){
    FILE *arq=fopen("Usuarios.txt", "w");
    if(arq==NULL){
        printf("Erro ao abrir arquivo!");
        return;
    }
    for(int i = 0; i < usuarios; i++){
        fprintf(arq, "%d,%s,%d,%.2f\n", banco[i].id, banco[i].nome, banco[i].idade, banco[i].saldo);
    }
    
    fclose(arq);
    printf("Dados salvos com sucesso no arquivo Usuarios.txt!\n");
}

int main(){
    pessoa *banco_dados=NULL;
    int gerador_id=1;
    int escolha;
    int total_usuarios=0;
    do{
        printf("UAIBANK Menu\n");
        printf(" [1]-Adicionar Novo Usuário\n [2]-Adicionar Múltiplos Usuários\n [3]-Buscar por ID\n [4]-Realizar Transferência\n [5]-Remover Usúario\n [0]-Encerrar e Salvar\nEscolha: ");
        scanf("%d", &escolha);
        switch (escolha){
            case 1: novo_usuario(&banco_dados, &total_usuarios, &gerador_id); break;
            case 2: multiplos_usuario(&banco_dados, &total_usuarios, &gerador_id);break;
            case 3: busca_id(banco_dados, total_usuarios); break;
            case 4: transferencia(banco_dados, total_usuarios); break;
            case 5: remocao_usuario(&banco_dados, &total_usuarios); break;
            case 0: salvar_encerrar(banco_dados, total_usuarios); break;
            default: printf("Opção Inválida! Tente Novamente\n");
        }
    }while(escolha!=0);
    if(banco_dados != NULL){
        free(banco_dados);
    }
    return 0;
}