#include "Simplex.h"
#include "MathMisc.h"

int chooseVariable(Vector& cT) {
    for (unsigned int i = 0; i < cT.GetSize(); i++)
        if (cT[i] < 0)
            return i;

    return -1;
}

int choosePivot(Matrix& A, Vector& b, unsigned int col) {
    int minPos = -1;
    int min = -1;

    // Procurando a linha do pivô tal que b[i] / A(i, col) seja o menor possível
    for (unsigned int i = 0; i < A.GetNumRows(); i++) {
        if (A(i, col) > 0) {
            float div = (float) b[i] / A(i, col);

            // Se min == -1, foi o primeiro encontro de um div positivo!
            if (min == -1) {
                minPos = i;
                min = div;
            }

            // Senão, temos que verificar se o novo div encontrado é menor do que o min
            else if (div < min) {
                minPos = i;
                min = div;
            }
        }
    }

    // Retorna o índice da linha do pivô caso encontre o mesmo. Senão -1
    return minPos;
}

void findObviousBase(Vector& cT, Matrix& A, PairList& basePositions) {
    for (unsigned int j = 0; j < cT.GetSize(); j++) {
        if (cT[j] == 0) {
            int row = findRowOf1(A, j);
            if (row != -1)
                basePositions.InsertPair(row, j);
        }
    }
}

void canonicForm(Vector& cT, Matrix& A, Vector& b, float& resultValue, unsigned int row, unsigned int col) {
    float m = 1.0 / A(row, col);
    fixPrecision5(m);
    
    // Divindo toda a linha do pivô pelo mesmo
    b[row] *= m;
    fixPrecision5(b[row]);

    A[row] *= m;
    fixPrecision5(A[row]);

    // Zerando toda a coluna do pivô (excluindo a dele)
    for (unsigned int i = 0; i < A.GetNumRows(); i++) {
        if (i != row) {
            m = (-1 * A(i, col));
            fixPrecision5(m);

            A[i] += A[row] * m;
            fixPrecision5(A[i]);

            b[i] += b[row] * m;
            fixPrecision5(b[i]);
        }
    }

    // Zerando o valor do vetor custo na coluna do pivô
    m = (-1 * cT[col]);
    fixPrecision5(m);

    cT += A[row] * m;
    fixPrecision5(cT);

    resultValue += b[row] * m;
    fixPrecision5(resultValue);
}

int findRowOf1(Matrix& A, unsigned int col) {
    // Percorreremos a coluna contando o número de 1's e 0's vistos
    unsigned int countOnes = 0;
    unsigned int countZeros = 0;
    unsigned row = 0;
    for (unsigned int i = 0; i < A.GetNumRows(); i++) {
        // Se na coluna de uma variável básica, encontrarmos 1, guardamos a linha
        if (A(i, col) == 1) {
            countOnes++;
            row = i;
        }
        else if (A(i, col) == 0) 
            countZeros++;
    }

    // Caso a coluna não seja básica, retornamos -1. Senão retornamos a linha do elemento 1
    // Para saber se a mesma é básica, basta vermos se temos apenas um 1 e 0's na coluna
    bool isBase = (countOnes == (A.GetNumRows() - countZeros));
    return isBase ? row : -1;
}

bool runSimplex(Vector& cT, Matrix& A, Vector& b, float& resultValue, PairList& basePositions, int& col, unsigned int numVariables, unsigned int numConstrains) {
    while (col != -1) {
        // Escolhendo o pivô
        int row = choosePivot(A, b, col);

        // Caso não encontremos nenhum pivô válido, nossa PL é ilimitada
        if (row == -1)
            return false;

        // Senão, inserimos a posição do pivô na lista e colocamos a PL na forma canônica
        basePositions.InsertPair(row, col);
        canonicForm(cT, A, b, resultValue, row, col);

        // Procuramos a próxima variável à entrar na base
        col = chooseVariable(cT);
    }

    return true;
}

Vector createAux(Vector& cT, Matrix& A, unsigned int numConstrains) {
    // Inserindo variáveis da PL auxiliar
    Vector cT_aux(cT.GetSize() + numConstrains);
    
    for (unsigned int i = 0; i < cT.GetSize(); i++)
        cT_aux[i] = 0;

    for (unsigned int i = cT.GetSize(); i < cT_aux.GetSize(); i++)
        cT_aux[i] = 1;

    for (unsigned int i = 0; i < numConstrains; i++) {
        for (unsigned int j = 0; j < numConstrains; j++) {
            unsigned int num = (i == j) ? 1 : 0;
            A[i].elements.push_back(num);
        }
    }

    return cT_aux;
}

Vector findResultVector(PairList& basePositions, Vector& b, unsigned int numVariables) {
    // Criando o vetor resultante e inicializando com 0
    Vector result(numVariables);
    for (unsigned int i = 0; i < numVariables; i++)
        result[i] = 0;

    // Percorrendo os índices dos pivôs.
    // Note que p.first -> linha do pivô e p.second -> coluna do pivô
    // Com isso, basta fazermos result[col] = b[row], para valores de col menores
    // que o número de variáveis do problema
    for (auto p : basePositions.GetPairs()) {
        if (p.second < numVariables)
            result[p.second] = b[p.first];
    }

    return result;
}

Vector findOptimalCertificate(Vector& cT, unsigned int numVariables) {
    // Criando o certificado (que será a parte das variáveis de folga no vetor de custo)
    Vector certificate(cT.GetSize() - numVariables);
    
    // Caminhando por esses valores guardando no certificado
    for (unsigned int i = numVariables; i < cT.GetSize(); i++)
        certificate[i - numVariables] = cT[i];

    return certificate;
}

Vector findUnlimitedCertificate(PairList& basePositions, Matrix& A, unsigned int col, unsigned int numVariables) {
    Vector certificate(numVariables);
    for (unsigned int i = 0; i < numVariables; i++)
        certificate[i] = 0;


    certificate[col] = 1;
    for (auto p : basePositions.GetPairs()) {
        if (A(p.first, col) != 0)
            certificate[p.second] = -A(p.first, col);
        else
            certificate[p.second] = A(p.first, col);
    }

    return certificate;
}

Vector findUnfeasibilityCertificate(Vector& cT_aux, unsigned int numVariables, unsigned int numConstrains) {
    Vector certificate(numConstrains);

    for (unsigned int i = numVariables; i < numVariables + numConstrains; i++)
        certificate[i - numVariables] = cT_aux[i];

    return certificate; 
}

bool hasNegative(Matrix& A, Vector& b) {
    // Percorrendo o vetor b. Caso encontremos um valor negativo, multiplicamos o mesmo por -1
    // e guardamos essa informação
    bool found = false;
    for (unsigned int i = 0; i < b.GetSize(); i++) {
        if (b[i] < 0) {
            A[i] *= -1;
            b[i] *= -1;
            found = true;
        }
    }

    // Retorna false caso não há nenhum elemento negativo e true caso contrário
    return found;
}