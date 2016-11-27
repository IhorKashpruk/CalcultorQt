#include "operation.h"

OperationList::OperationList(){}

OperationList::OperationList(std::vector<Number> &numbers_, std::string &operations_)
    : numbers(std::move(numbers_)), operations(std::move(operations_)){}

std::string OperationList::getOperations() const { return operations; }

std::vector<Number> OperationList::getNumbers() const { return numbers; }

void OperationList::addOperation(const char s, Number &left, Number &right){
    if(operations_on_the_priority.find(s) == std::string::npos){
        throw my::exception(my::TYPE_OF_ERROR::CRITICAL,"class OperationList::addOperation(...)", "Operation '"+ std::string(1,s) + "' not find!");
        return;
    }
    numbers.push_back(std::move(left));
    numbers.push_back(std::move(right));
    operations.push_back(s);
}
void OperationList::addOperation(const char s, Number &&left, Number &&right){
    if(operations_on_the_priority.find(s) == std::string::npos){
        throw my::exception(my::TYPE_OF_ERROR::CRITICAL,"class OperationList::addOperation(...)", "Operation '"+ std::string(1,s) + "' not find!");
        return;
    }
    numbers.push_back(left);
    numbers.push_back(right);
    operations.push_back(s);
}

void OperationList::addOperation(const char s){ if(operations_on_the_priority.find(s) != std::string::npos) operations.push_back(s); }

void OperationList::addNumber(const Number &number) { numbers.push_back(std::move(number)); }

bool OperationList::validate() { return (numbers.size() == (operations.size()+1));}

Number OperationList::calculate(){
    if(!validate())
        throw my::exception(my::TYPE_OF_ERROR::CRITICAL, "class OperationList::calculate()", "validete() return false!");

    size_t pos = std::string::npos;
    for(auto& it: operations_on_the_priority){
        while((pos = operations.find(it)) != std::string::npos){
            numbers[pos] = do_operation(it, numbers[pos],numbers[pos+1]);
            numbers.erase(numbers.begin()+pos+1);
            operations.erase(pos,1);
        }
    }
    return numbers[0];
}

std::string OperationList::buildExpression() const
{
    std::string str = "[";
    size_t pos = 0;
    for(auto& it: numbers){
        str += it.getValueStr();
        if(pos < operations.size())
            str.push_back(operations[pos]);
        pos++;
    }
    str += "]";
    return str;
}


Number OperationList::do_operation(const char s, const Number &left, const Number &right)
{
    Number n;
    switch (s) {
    case '+':
        return left+right;
    case '-':
        return left-right;
    case '*':
        return left*right;
    case '/':
        if(right == 0.0)
            throw my::exception(my::TYPE_OF_ERROR::CALCULATE, "class OperationList::do_operation(...)", "Divide by zero!");
        return left/right;
    case '#':
        if(right.getValue() < 0.0)
            throw my::exception(my::TYPE_OF_ERROR::CALCULATE, "class OperationList::do_operation(...)", "Can't the square root of a negative number[sqrt("+ right.getValueStr() +")]!");
           return sqrt(right);
    case '^':
        n = pow(left, right);
        break;
    case 'c':
        n = cos(right); break;
    case 's':
        n = sin(right); break;
    case 't':
        n = tan(right); break;
    case '!':
        n = std::tgamma(left.getValue()+1.0); break;
    case 'l':
        n = log(right.getValue()); break;
    case 'j':
        n = log10(right.getValue()); break;
    default:
        throw my::exception(my::TYPE_OF_ERROR::CRITICAL, "class OperationList::do_operation(...)", "Symbol not find!");
    }
    if(std::isinf(n.getValue()) || std::isnan(n.getValue()))
        throw my::exception(my::TYPE_OF_ERROR::CALCULATE, "class OperationList::do_operation(...)", "Overflow error!");
    return n;
}
