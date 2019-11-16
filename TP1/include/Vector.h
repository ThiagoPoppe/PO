#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>

class Vector {
public:
    std::vector<double> elements;

public:
    // Construtor e destrutor
    Vector();
    Vector(unsigned int n);
    ~Vector();

    // Método para pegar o tamanho do Vector
    unsigned int GetSize() const;

    /** Sobrecarga de operadores **/
    // Indexação
    double& operator[](unsigned int i);

    // Stream
    friend std::ostream& operator<<(std::ostream& os, Vector& v);

    // Produto interno entre dois Vectors
    double operator*(const Vector& v);

    // Soma de dois Vectors
    Vector operator+(const Vector& v);
    Vector& operator+=(const Vector& v);

    // Multiplicação de um Vector por um escalar
    Vector operator*(double val);
    Vector& operator*=(double val);
};

#endif