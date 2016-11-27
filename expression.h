#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <vector>
#include <cctype>
#include "calculator.h"
#include "operation.h"
#include "validator.h"
#include "exception.h"

class Expression;

typedef std::shared_ptr<Expression> expr_ptr;
typedef std::vector<std::pair<size_t, size_t>> vector_pair;

class Expression
{
private:
    Expression *parent;
    std::string text;
    std::vector<expr_ptr> next;

    void optimize();
public:
    Expression(Expression* parent_);
    Expression(Expression *parent_, const std::string& str_);
    void createTree(const std::string&str);
    Expression* addSymbol(char s);
    std::string getStr() const { return text; }
    std::string getFullStr() const;
    Number calculate();
    std::string buildExpression() const;
};

#endif // EXPRESSION_H
