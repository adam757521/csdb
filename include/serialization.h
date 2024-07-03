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

// used from https://lemire.me/blog/2022/11/25/making-all-your-integers-positive-with-zigzag-encoding/

// NOTE: Enstricted to signed types.
template <typename T, typename = typename std::enable_if<std::is_signed<T>::value>::type>
charvec_t encode_zigzag(T value)
{
    using unsigned_t = typename std::make_unsigned<T>::type;
    unsigned_t abs = (2 * value) ^ (value >> (sizeof(T) * 8 - 1));
    return encode_pbve<unsigned_t>(abs);
}

// NOTE: Enstricted to signed types.
template <typename T, typename = typename std::enable_if<std::is_signed<T>::value>::type>
T decode_zigzag(const charvec_t &b)
{
    using unsigned_t = typename std::make_unsigned<T>::type;
    unsigned_t n = decode_pbve<unsigned_t>(b);
    return (n >> 1) ^ (-(n & 1));
}
