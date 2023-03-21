#ifndef _SISTEMA_H
#define _SISTEMA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char rua[30];
  int numero;
  char bairro[30];
  char cidade[30];
  char estado[30];
}Endereco;

typedef struct{
  int numero_conta;
  char tipo_conta[15];
  float saldo;
  int senha;
}Conta;

typedef struct{
  int codigo_cliente;
  char nome[30];
  char cpf[15];
  Endereco endereco;
  Conta conta;
}Cliente;

typedef struct{
  char login[20];
  char senha[20];
}Usuario;

FILE* AbrirArquivo();
int AtualizaPosicaoRegistro(FILE *);
int FazerLogin (int login);
int Menu (int opcao);
int VerificaClienteExiste(FILE *arquivo_banco, char cpf[]);
int VerificaTipoConta (char tipo[]);
int VerificaContaExistente(FILE *arquivo_banco, char cpf[], char tipo[], int *ultimo_registro);

#endif