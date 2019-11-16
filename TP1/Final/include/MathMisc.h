#ifndef MATH_MISC_H
#define MATH_MISC_H

#include <cmath>
#include "Vector.h"

// Função auxiliar para fixar a precisão das operações usando 5 casas decimais
void fixPrecision5(float& num);

// Função auxiliar para fixar a precisão das operações usando 5 casas decimais (polimorfismo)
void fixPrecision5(Vector& v);

#endif