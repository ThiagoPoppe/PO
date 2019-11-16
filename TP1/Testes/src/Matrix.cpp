#include "Matrix.h"

// Definindo o construtor da classe
Matrix::Matrix(unsigned int rows, unsigned int cols)
: numRows(rows), numCols(cols), elements(rows) {
    for (unsigned int i = 0; i < rows; i++)
        elements[i] = Vector(cols);
}

// Definindo o destrutor da classe
Matrix::~Matrix() {}

// Método para retornar o número de linhas da matriz
unsigned int Matrix::GetNumRows() const {
    return numRows;
}

// Método para retornar o número de colunas da matriz
unsigned int Matrix::GetNumCols() const {
    return numCols;
}

// Definindo indexação de uma Matrix (retornar linha)
Vector& Matrix::operator[](unsigned int i) {
    return elements[i];
}

// Definindo a indexação de uma Matrix (retornar elemento)
double& Matrix::operator()(unsigned int i, unsigned int j) {
    return elements[i][j];
}

// Definindo o stream de uma Matrix
std::ostream& operator<<(std::ostream& os, Matrix& m) {
    for (unsigned int i = 0; i < m.numRows; i++) {
        os << m.elements[i];
        if (i != m.numRows - 1)
            os << "\n";
    }

    return os;
}