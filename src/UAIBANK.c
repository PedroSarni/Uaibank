#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
    int id;
    char nome[101];
    int idade;
    char sexo;
    char email[101];
    char estado[101];
    double saldo;
    char senha[101];
    char telefone[30];
    int erros;
}pessoa;

void limpa_buffer(){
    int ch;
    while (1){
        ch = getchar();
        if (ch == '\n' || ch == EOF){
            break;
        }}
}

int gerar_codigo_2FA(){
    return (rand()%90000)+10000;
}

void enviar_sms_2FA(int codigo, char telefone[]){

}

void enviar_email_2FA(int codigo, char email[]){
    char comando[300];

    snprintf(comando, sizeof(comando),
             "python3 scripts/enviar_email.py \"%d\" \"%s\"",
             codigo, email);

    int resultado = system(comando);

    if (resultado == 0) {
        printf("Código enviado para o e-mail: %s\n", email);
    }
    else {
        printf("Não foi possível enviar o código para %s. Verifique se o endereço está correto.\n", email);
    }
}

void recuperar_senha(char telefone[], char email[],pessoa *banco,int usuario){
    int codigo = gerar_codigo_2FA();
    int metodo;

    printf("\nComo deseja receber o código?\n");
    printf("[1] SMS\n");
    printf("[2] E-mail\n");
    printf("Escolha: ");
    scanf("%d", &metodo);

    if(metodo == 1){
        enviar_sms_2FA(codigo, telefone);
    }
    else if(metodo == 2){
        enviar_email_2FA(codigo, email);
    }
    else{
        printf("Opção inválida!\n");
        return;
    }

    int digitado;
    printf("\nDigite o código recebido: ");
    scanf("%d", &digitado);

    if(digitado == codigo){
        getchar();

        printf("Nova senha: ");
        fgets(banco[usuario].senha, 101, stdin);
        banco[usuario].senha[strcspn(banco[usuario].senha, "\n")] = '\0';

        banco[usuario].erros = 0;

        printf("\n====================================\n");
        printf("Senha alterada com sucesso!\n");
        printf("====================================\n\n");
    }
    else{
        printf("\n====================================\n");
        printf("Código incorreto!\n");
        printf("====================================\n\n");
    }

    return;
}

bool limparTelefone(const char *entrada, char *saida) {
    if (entrada == NULL || saida == NULL || strlen(entrada)<11) {
        if (saida != NULL) saida[0] = '\0';
        printf("Número de telefone inválido! Tente Novamente\n");
        return true;
    }

    char apenasNumeros[30];
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (isdigit((unsigned char)entrada[i])) {
            apenasNumeros[j++] = entrada[i];
        }
    }
    apenasNumeros[j] = '\0';
    char resultado[30];
    int inicio = 0;

    if (strlen(apenasNumeros) > 11 &&
        strncmp(apenasNumeros, "55", 2) == 0) {
        inicio = 2;
    }

    strcpy(resultado, apenasNumeros + inicio);
    strcpy(saida, resultado);
    return false;
}

void novo_usuario(pessoa **banco,int *usuarios, int *gerador_id){
    char nome [101];
    int idade;
    double saldo;
    char sexo;
    char estado [101];
    char senha[101];
    char telefone[30];
    char telefone_corrigido[30];
    char email[101];

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

    printf("Sexo[M/F]: ");
    getchar();
    sexo=getchar();
    sexo=toupper(sexo);
    while (sexo!='M' && sexo!='F')
    {
        printf("Opção Inválida! Tente Novamente\n");
        printf("Sexo[M/F]: ");
        sexo=getchar();
        sexo=toupper(sexo);

    }
    limpa_buffer();

    printf("Email: ");
    fgets(email, 101, stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Estado: ");
    fgets(estado, 101, stdin);
    estado[strcspn(estado, "\n")] = '\0';

    printf("Telefone: ");
    fgets(telefone, 30, stdin);
    telefone[strcspn(telefone, "\n")] = '\0';
    while(limparTelefone(telefone, telefone_corrigido)){
        printf("Telefone: ");
        fgets(telefone, 30, stdin);
        telefone[strcspn(telefone, "\n")] = '\0';
    }

    printf("Saldo: ");
    scanf("%lf", &saldo);
    while(saldo<0){
        printf("Saldo inválido! Tente Novamente\n");
        printf("Saldo: ");
        scanf("%lf", &saldo);
    }

    getchar();
    printf("Senha: ");
    fgets(senha, 101, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    *banco=realloc(*banco, ((*usuarios)+1)*sizeof(pessoa));
    if (*banco == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        exit(1);}
    (*banco)[*usuarios].id = *gerador_id;
    strcpy((*banco)[*usuarios].nome, nome);
    strcpy((*banco)[*usuarios].senha, senha);
    strcpy((*banco)[*usuarios].estado, estado);
    (*banco)[*usuarios].idade = idade;
    (*banco)[*usuarios].saldo = saldo;
    (*banco)[*usuarios].sexo = sexo;
    strcpy((*banco)[*usuarios].telefone, telefone_corrigido);
    strcpy((*banco)[*usuarios].email, email);
    (*banco)[*usuarios].erros=0;


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
            char senha [101];
            getchar();
            printf("Digite sua Senha: ");
            fgets(senha, 101, stdin);
            senha[strcspn(senha, "\n")] = '\0';
            if (strcmp(senha,banco[i].senha)==0){
                printf("\n========================================\n");
                printf("Nome:   %s\nEmail:  %s\nIdade:  %d\nSexo:   %c\nEstado: %s\nSaldo:  %.2fR$",banco[i].nome,banco[i].email, banco[i].idade, banco[i].sexo, banco[i].estado, banco[i].saldo);
                printf("\n========================================\n\n");
                return ;
            }
            else if(strcmp(senha,banco[i].senha)!=0 && banco[i].erros<2){
                printf("\n================================\nSenha Inválida! Tente Novamente\n================================\n\n");
                banco[i].erros++;
                return;
            }
            else{
                char resposta;
                printf("\n================================\nSenha Inválida! Tente Novamente\n================================\n");
                printf("Deseja Alterar a sua Senha? [S/N]: ");
                scanf(" %c",&resposta);
                resposta=toupper(resposta);
                while (resposta!='S' && resposta!='N'){
                    printf("Resposta Inválida! Tente Novamente\n");
                    scanf(" %c",&resposta);
                    resposta=toupper(resposta);
                }
                if(resposta=='S'){
                    recuperar_senha(banco[i].telefone,banco[i].email,banco, i);
                    return;
                }
                else{
                    return;
                }
            }
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

void registrar_transferencia(FILE *arq_trans,int id_remetente,int id_destinatario, float valor){
    fprintf(arq_trans,"%i,%i,%.2f\n",id_remetente,id_destinatario,valor);
    printf("Dados da transferência foram adicionados no arquivo Tranasferência.csv");
}

void transferencia(pessoa *banco, int usuarios, FILE *arq_trans){
    if (usuarios<2){
        printf("Erro, menos de 2 usúarios! Impossivel realizar uma transferência\n");
        return;
    }
    int id_rem;
    printf("Remetente [ID]: ");
    scanf("%d", &id_rem);
    int indice_remetente = validacao_id(banco, usuarios, id_rem);

    while(indice_remetente == -1){
        printf("Usuario Invalido! Tente Novamente\n");
        printf("Remetente [ID]: ");
        scanf("%d", &id_rem);
        indice_remetente = validacao_id(banco, usuarios, id_rem);
    }


    int  id_dest;
    printf("Destinatario [ID]: ");
    scanf("%d", &id_dest);
    int indice_destinatario = validacao_id(banco, usuarios, id_dest);

    while(indice_destinatario == -1 || indice_destinatario==indice_remetente){
        printf("Usuario Invalido! Tente Novamente\n");
        printf("Destinatario [ID]: ");
        scanf("%d", &id_dest);
        indice_destinatario = validacao_id(banco, usuarios, id_dest);
        }
    float valor;
    printf("Valor da Transferência: R$");
    scanf("%f", &valor);
    if(valor<0.01){
        printf("\n======================================\nTRANSFERÊNCIA NEGADA! VALOR INVÁLIDO\n======================================\n\n");
    }
    else if(valor>banco[indice_remetente].saldo){
        printf("\n=========================================\nTRANSFERÊNCIA NEGADA! SALDO INSUFICIENTE\n=========================================\n\n");
    }
    else{
        banco[indice_remetente].saldo-=valor;
        banco[indice_destinatario].saldo+=valor;
        registrar_transferencia(arq_trans,id_rem,id_dest,valor);
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
    FILE *arq=fopen("data/Usuarios.csv", "w");
    if(arq==NULL){
        printf("Erro ao abrir arquivo!");
        return;
    }
    fprintf(arq,"ID,Nome,Sexo,Idade,Estado,Saldo\n");
    for(int i = 0; i < usuarios; i++){
        fprintf(arq, "%d,%s,%c,%d,%s,%.2f\n", banco[i].id, banco[i].nome,banco[i].sexo, banco[i].idade,banco[i].estado, banco[i].saldo);
    }\

    fclose(arq);
    printf("Dados salvos com sucesso no arquivo Usuarios.csv!\n");
}


int main(){
    //gemini mandou eu executar isso na main pelo menos uma vez
    srand(time(NULL));

    pessoa *banco_dados=NULL;
    int gerador_id=1;
    int escolha;
    int total_usuarios=0;

    //arquivo de registro de transferencia
    FILE *arq_trans = fopen("data/Transferências.csv", "r+");
    fprintf(arq_trans,"ID_remetente,ID_destinatario,Valor\n");
    if (arq_trans == NULL) {
    printf("Erro ao abrir arquivo de transferencias!\n");
    return 1;
    }

    do{
        printf("UAIBANK Menu\n");
        printf(" [1]-Adicionar Novo Usuário\n [2]-Adicionar Múltiplos Usuários\n [3]-Buscar por ID\n [4]-Realizar Transferência\n [5]-Remover Usúario\n [0]-Encerrar e Salvar\nEscolha: ");
        scanf("%d", &escolha);
        switch (escolha){
            case 1: novo_usuario(&banco_dados, &total_usuarios, &gerador_id); break;
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
