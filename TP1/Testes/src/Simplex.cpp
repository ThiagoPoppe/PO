#include <limits>
#include "Simplex.h"

int chooseVariable(Vector& v) {
    int minPos = -1;
    double min = std::numeric_limits<double>::infinity();

    for (unsigned int i = 0; i < v.GetSize(); i++)
        if (v[i] < 0 && v[i] < min) {
            minPos = i;
            min = v[i];
        }
    
    return minPos;
}

int choosePivot(Matrix& A, Vector& b, unsigned int col) {
    int pivot = -1;
    double min = std::numeric_limits<double>::infinity();

    for (unsigned int i = 0; i < b.GetSize(); i++) {
        if (A(i, col) > 0.0) {
            double div = b[i] / A(i, col);
            if (div < min) {
                pivot = i;
                min = div;
            }
        }
    }

    return pivot;
}

void canonicForm(Vector& cT, Matrix& A, Vector& b, unsigned int row, unsigned int col) {
    // Tornar o pivot igual a 1
    A[row] *= 1 / A(row, col);

    // Pivoteando
    for (unsigned int i = 0; i < b.GetSize(); i++) {
        if (i != row) {
            double m = (-1 * A(i, col));
            A[i] += A[row] * m;
            b[i] += b[row] * m;
        }
    }

    // Fazendo a PL ficar na forma canônica
    cT += A[row] * (-cT[col]);
}