#include "Vector.h"

// Definindo construtor de Vector
Vector::Vector() {}

Vector::Vector(unsigned int n)
: elements(n) {}

// Definindo destrutor de Vector
Vector::~Vector() {}

// Método para pegar o tamanho do Vector
unsigned int Vector::GetSize() const {
    return elements.size();
}

// Definindo a indexação de um Vector
double& Vector::operator[](unsigned int i) {
    return elements[i];
}

// Definindo o stream de um Vector
std::ostream& operator<<(std::ostream& os, Vector& v) {
    for (unsigned int i = 0; i < v.GetSize(); i++)
        os << v[i] << " ";
        
    return os;
}

// Produto interno entre dois Vectors
double Vector::operator*(const Vector& v) {
    double dot = 0.0;
    for (unsigned int i = 0; i < GetSize(); i++)
        dot += elements[i] * v.elements[i];

    return dot;
}

// Soma de dois Vectors
Vector Vector::operator+(const Vector& v) {
    Vector newVector(GetSize());
    for (unsigned int i = 0; i < GetSize(); i++)
        newVector[i] = elements[i] + v.elements[i];

    return newVector;
}

Vector& Vector::operator+=(const Vector& v) {
    for (unsigned int i = 0; i < GetSize(); i++)
        elements[i] += v.elements[i];
    
    return *this;
}

// Multiplicação de um Vector por um escalar
Vector Vector::operator*(double val) {
    Vector newVector(GetSize());
    for (unsigned int i = 0; i < GetSize(); i++)
        newVector[i] = elements[i] * val;

    return newVector;
}

Vector& Vector::operator*=(double val) {
    for (unsigned int i = 0; i < GetSize(); i++)
        elements[i] *= val;
    
    return *this;
}