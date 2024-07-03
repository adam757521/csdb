#pragma once

#include <iostream>
#include <vector>

using charvec_t = std::vector<char>;

template <typename T>
charvec_t encode_pbve(T value)
{
    charvec_t encoded;

    do
    {
        char byte = value & 0b01111111;
        value >>= 7;

        if (value != 0)
            byte |= 0b10000000;
        encoded.push_back(byte);
    } while (value != 0);

    return encoded;
}

template <typename T>
T decode_pbve(const charvec_t &encoded)
{
    T value = 0;
    size_t shift = 0;

    for (const auto &byte : encoded)
    {
        value |= (byte & 0x7F) << shift;
        shift += 7;

        if ((byte & 0x80) == 0)
        {
            break;
        }
    }

    return value;
}

// NOTE: Enstricted to signed types. 
template <typename T, typename = typename std::enable_if<std::is_signed<T>::value>::type>
charvec_t encode_zigzag(T value)
{
    typename std::make_unsigned<T>::type abs_v = (value >> 1) ^ (value << (sizeof(T) - 1));
    return encode_pbve(abs_v);
}

// NOTE: Enstricted to signed types. 
template <typename T, typename = typename std::enable_if<std::is_signed<T>::value>::type>
T decode_zigzag(const charvec_t& b)
{
    return decode_pbve(b);
}