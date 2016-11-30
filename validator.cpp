//
// Created by igor on 12/11/16.
//

#include <iostream>
#include "validator.h"

Validator::Validator(const std::string &text) : text(text) {}

bool Validator::validate() {
    if(text.empty()) return false;
    std::string resoult_str(text);
    for(auto& pair: commandMap){
        size_t pos = 0;
            while((pos = resoult_str.find(pair.first, pos)) != std::string::npos){
                resoult_str.replace(pos, pair.first.size(), pair.second);
                pos += pair.second.size();
        }
    };
    if(weekSymbols.find(resoult_str[0]) != std::string::npos)
        resoult_str.insert(resoult_str.begin(), '0');
    std::shared_ptr<Symbol> firstSymbol(make_symbol(resoult_str[0]));
    std::shared_ptr<Symbol> lastSymbol(make_symbol(*resoult_str.rbegin()));

    if(firstSymbol->getType() != S_T::NUMBER && firstSymbol->getType() != S_T::WEEK_SYMBOL
       && firstSymbol->getType() != S_T::LEFT_BRACE && (firstSymbol->getType() != S_T::COMMAND || firstSymbol->getText() == "^" || firstSymbol->getText() == "!"))
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class Validator::validate(...)", "The first symbol can't be '" + firstSymbol->getText() + "'!");

    if(lastSymbol->getType() != S_T::NUMBER && lastSymbol->getType() != S_T::RIGHT_BRACE && lastSymbol->getText() != "!")
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION,"class Validator::validate(...)","The last symbol can't be '" + lastSymbol->getText() + "'!");

    if(std::count(resoult_str.begin(), resoult_str.end(), '(') != std::count(resoult_str.begin(), resoult_str.end(), ')'))
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION,"class Validator::validate(...)", "The count of the brace not equal!");

    symbols.push_back(firstSymbol);
    for(unsigned int i = 1; i < resoult_str.size(); i++){
        lastSymbol.reset(make_symbol(resoult_str[i]));
        vec_sh_ptr localV = (*symbols.rbegin())->add_operation(*lastSymbol);
        symbols.erase(symbols.end()-1);
        for(std::shared_ptr<Symbol>& it: localV)
            symbols.push_back(it);
    }
    for(unsigned int j = 0; j < symbols.size(); j++){
        if(symbols[j]->getType() == S_T::COMMAND && symbols[j]->getText() != "^" && symbols[j]->getText() != "!"){
            symbols.insert(symbols.begin()+j,std::make_shared<number_symbol>("0"));
            j++;
        }else
        if(symbols[j]->getType() == S_T::COMMAND && symbols[j]->getText() == "!"){
            symbols.insert(symbols.begin()+j+1,std::make_shared<number_symbol>("0"));
            j++;
        }
    }

    return true;
}

const vec_sh_ptr &Validator::getSymbols() const {
    return symbols;
}

std::string Validator::getSimplifyText() const
{
    std::string str;
    for(auto& it: symbols)
        str += it->getText();
    return str;
}


vec_sh_ptr Validator::simplifyOnlyNumbers(const std::string& str){
    if(str.empty()) throw my::exception(my::TYPE_OF_ERROR::CRITICAL, "class Validator::simplifyOnlyNumbers(...)",  "String is empty!");

    vec_sh_ptr v;
    std::shared_ptr<Symbol> lastSymbol;
    v.push_back(std::shared_ptr<Symbol>(make_symbol(str[0])));
    for(unsigned int i = 1; i < str.size(); i++){
        lastSymbol.reset(make_symbol(str[i]));
        if(lastSymbol->getType() != SYMBOL_TYPE::NUMBER && lastSymbol->getType() != SYMBOL_TYPE::DOT){
            v.push_back(lastSymbol);
            continue;
        }
        if((*v.rbegin())->getType() == SYMBOL_TYPE::NUMBER){
            vec_sh_ptr localV = (*v.rbegin())->add_operation(*lastSymbol);
            v.erase(v.end()-1);
            for(std::shared_ptr<Symbol>& it: localV)
                v.push_back(it);
        }else
            v.push_back(lastSymbol);
    }
    return v;
}
