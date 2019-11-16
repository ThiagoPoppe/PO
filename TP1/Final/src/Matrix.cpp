#include <iomanip>

#include "Matrix.h"

Matrix::Matrix(unsigned int rows, unsigned int cols)
: elements(rows) {
    for (unsigned int i = 0; i < rows; i++)
        elements[i] = Vector(cols);
}

Matrix::~Matrix() { }

Vector& Matrix::operator[](unsigned int i) {
    return elements[i];
}

float& Matrix::operator()(unsigned int i, unsigned int j) {
    return elements[i][j];
}

std::ostream& operator<<(std::ostream& os, Matrix& m) {
    for (unsigned int i = 0; i < m.GetNumRows(); i++)
        os << std::setprecision(7) << m[i] << "\n";

    return os;
}

unsigned int Matrix::GetNumRows() {
    return elements.size();
}

unsigned int Matrix::GetNumCols() {
    return elements[0].GetSize();
}