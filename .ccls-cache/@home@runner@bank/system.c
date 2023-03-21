#include "system.h"

int AtualizaPosicaoRegistro(FILE *arquivo_banco){
  Cliente cliente;
  int atualiza_ultimo_registro=0;

  do{

    fread(&cliente, sizeof(Cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;
    atualiza_ultimo_registro++;
    
  }while(!feof(arquivo_banco));

  rewind(arquivo_banco);
  
  return atualiza_ultimo_registro;
}

int Menu (int opcao){
  
  printf("\n\t\t---- SISTEMA BANCO PB ----\n");
  printf("1. Cadastro de conta.\n");
  printf("2. Listagem de contas.\n");
  printf("3. Busca de conta.\n");
  printf("4. Edição de conta.\n");
  printf("5. Excluir conta.\n");
  printf("6. Mudar senha da conta.\n");
  printf("7. Saques.\n");
  printf("8. Depósitos.\n");
  printf("9. Transferências.\n");
  printf("0. Sair.\n");

  printf("Informe a opção desejada: ");
  scanf("%d", &opcao);
  printf("----------------------------------\n");
  
  return opcao;
}

int FazerLogin (int login){
  Usuario usuario[3]={"usuario1", "1234", "usuario2", "4567", "usuario3", "7890"};
  Usuario usuario_temp;

  printf("\t\t---- BEM VINDO ----\n");
  printf("Login: ");
  scanf(" %[^\n]", usuario_temp.login);
  printf("Senha: ");
  scanf(" %[^\n]", usuario_temp.senha);

  for(int i=0; i<3; i++){
    if((strcmp(usuario_temp.login, usuario[i].login)==0) && (strcmp(usuario_temp.senha, usuario[i].senha)==0)){
      return 1;
    }  
  }
  return 0;
}

FILE* AbrirArquivo(){
  FILE *arquivo_banco;

  if((arquivo_banco = fopen("cadastro_banco.bin", "r+")) == NULL){
    arquivo_banco = fopen("cadastro_banco.bin", "w+");
  }

  if(arquivo_banco == NULL){
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }
  return arquivo_banco;
}

int VerificaClienteExiste(FILE *arquivo_banco, char cpf[]){
  Cliente cliente;
  int cont=0;
  rewind(arquivo_banco);
  
  while (!feof(arquivo_banco)) {
    fread(&cliente, sizeof(cliente), 1, arquivo_banco);
    if (feof(arquivo_banco))
      break;
    if (strcmp(cliente.cpf, cpf) == 0){
      cont++;
    }
  }
  //se o cliente tiver uma conta
  if(cont==1){
    return 1;
  }

  //se o cliente tiver duas
  else if(cont==2){
    return 2;
  }
  
  return 0;
}

int VerificaTipoConta (char tipo[]){
  
  if((strcmp("poupanca", tipo) == 0) || (strcmp("corrente", tipo) == 0)){
    return 1;
  }
  return 0;
}

int VerificaContaExistente(FILE *arquivo_banco, char cpf[], char tipo[], int *ultimo_registro){
  Cliente cliente_temp, cliente;
  rewind(arquivo_banco);

  while (!feof(arquivo_banco)) {
    fread(&cliente_temp, sizeof(Cliente), 1, arquivo_banco);

    //procura a outra conta que o cliente tem
    if (strcmp(cliente_temp.cpf, cpf) == 0){
      //verifica se a conta e de outro tipo
      if(strcmp(tipo, cliente_temp.conta.tipo_conta) != 0){
        //verifica se o tipo de conta e valido
        if(VerificaTipoConta(tipo) == 1){
          //copia os dados da conta já existente
          cliente.codigo_cliente = cliente_temp.codigo_cliente;
          strcpy(cliente.nome, cliente_temp.nome);
          strcpy(cliente.cpf, cpf);
          cliente.endereco = cliente_temp.endereco;
          //informacoes da nova conta
          cliente.conta.numero_conta = (*ultimo_registro) + 1001;
          strcpy(cliente.conta.tipo_conta, tipo);
          printf("Saldo: ");
          scanf("%f", &cliente.conta.saldo);
          printf("Senha: ");
          scanf("%d", &cliente.conta.senha);

          fseek(arquivo_banco, (*ultimo_registro) * sizeof(Cliente), SEEK_SET);
          if ((fwrite(&cliente, sizeof(Cliente), 1, arquivo_banco)) != 1) {
            printf("Erro ao cadastrar cliente. Tente novamente.\n");
            return 1;
          } else {
            printf("Cliente cadastrado com sucesso!\n");
            (*ultimo_registro)++;
            return 1;
          }
        }else{
          printf("Tipo de conta inexistente.\n");
          return 1;
        }
      }
    }
  }
  return 0;
} 