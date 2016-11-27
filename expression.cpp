#include "expression.h"

Expression::Expression(Expression *parent_) : parent(parent_), text("") {}

Expression::Expression(Expression *parent_, const std::string &str_) : parent(parent_), text("")
{
    createTree(str_);
}

void Expression::createTree(const std::string &str)
{
    Expression* ptr = this;
    for(size_t i = 0; i < str.size(); i++){
        if(ptr == nullptr)
            throw my::exception(my::TYPE_OF_ERROR::CRITICAL, "class Expression::createTree()", "NullPointerException!");
        ptr = ptr->addSymbol(str[i]);
    }
}

Expression *Expression::addSymbol(char s)
{
    if(s == '('){
        next.push_back(expr_ptr(new Expression(this)));
        text.push_back('&');
        return (*next.rbegin()).get();
    }
    else
        if(s == ')'){
            return parent;
        }
    text.push_back(s);
    return this;
}

std::string Expression::getFullStr() const
{
    std::string resolt_str = text;
    size_t pos;
    size_t n = 0;
    while((pos = resolt_str.find("&")) != std::string::npos){
        if(next.size() > n){
            resolt_str.replace(pos, 1, "("+next[n]->getFullStr()+")");
            n++;
        }
    }
    return resolt_str;
}

Number Expression::calculate()
{
    // If expression empty throw exception
    if(text.empty()) throw my::exception(my::TYPE_OF_ERROR::CRITICAL, "class Expression::calculate(...)","Expression is empty!");
    // Get numbers to vector<Number>
    vec_sh_ptr vecShared = Validator::simplifyOnlyNumbers(text);
    std::vector<Number> numbers;
    for(auto& it: vecShared){
        if(it->getType() == SYMBOL_TYPE::NUMBER)
            numbers.push_back(Number(it->getText()));
    }

    // Remove '&'
    std::string local_str = "";
    for(unsigned int i = 0; i < vecShared.size(); i++)
        if(vecShared[i]->getType() == SYMBOL_TYPE::NUMBER)
            vecShared.erase(vecShared.begin()+i);
    size_t n = 0;
    for(size_t i = 0; i < vecShared.size(); i++){
        if(vecShared[i]->getText() == "&"){
            numbers.insert(numbers.begin()+i, next[n]->calculate());
            vecShared.erase(vecShared.begin()+i); i--; n++;
        }else
            local_str += vecShared[i]->getText();
    }

    // Remove numbers
    return OperationList(numbers, local_str).calculate();
}
