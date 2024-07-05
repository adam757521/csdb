#pragma once

#include <string>
#include "serialization.h"

enum class FieldOptions : char
{
    Nullable = 0x1,
    List = 1 << 1,
};

inline FieldOptions operator|(FieldOptions a, FieldOptions b)
{
    return (FieldOptions)((char)a | (char)b);
}

enum class FieldType : char
{
    Text,
    Number, // VarInt
};

// NOTE: bitfield structs https://en.wikipedia.org/wiki/Bit_field
struct FieldFlag
{
    FieldType type : 3;
    FieldOptions options : 5;

    FieldFlag(const FieldType &type, const FieldOptions &options);
    FieldFlag() = default;

    friend std::ostream &operator<<(std::ostream &ostream, const FieldFlag &flag);
    friend std::istream &operator>>(std::istream &istream, FieldFlag &flag);
};

class FieldHeader
{
public:
    FieldHeader(const FieldOptions &options_, const FieldType &type_, const std::string &name_);
    FieldHeader();
    ~FieldHeader() = default;

    std::string GetName() const;
    FieldOptions GetOptions() const;
    FieldType GetType() const;

    friend std::ostream &operator<<(std::ostream &ostream, const FieldHeader &header);
    friend std::istream &operator>>(std::istream &istream, FieldHeader &header);

private:
    FieldFlag flag;
    std::string name;
};