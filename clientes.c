#include "clientes.h"
#include "system.h"

void CadastraConta(int *ultimo_registro, FILE *arquivo_banco) {
  Cliente cliente;

  printf("\n*INFORMAÇÕES DO CLIENTE*\n");
  printf("CPF do cliente: ");
  scanf(" %[^\n]", cliente.cpf);
  //verifica se o cpf já possui contas
  if (VerificaClienteExiste(arquivo_banco, cliente.cpf) == 2) {
    printf("Ja existe conta poupanca e corrente com este CPF!");
    return;
  } 
  //se o cliente já tiver uma conta
  if(VerificaClienteExiste(arquivo_banco, cliente.cpf) == 1){
    printf("Cliente já possui uma conta.\n");
    printf("Tipo de conta (corrente ou poupanca): ");
    scanf(" %[^\n]", cliente.conta.tipo_conta);
    if(VerificaContaExistente(arquivo_banco, cliente.cpf, cliente.conta.tipo_conta, ultimo_registro)==0){
      printf("Cliente já tem conta %s. Tente novamente.\n", cliente.conta.tipo_conta);
      return;
    }
    return;
  }

  //se o cliente não tiver nenhuma conta
  cliente.codigo_cliente = (*ultimo_registro) + 1;
  printf("Nome do cliente: ");
  scanf(" %[^\n]", cliente.nome);

  printf("\n*CONTA*\n");
  printf("Tipo de conta (corrente ou poupanca): ");
  scanf(" %[^\n]", cliente.conta.tipo_conta);

  //verifica se o tipo da conta é válido ou não
  if(VerificaTipoConta(cliente.conta.tipo_conta)==1){
    cliente.conta.numero_conta = (*ultimo_registro) + 1001;
    printf("Saldo: ");
    scanf("%f", &cliente.conta.saldo);
    printf("Senha: ");
    scanf("%d", &cliente.conta.senha);

    printf("\n*ENDEREÇO*\n");
    printf("Rua: ");
    scanf(" %[^\n]", cliente.endereco.rua);
    printf("Número: ");
    scanf("%d", &cliente.endereco.numero);
    printf("Bairro: ");
    scanf(" %[^\n]", cliente.endereco.bairro);
    printf("Cidade: ");
    scanf(" %[^\n]", cliente.endereco.cidade);
    printf("Estado: ");
    scanf(" %[^\n]", cliente.endereco.estado);
  
    fseek(arquivo_banco, (*ultimo_registro) * sizeof(Cliente), SEEK_SET);
    if ((fwrite(&cliente, sizeof(Cliente), 1, arquivo_banco)) != 1) {
      printf("Erro ao cadastrar cliente. Tente novamente.\n");
    } else {
      printf("Cliente cadastrado com sucesso!\n");
      (*ultimo_registro)++;
    }
  } else {
    printf("Tipo de conta não existente.\n");
  }
}

void ListarContas(FILE *arquivo_banco) {
  Cliente cliente;
  int cont=0;
  rewind(arquivo_banco);

  do {
    fread(&cliente, sizeof(Cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;

    else if (cliente.codigo_cliente != 0) {
      printf("\n*DADOS DO CLIENTE*\n");
      printf("Codigo do cliente: %d\n", cliente.codigo_cliente);
      printf("Nome: %s\n", cliente.nome);
      printf("CPF: %s\n", cliente.cpf);
      printf("Rua: %s\n", cliente.endereco.rua);
      printf("Número: %d\n", cliente.endereco.numero);
      printf("Bairro: %s\n", cliente.endereco.bairro);
      printf("Cidade: %s\n", cliente.endereco.cidade);
      printf("Estado: %s\n", cliente.endereco.estado);
      printf("Número da conta: %d\n", cliente.conta.numero_conta);
      printf("Tipo da conta: %s\n", cliente.conta.tipo_conta);
      printf("Saldo: R$%.2f\n", cliente.conta.saldo);
      cont++;
    }
  } while (!feof(arquivo_banco));

  if(cont==0){
    printf("Nenhuma conta encontrada.\n");
  }
}

void BuscarContas(FILE *arquivo_banco) {
  Cliente cliente;
  char cpf[15];
  int cont=0;
  rewind(arquivo_banco);

  printf("Entre com o CPF do cliente: ");
  scanf(" %[^\n]", cpf);
  while (!feof(arquivo_banco)) {
    fread(&cliente, sizeof(cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;
    
    if (strcmp(cliente.cpf, cpf) == 0) {
      printf("\n*DADOS DO CLIENTE*\n");
      printf("Codigo do cliente: %d\n", cliente.codigo_cliente);
      printf("Nome: %s\n", cliente.nome);
      printf("CPF: %s\n", cliente.cpf);
      printf("Rua: %s\n", cliente.endereco.rua);
      printf("Número: %d\n", cliente.endereco.numero);
      printf("Bairro: %s\n", cliente.endereco.bairro);
      printf("Cidade: %s\n", cliente.endereco.cidade);
      printf("Estado: %s\n", cliente.endereco.estado);
      printf("Número da conta: %d\n", cliente.conta.numero_conta);
      printf("Tipo da conta: %s\n", cliente.conta.tipo_conta);
      printf("Saldo: R$%.2f\n", cliente.conta.saldo);

      cont++;
    } 
  }
  if (cont==0){
    printf("Nenhuma conta encontrada.\n");
  }
}

void EditarConta(FILE *arquivo_banco) {
  int conta_cliente_edicao, cont=0;
  Cliente cliente_edicao;
  char edita_campo[2];
  rewind(arquivo_banco);

  printf("Informe a conta do cliente: ");
  scanf("%d", &conta_cliente_edicao);

  while (!feof(arquivo_banco)) {
    fread(&cliente_edicao, sizeof(Cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;
    
    if (cliente_edicao.conta.numero_conta == conta_cliente_edicao) {

      cont++;

      printf("Nome: %s\n", cliente_edicao.nome);
      printf("Deseja editar o nome? s/n: ");
      scanf(" %[^\n]", edita_campo);
      if (strcmp(edita_campo, "s") == 0) {
        printf("Entre com o novo mome: ");
        scanf(" %[^\n]", cliente_edicao.nome);
      }

      printf("CPF: %s\n", cliente_edicao.cpf);
      printf("Deseja editar o CPF? s/n: ");
      scanf(" %[^\n]", edita_campo);
      if (strcmp(edita_campo, "s") == 0) {
        printf("Entre com o novo cpf: ");
        scanf(" %[^\n]", cliente_edicao.cpf);
      }

      printf("Rua: %s\n", cliente_edicao.endereco.rua);
      printf("Deseja editar a rua? s/n: ");
      scanf(" %[^\n]", edita_campo);
      if (strcmp(edita_campo, "s") == 0) {
        printf("Entre com o novo nome da rua: ");
        scanf(" %[^\n]", cliente_edicao.endereco.rua);
      }

      printf("Número: %d\n", cliente_edicao.endereco.numero);
      printf("Deseja editar a número da rua? s/n: ");
      scanf(" %[^\n]", edita_campo);
      if (strcmp(edita_campo, "s") == 0) {
        printf("Entre com o novo numero da rua: ");
        scanf("%d", &cliente_edicao.endereco.numero);
      }

      printf("Bairro: %s\n", cliente_edicao.endereco.bairro);
      printf("Deseja editar o bairro? s/n: ");
      scanf(" %[^\n]", edita_campo);
      if (strcmp(edita_campo, "s") == 0) {
        printf("Entre com o novo bairro: ");
        scanf(" %[^\n]", cliente_edicao.endereco.bairro);
      }

      printf("Cidade: %s\n", cliente_edicao.endereco.cidade);
      printf("Deseja editar a cidade? s/n: ");
      scanf(" %[^\n]", edita_campo);
      if (strcmp(edita_campo, "s") == 0) {
        printf("Entre com a nova cidade: ");
        scanf(" %[^\n]", cliente_edicao.endereco.cidade);
      }

      printf("Estado: %s\n", cliente_edicao.endereco.estado);
      printf("Deseja editar o estado? s/n: ");
      scanf(" %[^\n]", edita_campo);
      if (strcmp(edita_campo, "s") == 0) {
        printf("Entre com o novo estado: ");
        scanf(" %[^\n]", cliente_edicao.endereco.estado);
      }
    
      fseek(arquivo_banco, (conta_cliente_edicao - 1001) * sizeof(Cliente), SEEK_SET);
      if ((fwrite(&cliente_edicao, sizeof(Cliente), 1, arquivo_banco)) != 1) {
        printf("Erro ao editar dados da conta.\n");
        return;
      } else {
        printf("Dados da conta editados com sucesso.\n");
      }
    } 
  }
  if (cont==0){
    printf("Nenhuma conta encontrada.\n");
    return;
  }
}

void ExcluirConta(FILE *arquivo_banco) {
  Cliente cliente;
  Cliente cliente_nulo = {0, " ", " ", " ", 0, " ", " ", " ", 0, " ", 0, 0};
  int conta_cliente_excluir, cont=0;
  char escolha[2];
  

  printf("Informe a que deseja excluir: ");
  scanf("%d", &conta_cliente_excluir);

  while (!feof(arquivo_banco)) {
    fread(&cliente, sizeof(Cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;
    
    if (cliente.conta.numero_conta == conta_cliente_excluir){ 
      cont++;

      printf("\t\t\n---- CONTA ENCONTRADA ----");
      printf("\t\t\n---- DADOS DO CLIENTE ----\n");
      printf("Codigo do cliente: %d\n", cliente.codigo_cliente);
      printf("Nome: %s\n", cliente.nome);
      printf("CPF: %s\n", cliente.cpf);
      printf("Rua: %s\n", cliente.endereco.rua);
      printf("Número: %d\n", cliente.endereco.numero);
      printf("Bairro: %s\n", cliente.endereco.bairro);
      printf("Cidade: %s\n", cliente.endereco.cidade);
      printf("Estado: %s\n", cliente.endereco.estado);
      printf("Número da conta: %d\n", cliente.conta.numero_conta);
      printf("Tipo da conta: %s\n", cliente.conta.tipo_conta);
      printf("Saldo: %.2f\n", cliente.conta.saldo);

      printf("Deseja excluir esta conta? s/n: ");
      scanf(" %[^\n]", escolha);

      if (strcmp(escolha, "s") == 0) {
        fseek(arquivo_banco, (conta_cliente_excluir - 1001) * sizeof(Cliente), SEEK_SET);
        if ((fwrite(&cliente_nulo, sizeof(Cliente), 1, arquivo_banco)) != 1) {
          printf("Erro ao excluir conta.\n");
          return;
        } else {
          printf("Conta excluída com sucesso.\n");
        }
      }
    }
  }
  if (cont == 0) {
    printf("Conta não encontrada.\n");
    return;
  }
}

void MudarSenha(FILE *arquivo_banco) {
  char escolha[2];
  int num_conta;
  Cliente cliente_mudar_senha;
  int nova_senha, nova_senha_2;
  rewind(arquivo_banco);

  printf("Informe o numero da conta: ");
  scanf("%d", &num_conta);
  while (!feof(arquivo_banco)) {
    fread(&cliente_mudar_senha, sizeof(Cliente), 1, arquivo_banco);
    if (cliente_mudar_senha.conta.numero_conta == num_conta) {

      printf("\n*DADOS DO CLIENTE*\n");
      printf("Codigo do cliente: %d\n", cliente_mudar_senha.codigo_cliente);
      printf("Nome: %s\n", cliente_mudar_senha.nome);
      printf("CPF: %s\n", cliente_mudar_senha.cpf);
      printf("Rua: %s\n", cliente_mudar_senha.endereco.rua);
      printf("Número: %d\n", cliente_mudar_senha.endereco.numero);
      printf("Bairro: %s\n", cliente_mudar_senha.endereco.bairro);
      printf("Cidade: %s\n", cliente_mudar_senha.endereco.cidade);
      printf("Estado: %s\n", cliente_mudar_senha.endereco.estado);
      printf("Número da conta: %d\n", cliente_mudar_senha.conta.numero_conta);
      printf("Tipo da conta: %s\n", cliente_mudar_senha.conta.tipo_conta);

      printf("Deseja mudar a senha desta conta? (s/n): \n");
      scanf(" %[^\n]", escolha);

      if (strcmp(escolha, "s") == 0) {
        printf("Digite a nova senha: ");
        scanf("%d", &nova_senha);

        printf("Digite a nova senha novamente: ");
        scanf("%d", &nova_senha_2);

        if (nova_senha == nova_senha_2) {
          cliente_mudar_senha.conta.senha = nova_senha;

          fseek(arquivo_banco,
                (cliente_mudar_senha.codigo_cliente - 1) * sizeof(Cliente),
                SEEK_SET);
          if ((fwrite(&cliente_mudar_senha, sizeof(Cliente), 1,
                      arquivo_banco)) != 1) {
            printf("Erro ao mudar a senha.\n");
            return;
          } else {
            printf("Senha alterada com sucesso.\n");
          }
        } else {
          printf("As senhas não coincidem. Tente novamente.\n");
        }
      }
      break;

    } else if (cliente_mudar_senha.conta.numero_conta != num_conta &&
               feof(arquivo_banco)) {
      printf("Conta não encontrada.\n");
    }
  }
}