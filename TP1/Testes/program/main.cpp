#include <iostream>

#include "Vector.h"
#include "Matrix.h"
#include "Simplex.h"

void printInfo(Vector& cT, Matrix& A, Vector& b) {
    std::cout << "cT = " << cT << std::endl;
    std::cout << "A =\n" << A << std::endl;
    std::cout << "b = " << b << std::endl;
}

int main(int argc, const char** argv) {
    // Lendo o número de restrições e variáveis
    unsigned int numConstrains, numVariables;
    std::cin >> numConstrains >> numVariables;

    // Criando nossa função objetivo, vetor b, matriz de restrições
    Vector cT(numVariables + numConstrains);
    Vector b(numConstrains);
    Matrix A(numConstrains, numVariables + numConstrains);

    // Inserindo os valores na função objetivo
    for (unsigned int i = 0; i < numVariables; i++)
        std::cin >> cT[i];

    // Inserindo os valores na matriz de restrições e vetor b
    for (unsigned int i = 0; i < numConstrains; i++) {
        for (unsigned int j = 0; j < numVariables; j++) {
            std::cin >> A(i, j);
        }

        std::cin >> b[i];
    }

    // Inserindo variáveis de folga
    for (unsigned int i = numVariables; i < cT.GetSize(); i++)
        cT[i] = 0;

    for (unsigned int i = 0; i < numConstrains; i++)
        for (unsigned int j = numVariables; j < cT.GetSize(); j++)
            A(i, j) = i == (j - numVariables) ? 1 : 0;

    // Multiplicando o vetor cT por -1
    cT *= -1;

    printInfo(cT, A, b);
    std::cout << std::endl;

    // Escolhemos uma variável para entrar na base
    int varIn = chooseVariable(cT);
    while (varIn != -1) {
        // Escolhemos um pivot
        int pivot = choosePivot(A, b, varIn);

        // Caso seja -1, PL é ilimitada
        if (pivot == -1) {
            std::cout << "PL Ilimitada" << std::endl;
            break;
        }
        else {
            // Senão, pivoteamos e colocamos a matriz na forma canônica
            canonicForm(cT, A, b, pivot, varIn);
        }

        // Escolhemos outra variável para entrar na base
        varIn = chooseVariable(cT);
    }

    printInfo(cT, A, b);

    return 0;
}