#include "field.h"
#include <exceptions.h>
#include <iostream>

char createFlag(const FieldOptions &options_, const FieldType &type_)
{
    char type_char = (char)type_;
    char options_char = (char)options_;

    char options_lshifted = options_char << 4;
    return options_lshifted | type_char;
}

FieldHeader::FieldHeader(const FieldOptions &options_, const FieldType &type_, const std::string &name_) : options(options_), type(type_), name(name_)
{
    if (name.length() > UINT8_MAX)
    {
        throw Exception::InvalidStringLengthException();
    }
}

FieldHeader::FieldHeader()
{
}

std::string FieldHeader::GetName() const
{
    return name;
}

FieldOptions FieldHeader::GetOptions() const
{
    return options;
}

FieldType FieldHeader::GetType() const
{
    return type;
}


// - 1 byte string size
// - n byte string (field name)
// - 1 byte field flags:
//     - field types
//     - field decorators
std::ostream& operator<<(std::ostream& out, const FieldHeader& header)
{
    out << (char)header.name.length();
    out << header.name;
    out << createFlag(header.options, header.type);

    return out;
}

std::istream& operator>>(std::istream& in, FieldHeader& header)
{
    char length;
    in >> length;

    header.name.resize(length);
    in.read((char *)header.name.data(), length);

    char flags;
    in >> flags;

    char type_ = flags & 0b00001111;
    char options_ = (flags & 0b11110000) >> 4;

    // TODO: handle incorrect parsing
    // TODO: how will we read each option in the field
    header.type = (FieldType)type_;
    header.options = (FieldOptions)options_;

    return in;
}
