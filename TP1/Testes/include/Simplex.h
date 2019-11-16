#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "Vector.h"
#include "Matrix.h"

int chooseVariable(Vector& v);
int choosePivot(Matrix& A, Vector& b, unsigned int col);
void canonicForm(Vector& cT, Matrix& A, Vector& b, unsigned int row, unsigned int col);

#endif