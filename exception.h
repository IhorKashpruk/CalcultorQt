#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
#include <string>

namespace my {

enum class TYPE_OF_ERROR{
    VERIFICATION,
    CALCULATE,
    CRITICAL
};

class exception : public std::runtime_error
{
private:
    const TYPE_OF_ERROR type;
    const std::string error_class;
public:
    explicit exception(const TYPE_OF_ERROR& type_, const std::string& error_class_, const std::string& message_);
    TYPE_OF_ERROR getType() const;
    std::string getError_class() const;
};
}

#endif // EXCEPTION_H
