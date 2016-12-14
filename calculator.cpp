#include "calculator.h"

Calculator::Calculator() {}

Number Calculator::calculate(const std::string &str)
{
    Validator validator(str);
    validator.validate();
    return Expression(nullptr, validator.getSimplifyText()).calculate();
}

{
    Validator validator("1+2/23.1-(110+22*1(-12-2^2))-1");
    if(validator.validate()){
        // do something
    }
}
