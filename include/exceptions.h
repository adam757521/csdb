#pragma once

#include <exception>
#include <string>

namespace Exception
{
    // expection when the string has a length bigger than UINT8_MAX
    class InvalidStringLength : public std::exception
    {
        const char *what() const throw()
        {
            return "invalid string length";
        }
    };
}