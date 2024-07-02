#include "field.h"
#include <exceptions.h>
#include <iostream>

FieldFlag::FieldFlag(const FieldType& type, const FieldOptions& options) : type(type), options(options) {}

FieldHeader::FieldHeader(const FieldOptions &options_, const FieldType &type_, const std::string &name_) : flag(FieldFlag(type_, options_)), name(name_)
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
    return this->flag.options;
}

FieldType FieldHeader::GetType() const
{
    return this->flag.type;
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
    out << header.flag;

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
    header.flag.type = (FieldType)type_;
    header.flag.options = (FieldOptions)options_;

    return in;
}


std::ostream& operator<<(std::ostream& out, const FieldFlag& flag) {
    out << *(char*) &flag;
    return out;
}

std::istream& operator>>(std::istream& in, FieldFlag& flag) {
    union {
        FieldFlag out_flag;
        char byte;
    };
    in >> byte;
    flag = out_flag;
    return in;
}
