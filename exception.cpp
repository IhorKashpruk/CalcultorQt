#include "exception.h"

using namespace my;

TYPE_OF_ERROR exception::getType() const { return type; }

std::string exception::getError_class() const { return error_class; }

exception::exception(const TYPE_OF_ERROR &type_, const std::string &error_class_, const std::string &message_)
    : std::runtime_error(message_), type(type_), error_class(error_class_) {}
