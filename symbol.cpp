//
// Created by igor on 11/11/16.
//

#include "symbol.h"

std::string Symbol::getText() const { return text; }
SYMBOL_TYPE Symbol::getType() const { return type; }
Symbol::Symbol(SYMBOL_TYPE type, const std::string &text) : type(type), text(text) {}


/*                  Class number_symbol                 */
number_symbol::number_symbol(const std::string& text) : Symbol(SYMBOL_TYPE::NUMBER, text) {}
vec_sh_ptr number_symbol::add_operation(const Symbol &s) const {
    if(s.getType() == S_T::LEFT_BRACE
       || s.getType() == S_T::UNKNOW || (s.getType() == S_T::COMMAND && s.getText() != "!" && s.getText() != "^"))
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class number_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
    if(s.getType() == S_T::DOT && text.find('.') != std::string::npos)
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class number_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
    if(s.getType() == S_T::DOT || s.getType() == S_T::NUMBER)
        return vec_sh_ptr{std::make_shared<number_symbol>(text+s.getText())};
    if(*text.rbegin() == '.')
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION,"class number_symbol::add_operation(...)", "Can't add '" + s.getText() + "', because last symbol in number is '.'!");
    return vec_sh_ptr{std::make_shared<number_symbol>(text), std::shared_ptr<Symbol>(make_symbol(s))};
}

/*                  Class dot_symbol                    */
dot_symbol::dot_symbol() : Symbol(SYMBOL_TYPE::DOT, ".") {}
vec_sh_ptr dot_symbol::add_operation(const Symbol &s) const {
//    if(s.getType() != S_T::NUMBER)
//        throw std::runtime_error("class dot_symbol::add_operation. Can't add '" + s.getText() + "' to '.'!");
//    return vec_sh_ptr{std::make_shared<dot_symbol>(), std::make_shared<number_symbol>(s)};
    throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class dot_symbol::add_operation(...)", "Can't add '" + s.getText() + "' to '.'!");
}

/*                  Class left_brace_symbol             */
left_brace_symbol::left_brace_symbol() : Symbol(SYMBOL_TYPE::LEFT_BRACE, "(") {}
vec_sh_ptr left_brace_symbol::add_operation(const Symbol &s) const {
    if(s.getType() != S_T::WEEK_SYMBOL && s.getType() != S_T::NUMBER && s.getType() != S_T::LEFT_BRACE
            && s.getText() == "^" && s.getText() == "!")
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class left_brace_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
    if(s.getType() == S_T::WEEK_SYMBOL)
        return vec_sh_ptr{std::make_shared<left_brace_symbol>(), std::make_shared<number_symbol>("0"), std::shared_ptr<Symbol>(make_symbol(s))};
    //  if s.getType() == NUMBER or LEFT_BRACE
    return vec_sh_ptr{std::make_shared<left_brace_symbol>(), std::shared_ptr<Symbol>(make_symbol(s))};
}

/*                  Class right_brace_symbol            */
right_brace_symbol::right_brace_symbol() : Symbol(SYMBOL_TYPE::RIGHT_BRACE, ")") {}
vec_sh_ptr right_brace_symbol::add_operation(const Symbol &s) const {
    if(s.getType() != S_T::STRONG_SYMBOL && s.getType() != S_T::RIGHT_BRACE && s.getType() != S_T::WEEK_SYMBOL && s.getText() != "^" && s.getText() != "!")
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class right_brace_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
    //  if s.getType() == STRONG_SYMBOL or RIGHT_SYMBOL or WEEK_SYMBOL
    return vec_sh_ptr{std::make_shared<right_brace_symbol>(), std::shared_ptr<Symbol>(make_symbol(s))};
}

/*                  Class week_symbol                   */
week_symbol::week_symbol(const std::string &text) : Symbol(SYMBOL_TYPE::WEEK_SYMBOL, text) {}
vec_sh_ptr week_symbol::add_operation(const Symbol &s) const {
    if(s.getType() != S_T::NUMBER && s.getType() != S_T::WEEK_SYMBOL && s.getType() != S_T::LEFT_BRACE)
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class week_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
    if(s.getType() == S_T::WEEK_SYMBOL)
        return vec_sh_ptr{std::make_shared<week_symbol>(text!=s.getText()?"-":"+")};
    return vec_sh_ptr{std::make_shared<week_symbol>(text), std::shared_ptr<Symbol>(make_symbol(s))};
}

/*                  Class strong_symbol                  */
strong_symbol::strong_symbol(const std::string &text) : Symbol(SYMBOL_TYPE::STRONG_SYMBOL, text) {}
vec_sh_ptr strong_symbol::add_operation(const Symbol &s) const {
    if(s.getType() != S_T::NUMBER && s.getType() != S_T::LEFT_BRACE)
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class strong_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
    return vec_sh_ptr{std::make_shared<strong_symbol>(text), std::shared_ptr<Symbol>(make_symbol(s))};
}

/*                  Class command_symbol                */
command_symbol::command_symbol(const std::string &text) : Symbol(SYMBOL_TYPE::COMMAND, text) {}
vec_sh_ptr command_symbol::add_operation(const Symbol &s) const {
    if(this->text == "!"){
        if(s.getType() != S_T::NUMBER && s.getType() != S_T::WEEK_SYMBOL
                && s.getType() != S_T::STRONG_SYMBOL && s.getText() != "!"
                && s.getText()  != "^"){
            throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class command_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
        }
    }else
    if(s.getType() != S_T::NUMBER && s.getType() != S_T::LEFT_BRACE)
        throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class command_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
    return vec_sh_ptr{std::make_shared<command_symbol>(text), std::shared_ptr<Symbol>(make_symbol(s))};
}

/*                  Class unknow_symbol                 */
unknow_symbol::unknow_symbol(const std::string &text) : Symbol(SYMBOL_TYPE::UNKNOW, text) {}
vec_sh_ptr unknow_symbol::add_operation(const Symbol &s) const {
    throw my::exception(my::TYPE_OF_ERROR::VERIFICATION, "class unknow_symbol::add_operation(...)","Can't add '" + s.getText() + "' to '" + text + "'!");
}
