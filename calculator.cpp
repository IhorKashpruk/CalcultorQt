#include "calculator.h"

Calculator::Calculator() {}

Number Calculator::calculate(const std::string &str)
{
    Validator validator(str);
    validator.validate();
    return Expression(nullptr, validator.getSimplifyText()).calculate();
}
