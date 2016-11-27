#ifndef NUMBER_H
#define NUMBER_H

#include <sstream>
#include <iomanip>
#include "exception.h"

class Number{
private:
    double value;

    bool validate(const std::string &number);
public:
    Number();
    Number(const Number& obj);
    Number(const double value_);
    Number(const std::string &number, bool validate_on = true);

    double getValue() const;
    std::string getValueStr() const;

    Number operator+(const Number& obj) const;
    Number operator-(const Number& obj) const;
    Number operator*(const Number& obj) const;
    Number operator/(const Number& obj) const;
    Number& operator =(const Number& obj);
    operator double() const;
    operator std::string() const;
    bool operator ==(double number);
    friend std::ostream &operator<<(std::ostream& os, Number& obj){ os << obj.getValue(); return os;}
    friend std::ostream &operator<<(std::ostream& os, Number&& obj){ os << obj.getValue(); return os;}

};

#endif // NUMBER_H
