#include <iomanip>

#include "MathMisc.h"
#include "Vector.h"

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