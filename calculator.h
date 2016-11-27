#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "number.h"
#include "validator.h"
#include "expression.h"

class Calculator
{
public:
    Calculator();
    Number calculate(const std::string& str);
};

#endif // CALCULATOR_H
