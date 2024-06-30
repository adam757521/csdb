#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace Exception
{
    class InvalidStringLengthException : public std::exception {
    public:
        InvalidStringLengthException() {}

        char* what()
        {
            return "Invalid string length";
        }
    };
}

#endif