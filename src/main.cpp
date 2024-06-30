#include <cstdint>
#include <serialization.h>
#include <field.h>
#include <iostream>
#include <fstream>

int main()
{
    FieldHeader header(FieldOptions::Nullable | FieldOptions::Test, FieldType::Text, "Username");
    std::ofstream file("csdb.db");

    if (!file.is_open())
    {
        std::cerr << "cannot open file." << std::endl;
        return 1;
    }
    header.Serialize(file);
    file.close(); // to write changes
    // std::ios_base::app | std::ios_base::in | std::ios_base::out

    std::fstream input("csdb.db");
    FieldHeader new_header;
    new_header.Deserialize(input);
    input.close();

    std::cout << new_header.GetName() << " type values: " << (int)new_header.GetType() << " " << (int)new_header.GetOptions() << std::endl;

    return 0;
}
