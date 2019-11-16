#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

class Matrix {
private:
    unsigned int numRows;
    unsigned int numCols;

public:
    std::vector<Vector> elements;

public:
    // Construtor e destrutor
    Matrix(unsigned int rows, unsigned int cols);
    ~Matrix();

    // Métodos para pegar as dimensões da matriz
    unsigned int GetNumRows() const;
    unsigned int GetNumCols() const;

    /** Sobrecarga de operadores **/
    // Indexação usando []
    Vector& operator[](unsigned int i);

    // Indexação usando ()
    double& operator()(unsigned int i, unsigned int j);

    // Stream
    friend std::ostream& operator<<(std::ostream& os, Matrix& v);
};

#endif