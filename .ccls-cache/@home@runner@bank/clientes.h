#ifndef _CLIENTES_H
#define _CLIENTES_H

#include <stdio.h>

void CadastraConta (int *, FILE *);
void ListarContas (FILE *);
void BuscarContas(FILE *);
void EditarConta (FILE *);
void ExcluirConta(FILE *);
void MudarSenha (FILE *);

#endif