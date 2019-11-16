#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "Vector.h"
#include "Matrix.h"
#include "PairList.h"
#include "MathMisc.h"

// Função que retorna o índice da variável que irá entrar na base. Retorna -1 caso não encontre nenhuma variável
int chooseVariable(Vector& cT);

/* Função que dado a coluna da variável que irá entrar na base,
   retorna o índice da linha do pivô escolhido. Retorna -1 caso não encontre nenhum pivô */
int choosePivot(Matrix& A, Vector& b, unsigned int col);

// Função que procura por uma base óbvia antes de começarmos o SIMPLEX
void findObviousBase(Vector& cT, Matrix& A, PairList& basePositions);

// Função que realiza o processo de pivotação e transforma a PL na sua forma canônica
void canonicForm(Vector& cT, Matrix& A, Vector& b, float& resultValue, unsigned int row, unsigned int col);

// Função que retorna se uma coluna da matriz é básica
int findRowOf1(Matrix& A, unsigned int col);

// Função que executa o Simplex retornando true caso encontre uma solução ótima e false caso contrário
bool runSimplex(Vector& cT, Matrix& A, Vector& b, float& resultValue, PairList& basePositions, int& col, unsigned int numVariables, unsigned int numConstrains);

// Função que cria a PL auxiliar retornando o vetor de custo auxiliar
Vector createAux(Vector& cT, Matrix& A, unsigned int numConstrains);

// Função que retorna o vetor resultante
Vector findResultVector(PairList& basePositions, Vector& b, unsigned int numVariables);

// Função que retorna o certificado de otimalidade
Vector findOptimalCertificate(Vector& cT, unsigned int numVariables);

// Função que retorna o certificado de ilimitada
Vector findUnlimitedCertificate(PairList& basePositions, Matrix& A, unsigned int col, unsigned int numVariables);

// Função que retorna o certificado de inviabilidade
Vector findUnfeasibilityCertificate(Vector& cT_aux, unsigned int numVariables, unsigned int numConstrains);

// Função que verifica se o vetor b possui algum elemento menor que 0, multiplicando por -1 as linhas de A e b
bool hasNegative(Matrix& A, Vector& b);

#endif