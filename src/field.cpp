#include <field.h>
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
void FieldHeader::Serialize(std::ostream &out) const
{
    out << (char)name.length();
    out << name;
    out << createFlag(options, type);
}

void FieldHeader::Deserialize(std::istream &is)
{
    char length;
    is >> length;

    name.resize(length);
    is.read((char *)name.data(), length);

    char flags;
    is >> flags;

    char type_ = flags & 0b00001111;
    char options_ = (flags & 0b11110000) >> 4;

    // TODO: handle incorrect parsing
    // TODO: how will we read each option in the field
    type = (FieldType)type_;
    options = (FieldOptions)options_;
}
