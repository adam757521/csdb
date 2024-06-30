#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>

class Serializable
{
public:
    virtual void Serialize(std::ostream& os) const = 0;
    virtual void Deserialize(std::istream& is) = 0;
};

using charvec_t = std::vector<char>;

template <typename T>
charvec_t encode_pbve(T value)
{
    charvec_t encoded;

    do 
    {
        char byte = value & 0x7F;
        value >>= 7;

        if (value != 0) byte |= 0x80;
        encoded.push_back(byte);
    } while (value != 0);
    
    return encoded;
}

template <typename T>
T decode_pbve(const charvec_t& encoded)
{
    T value = 0;
    size_t shift = 0;
    
    for (const auto& byte : encoded) 
    {
        value |= (byte & 0x7F) << shift;
        shift += 7;

        if ((byte & 0x80) == 0) {
            break;
        }
    }
    
    return value;
}

#endif SERIALIZABLE_H

