#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>

// Classe para realizar operações com vetores
class Vector {
public:
    std::vector<float> elements;

public:
    // Construtor e destrutor
    Vector();
    Vector(unsigned int n);
    ~Vector();

    // Define a soma entre dois vetores
    Vector operator+(const Vector& other);
    Vector& operator+=(const Vector& other);

    // Define o produto de um vetor por um escalar
    Vector operator*(float num);
    Vector& operator*=(float num);

    // Define a indexação do vetor
    float& operator[](unsigned int i);

    // Define o stream de output do vetor
    friend std::ostream& operator<<(std::ostream& os, Vector& v);

    // Método para retornar o tamanho do vetor
    unsigned int GetSize();
};

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

class PairList {
private:
    std::list<std::pair<unsigned int, unsigned int>> pairs;

public:
    PairList();
    ~PairList();

    void InsertPair(unsigned int x, unsigned int y);
    void RemoveInvalidPairs(unsigned int numVariables, unsigned int numConstrains);
    void PrintPairs();

    bool IsEmpty();

    std::list<std::pair<unsigned int, unsigned int>> GetPairs();
};


// Função auxiliar para fixar a precisão das operações usando 5 casas decimais
void fixPrecision5(float& num);

// Função auxiliar para fixar a precisão das operações usando 5 casas decimais (polimorfismo)
void fixPrecision5(Vector& v);

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

Vector::Vector() { }

Vector::Vector(unsigned int n)
: elements(n) { }

Vector::~Vector() { }

float& Vector::operator[](unsigned int i) {
    return elements[i];
}

Vector Vector::operator+(const Vector& other) {
    Vector newVector(GetSize());
    for (unsigned int i = 0; i < GetSize(); i++) {
        newVector[i] = elements[i] + other.elements[i];
        fixPrecision5(newVector[i]);
    }

    return newVector;
}

Vector& Vector::operator+=(const Vector& other) {
    for (unsigned int i = 0; i < GetSize(); i++) {
        elements[i] += other.elements[i];
        fixPrecision5(elements[i]);
    }

    return *this;
}

Vector Vector::operator*(float num) {
    Vector newVector(GetSize());
    for(unsigned int i = 0; i < GetSize(); i++) {
        newVector[i] = elements[i] * num;
        fixPrecision5(newVector[i]);
    }

    return newVector;
}

Vector& Vector::operator*=(float num) {
    for(unsigned int i = 0; i < GetSize(); i++) {
        elements[i] *= num;
        fixPrecision5(elements[i]);
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, Vector& v) {
    for(unsigned int i = 0; i < v.GetSize(); i++)
        os << std::setprecision(7) << v[i] << " ";
    
    return os;
}

unsigned int Vector::GetSize() {
    return elements.size();
}

void fixPrecision5(float& num) {
    if (std::abs(num) < 1e-5)
        num = 0.0;
}

void fixPrecision5(Vector& v) {
    for (unsigned int i = 0; i < v.GetSize(); i++)
        fixPrecision5(v[i]);
}

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

PairList::PairList() { }
PairList::~PairList() { }

void PairList::InsertPair(unsigned int x, unsigned int y) {
    auto newPair = std::make_pair(x, y);

    for (auto p : GetPairs()) {
        if (p.first == x) {
            pairs.remove(p);
            break;
        }
    }

    pairs.push_back(newPair);
}

void PairList::RemoveInvalidPairs(unsigned int numVariables, unsigned int numConstrains) {
    for (auto p : GetPairs()) {
        if (p.second > numVariables)
            pairs.remove(p);
    }
}

void PairList::PrintPairs() {
    for (auto p : pairs) {
        std::cout << "(" << p.first << ", " << p.second << ")" << std::endl;
    }
}

bool PairList::IsEmpty() {
    return pairs.size() == 0;
}

std::list<std::pair<unsigned int, unsigned int>> PairList::GetPairs() {
    return pairs;
}

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





int main(int argc, const char** argv) {
    // Lendo o número de restrições e variáveis
    unsigned int numConstrains, numVariables;
    std::cin >> numConstrains >> numVariables;

    // Definindo o valor objetivo
    float resultValue = 0.0;

    // Criando uma lista de pares que irão conter a linha e coluna dos pivots
    PairList basePositions;

    // Criando o vetor de custo e lendo seus valores
    Vector cT(numVariables);
    for (unsigned i = 0; i < numVariables; i++)
        std::cin >> cT[i];

    // Criando a matriz de restrições, o vetor b e lendo seus valores
    Matrix A(numConstrains, numVariables);
    Vector b(numConstrains);
    for (unsigned i = 0; i < numConstrains; i++) {
        for (unsigned j = 0; j < numVariables; j++)
            std::cin >> A(i, j);

        std::cin >> b[i];
    }

    // Verificando se possuímos uma base óbvia antes de adicionarmos as variáveis de folga
    findObviousBase(cT, A, basePositions);

    // Adicionando as variáveis de folga
    for (unsigned i = 0; i < numConstrains; i++)
        cT.elements.push_back(0);

    for (unsigned i = 0; i < numConstrains; i++) {
        for (unsigned j = 0; j < numConstrains; j++) {
            int num = (i == j) ? 1 : 0;
            A[i].elements.push_back(num);
        }
    }

    // Multiplicando o vetor de custo por -1
    cT *= -1;

    // Verificando de antemão se a PL possui algum valor de b negativo.
    // Se sim, primeiramente faremos a auxiliar para encontrar as bases
    if (hasNegative(A, b)) {
        // Criando a auxiliar
        Vector cT_aux = createAux(cT, A, numConstrains);
 
        // Tornando a auxiliar canônica
        for (unsigned i = 0; i < A.GetNumRows(); i++) {
            float temp = (-1 * b[i]);
            fixPrecision5(temp);

            resultValue += temp;
            fixPrecision5(resultValue);

            cT_aux += (A[i] * -1);
            fixPrecision5(cT_aux);
        }

        // Escolhendo uma variável para entrar na base, assim começando o Simplex
        int col = chooseVariable(cT); 

        // Rodando o Simplex
        runSimplex(cT_aux, A, b, resultValue, basePositions, col, numVariables, numConstrains);

        // Caso o valor objetivo dê menor que 0, temos que a PL é inviável
        if (resultValue < 0) {
            // Calculamos o certificado de inviabilidade
            Vector certificate = findUnfeasibilityCertificate(cT_aux, numVariables, numConstrains);

            // Imprimimos as informações necessárias
            std::cout << "inviavel" << std::endl;
            std::cout << certificate << std::endl;
            return 0;
        }

        // Senão, iremos retirar as variáveis auxiliares da matriz A
        for (unsigned i = 0; i < numConstrains; i++)
            for (unsigned j = 0; j < numConstrains; j++)
                A[i].elements.pop_back();

        // Removendo pivots que não são mais válidos
        basePositions.RemoveInvalidPairs(numVariables, numConstrains);

        // Atualizando o vetor de custo e o valor objetivo
        for (auto p : basePositions.GetPairs()) {
            float m = (-1 * cT[p.second]);
            fixPrecision5(m);

            cT += A[p.first] * m;
            fixPrecision5(cT);

            resultValue += b[p.first] * m;
            fixPrecision5(resultValue);
        }
    }

    // Escolhendo uma variável para entrar na base, assim começando o Simplex
    int col = chooseVariable(cT); 

    // Rodando o Simplex
    bool foundOptimal = runSimplex(cT, A, b, resultValue, basePositions, col, numVariables, numConstrains);

    if (foundOptimal) {
        // Calculamos o vetor resultado  e certificado de otimalidade
        Vector resultVector = findResultVector(basePositions, b, numVariables);
        Vector certificate = findOptimalCertificate(cT, numVariables);

        // Imprimimos as informações necessárias
        std::cout << "otima" << std::endl;
        std::cout << resultValue << std::endl;
        std::cout << resultVector << std::endl;
        std::cout << certificate << std::endl;
    }

    else {
        Vector resultVector = findResultVector(basePositions, b, numVariables);
        Vector certificate = findUnlimitedCertificate(basePositions, A, col, numVariables);

        std::cout << "ilimitada" << std::endl;
        std::cout << resultVector << std::endl;
        std::cout << certificate << std::endl;
        exit(0);
    }

    return 0;
}