#ifndef FIELD_H 
#define FIELD_H 

#include <string>
#include <serialization.h>

enum class FieldOptions : char {
    Nullable = 0x1, 
    Test = 1 << 1,
};

inline FieldOptions operator|(FieldOptions a, FieldOptions b)
{
    return (FieldOptions)((char)a | (char)b);
}

enum class FieldType {
    Text = 0x1,
};

class FieldHeader : Serializable {
public:
    FieldHeader(const FieldOptions& options_, const FieldType& type_, const std::string& name_);
    FieldHeader();
    ~FieldHeader() = default;

    std::string GetName() const;
    FieldOptions GetOptions() const;
    FieldType GetType() const;

    void Serialize(std::ostream& os) const override;
    void Deserialize(std::istream& is) override;
private:
    FieldOptions options;
    FieldType type;
    std::string name;
};

#endif // FIELD_H

