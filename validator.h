//
// Created by igor on 12/11/16.
//

#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "symbol.h"
#include "exception.h"
#include <algorithm>
#include <vector>
#include <memory>

class Validator {
public:
    Validator(const std::string &text);
    bool validate();
    const vec_sh_ptr &getSymbols() const;
    std::string getSimplifyText() const;

    static vec_sh_ptr simplifyOnlyNumbers(const std::string& str);
private:
    std::string text;
    vec_sh_ptr symbols;
};


#endif //VALIDATOR_H
