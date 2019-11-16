#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>

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

#endif