#include "transacoes_bancarias.h"
#include "system.h"

void Saque(FILE *arquivo_banco) {
  Cliente cliente;
  int senha;
  int conta_saque;
  float valor_saque;

  printf("Digite a conta que deseja sacar: ");
  scanf("%d", &conta_saque);
  // verifica se a conta existe
  rewind(arquivo_banco);
  while (!feof(arquivo_banco)) {
    fread(&cliente, sizeof(cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;

    if (cliente.conta.numero_conta == conta_saque) {
      printf("Digite a senha: ");
      scanf("%d", &senha);

      if (senha == cliente.conta.senha) {

        printf("\n*DADOS DO CLIENTE*\n");
        printf("Codigo do cliente: %d\n", cliente.codigo_cliente);
        printf("Nome: %s\n", cliente.nome);
        printf("CPF: %s\n", cliente.cpf);
        printf("Número da conta: %d\n", cliente.conta.numero_conta);
        printf("Tipo da conta: %s\n\n", cliente.conta.tipo_conta);

        printf("Digite o valor do saque: ");
        scanf("%f", &valor_saque);

        // verifica se o saldo é suficiente
        if (cliente.conta.saldo >= valor_saque) {
          cliente.conta.saldo -= valor_saque;
          fseek(arquivo_banco, (conta_saque - 1001) * sizeof(Cliente),
                SEEK_SET);
          fwrite(&cliente, sizeof(Cliente), 1, arquivo_banco);
          printf("Saque realizado com sucesso!\n");

          printf("\n*COMPROVANTE DE SAQUE*\n");
          printf("-----------------------\n");
          printf("Número da conta: %d\n", conta_saque);
          printf("Nome: %s\n", cliente.nome);
          printf("Valor do saque: R$%.2f\n", valor_saque);
          printf("-----------------------\n");

          return;

        } else {
          printf("Saldo insuficiente!\n");
          return;
        }

      } else {
        printf("Senha inválida.\n");
        break;
      }

    } else if (cliente.conta.numero_conta != conta_saque &&
               feof(arquivo_banco)) {
      printf("Conta não encontrada\n");
    }
  }
}

void Deposito(FILE *arquivo_banco) {
  Cliente cliente;
  int conta_deposito;
  float valor_deposito;
  char resposta[2];

  printf("Digite a conta que deseja depositar: ");
  scanf("%d", &conta_deposito);
  // verifica se a conta existe
  rewind(arquivo_banco);
  while (!feof(arquivo_banco)) {
    fread(&cliente, sizeof(cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;

    if (cliente.conta.numero_conta == conta_deposito) {

      printf("\n*DADOS DO CLIENTE PARA DEPOSITO*\n");
      printf("Codigo do cliente: %d\n", cliente.codigo_cliente);
      printf("Nome: %s\n", cliente.nome);
      printf("CPF: %s\n", cliente.cpf);
      printf("Número da conta: %d\n", cliente.conta.numero_conta);
      printf("Tipo da conta: %s\n\n", cliente.conta.tipo_conta);

      printf("Os dados para deposito estão corretos? s/n: ");
      scanf(" %[^\n]", resposta);

      if (strcmp(resposta, "s") == 0) {
        printf("Digite o valor do deposito: ");
        scanf("%f", &valor_deposito);
        cliente.conta.saldo += valor_deposito;
        fseek(arquivo_banco, (conta_deposito - 1001) * sizeof(Cliente), SEEK_SET);
        fwrite(&cliente, sizeof(Cliente), 1, arquivo_banco);

          printf("Deposito realizado com sucesso!\n");
          printf("\n*COMPROVANTE DE DEPOSITO*\n");
          printf("-----------------------\n");
          printf("Número da conta: %d\n", conta_deposito);
          printf("Nome: %s\n", cliente.nome);
          printf("Valor do deposito: R$%.2f\n", valor_deposito);
          printf("-----------------------\n");
        
        return;
      } else {
        printf("Dados incorretos. Tente novamente.\n");
        break;
      }

    } else if (cliente.conta.numero_conta != conta_deposito &&
               feof(arquivo_banco)) {
      printf("Conta não encontrada\n");
    }
  }
}

void Transferencia(FILE *arquivo_banco) {
  Cliente cliente, cliente_transferencia;
  int conta;
  int conta_transferencia;
  int senha;
  float valor_transferencia;
  char resposta[2];

  printf("Digite sua conta: ");
  scanf("%d", &conta);
  // verifica se a conta existe
  rewind(arquivo_banco);
  while (!feof(arquivo_banco)) {
    fread(&cliente, sizeof(cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;
    if (cliente.conta.numero_conta == conta) {
      printf("Digite a senha: ");
      scanf("%d", &senha);

      if (senha == cliente.conta.senha) {
        printf("Digite a conta que deseja transferir: ");
        scanf("%d", &conta_transferencia);
        // verifica se a conta existe
        rewind(arquivo_banco);
        while (!feof(arquivo_banco)) {
          fread(&cliente_transferencia, sizeof(cliente_transferencia), 1,
                arquivo_banco);
          if (conta == conta_transferencia) {
            printf("\e[31mErro, Conta de origem igual a de destino!!\e[0m\n");
            return;
          }
          if (cliente_transferencia.conta.numero_conta == conta_transferencia) {

            printf("\n*DADOS DO CLIENTE PARA TRANSFERENCIA*\n");
            printf("Codigo do cliente: %d\n",
                   cliente_transferencia.codigo_cliente);
            printf("Nome: %s\n", cliente_transferencia.nome);
            printf("CPF: %s\n", cliente_transferencia.cpf);
            printf("Número da conta: %d\n",
                   cliente_transferencia.conta.numero_conta);
            printf("Tipo da conta: %s\n\n",
                   cliente_transferencia.conta.tipo_conta);

            printf("Os dados para transferencia estão corretos? s/n: ");
            scanf(" %[^\n]", resposta);

            if (strcmp(resposta, "s") == 0) {
              printf("Digite o valor da transferencia: ");
              scanf("%f", &valor_transferencia);

              // verifica se o saldo é suficiente
              if (cliente.conta.saldo >= valor_transferencia) {
                cliente.conta.saldo -= valor_transferencia;
                fseek(arquivo_banco, (conta - 1001) * sizeof(Cliente),
                      SEEK_SET);
                fwrite(&cliente, sizeof(Cliente), 1, arquivo_banco);
                cliente_transferencia.conta.saldo += valor_transferencia;
                fseek(arquivo_banco,
                      (conta_transferencia - 1001) * sizeof(Cliente), SEEK_SET);
                fwrite(&cliente_transferencia, sizeof(Cliente), 1,
                       arquivo_banco);

                printf("Transferencia realizada com sucesso!\n");

                printf("\n*COMPROVANTE DE TRANSFERENCIA*\n");
                printf("-----------------------\n");
                printf("Número da conta: %d\n", conta);
                printf("Nome: %s\n", cliente.nome);
                printf("Número da conta de transferencia: %d\n",
                       conta_transferencia);
                printf("Nome: %s\n", cliente_transferencia.nome);
                printf("Valor da transferencia: R$%.2f\n", valor_transferencia);
                printf("-----------------------\n");

                return;

              } else {
                printf("Saldo Insuficiente.\n");
                break;
              }

            } else {
              printf("Algum dado esta incorreto? Tente novamente.\n");
              return;
            }

          } else if (cliente_transferencia.conta.numero_conta !=
                         conta_transferencia &&
                     feof(arquivo_banco)) {
            printf("Conta não encontrada\n");
          }
        }

      } else {
        printf("Senha inválida.\n");
        return;
      }

    } else if (cliente.conta.numero_conta != conta && feof(arquivo_banco)) {
      printf("Conta não encontrada\n");
    }
  }
}