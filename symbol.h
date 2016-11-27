//
// Created by igor on 11/11/16.
//

#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "exception.h"

const std::map<std::string, std::string> commandMap{
        {"sqrt",    "#"},
        {"pow",     "^"},
        {"cos",     "c"},
        {"sin",     "s"},
        {"tg",      "t"},
        {"!",       "!"},
        {"ln",      "l"},
        {"log",     "j"}
};
const std::string weekSymbols       = "+-";
const std::string strongSymbols     = "*/";
const std::string commandSymbols    = "^#!cstlj";

enum class SYMBOL_TYPE{
    NUMBER,
    DOT,
    LEFT_BRACE,
    RIGHT_BRACE,
    WEEK_SYMBOL,
    STRONG_SYMBOL,
    COMMAND,
    UNKNOW
};

class Symbol;
typedef SYMBOL_TYPE S_T;
typedef std::vector<std::shared_ptr<Symbol>> vec_sh_ptr;

/*                  Abstract class Symbol                   */
class Symbol
{
protected:
    SYMBOL_TYPE type;
    std::string text;
public:
    std::string getText() const;
    SYMBOL_TYPE getType() const;
    Symbol(SYMBOL_TYPE type, const std::string &text);
    virtual vec_sh_ptr add_operation(const Symbol& s) const = 0;
};

/*                  Classes implements base class Symbol    */
class number_symbol : public Symbol
{
public:
    number_symbol(const std::string& text);
    vec_sh_ptr add_operation(const Symbol &s) const override;
};

class dot_symbol : public Symbol
{
public:
    dot_symbol();
    vec_sh_ptr add_operation(const Symbol &s) const override;
};

class left_brace_symbol : public Symbol
{
public:
    left_brace_symbol();
    vec_sh_ptr add_operation(const Symbol &s) const override;
};

class right_brace_symbol : public Symbol
{
public:
    right_brace_symbol();
    vec_sh_ptr add_operation(const Symbol &s) const override;
};

class week_symbol : public Symbol
{
public:
    week_symbol(const std::string &text);
    vec_sh_ptr add_operation(const Symbol &s) const override;
};

class strong_symbol : public Symbol
{
public:
    strong_symbol(const std::string &text);
    vec_sh_ptr add_operation(const Symbol &s) const override;
};

class command_symbol : public Symbol
{
public:
    command_symbol(const std::string &text);
    vec_sh_ptr add_operation(const Symbol &s) const override;
};

class unknow_symbol : public Symbol
{
public:
    unknow_symbol(const std::string &text);
    vec_sh_ptr add_operation(const Symbol &s) const override;
};


/*                  Functions for create new objects     */
inline Symbol* make_symbol(const SYMBOL_TYPE& type, const std::string& text = ""){
    switch(type){
        case S_T::NUMBER:       return new number_symbol(text);
        case S_T::DOT:          return new dot_symbol();
        case S_T::LEFT_BRACE:   return new left_brace_symbol();
        case S_T::RIGHT_BRACE:  return new right_brace_symbol();
        case S_T::WEEK_SYMBOL:  return new week_symbol(text);
        case S_T::STRONG_SYMBOL:return new strong_symbol(text);
        case S_T::COMMAND:      return new command_symbol(text);
        case S_T::UNKNOW:       return new unknow_symbol(text);
    }
    return nullptr;
}


inline Symbol* make_symbol(const Symbol& symbol){
    return make_symbol(symbol.getType(), symbol.getText());
}

inline Symbol* make_symbol(const char s){
    if(isdigit(s))                  return make_symbol(S_T::NUMBER, std::string(1,s));
    if(s == '.')                    return make_symbol(S_T::DOT);
    if(s == '(')                    return make_symbol(S_T::LEFT_BRACE);
    if(s == ')')                    return make_symbol(S_T::RIGHT_BRACE);
    if(weekSymbols.find(s) != std::string::npos)   return make_symbol(S_T::WEEK_SYMBOL, std::string(1,s));
    if(strongSymbols.find(s) != std::string::npos) return make_symbol(S_T::STRONG_SYMBOL, std::string(1,s));
    if(commandSymbols.find(s) != std::string::npos)return make_symbol(S_T::COMMAND, std::string(1,s));
    return make_symbol(S_T::UNKNOW, std::string(1,s));
}

#endif //SYMBOL_H
