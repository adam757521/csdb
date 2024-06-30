#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace Exception
{
    class InvalidStringLengthException : public std::exception
    {
        const char *what() const throw()
        {
            return "C++ Exception";
        }
    };
}

#endif