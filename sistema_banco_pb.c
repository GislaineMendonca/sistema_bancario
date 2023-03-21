#include "clientes.h"
#include "system.h"
#include "transacoes_bancarias.h"

int main() {

  FILE *arquivo_banco;
  int ultimo_registro=0;
  int login, opcao;

  arquivo_banco = AbrirArquivo();
  
  ultimo_registro = AtualizaPosicaoRegistro(arquivo_banco);

  login = FazerLogin(login);
    while(login!=1){
        printf("Erro ao fazer login. Tente novamente.\n");
        login = FazerLogin(login);
    }

    printf("Logado com sucesso!\n");
    
    do{

      opcao = Menu(opcao);

      switch (opcao){
        case 1:
          printf("\n\t\t---- CADASTRAR CONTA ----\n");
          CadastraConta(&ultimo_registro, arquivo_banco);
          break;

        case 2:
          printf("\n\t\t---- LISTAGEM DE CONTAS ----\n");
          ListarContas(arquivo_banco);
          break;

        case 3:
          printf("\n\t\t---- BUSCAR CONTA ----\n");
          BuscarContas(arquivo_banco);
          break;

        case 4:
          printf("\n\t\t---- EDITAR CONTA ----\n");
          EditarConta(arquivo_banco);
          break;

        case 5:
          printf("\n\t\t---- EXCLUIR CONTA ----\n");
          ExcluirConta(arquivo_banco);
          break;

        case 6:
          printf("\n\t\t---- MUDAR SENHA DA CONTA ----\n");
          MudarSenha(arquivo_banco);
          break;

        case 7:
          printf("\n\t\t---- SAQUE ----\n");
          Saque(arquivo_banco);
          break;

        case 8:
          printf("\n\t\t---- DEPOSITO ----\n");
          Deposito(arquivo_banco);
          break;

        case 9:
          printf("\n\t\t---- TRANSFERENCIA ----\n");
          Transferencia(arquivo_banco);
          break;

        case 0:
          printf("Finalizando programa...\n");
          break;

        default:
          printf("Opcao invalida. Tente novamente.\n");
          break;
      }
    }while(opcao!=0);

  fclose(arquivo_banco);
  return 0;
}