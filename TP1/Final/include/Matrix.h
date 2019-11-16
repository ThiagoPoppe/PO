#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

// Classe para facilitar o acesso à componentes de uma matriz
class Matrix {
public:
    std::vector<Vector> elements;

public:
    // Construtor e destrutor
    Matrix(unsigned int rows, unsigned int cols);
    ~Matrix();

    // Definindo a indexação que retorna a i-ésima linha
    Vector& operator[](unsigned int i);

    // Definido a indexação que retorna o elemento ij
    float& operator()(unsigned int i, unsigned int j);

    // Definindo o stream de output da matriz
    friend std::ostream& operator<<(std::ostream& os, Matrix& m);

    // Definindo métodos para retornar o tamanho da matriz
    unsigned int GetNumRows();
    unsigned int GetNumCols();
};

#endif