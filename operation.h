#ifndef OPERATION_H
#define OPERATION_H
#include <cmath>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include "number.h"
#include "exception.h"

const std::string operations_on_the_priority = "!#^cstlj*/-+";

class OperationList
{
private:
    std::vector<Number> numbers;
    std::string operations;
    Number do_operation(const char s, const Number& left, const Number& right);

public:
    OperationList();
    OperationList(std::vector<Number>& numbers_, std::string& operations_);

    std::string getOperations() const;
    std::vector<Number> getNumbers() const;
    void addOperation(const char s, Number& left, Number& right);
    void addOperation(const char s, Number&& left, Number&& right);
    void addOperation(const char s);
    void addNumber(const Number& number);
    bool validate();
    Number calculate();
    std::string buildExpression() const;
};

#endif // OPERATION_H
