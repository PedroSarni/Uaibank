#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
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
} pessoa;

void limpa_buffer();

int gerar_codigo_2FA();

void exibir_usuario();

void enviar_email_2FA(int codigo, char email[]);

void recuperar_senha(char email[], pessoa *banco, int usuario);

bool limparTelefone(const char *entrada, char *saida);

void novo_usuario(pessoa **banco, int *usuarios, int *gerador_id);

void multiplos_usuario(pessoa **banco, int *usuarios, int *gerador_id);

void busca_id(pessoa *banco, int usuario);

int validacao_id(pessoa *banco, int usuarios, int id_procurado);

void registrar_transferencia(FILE *arq_trans, int id_remetente,
                             int id_destinatario, float valor);

void transferencia(pessoa *banco, int usuarios, FILE *arq_trans);

void remocao_usuario(pessoa **banco, int *usuarios);

void salvar_encerrar(pessoa *banco, int usuarios);

#endif