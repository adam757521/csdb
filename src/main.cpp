#include <cstdint>
#include <serialization.h>
#include <field.h>
#include <iostream>
#include <fstream>
#include "asio.hpp"

int main()
{
    // char a = decode_zigzag<char>(encode_zigzag<char>(-5));
    // std::cout << signed(a) << std::endl;
    auto buff = encode_zigzag<int>(INT32_MAX);
    std::cout << decode_zigzag<int>(buff) << std::endl;
    return 0;

    FieldHeader header(FieldOptions::Nullable | FieldOptions::List, FieldType::Text, "Username");
    std::ofstream file("csdb.db");

    if (!file.is_open())
    {
        std::cerr << "cannot open file." << std::endl;
        return 1;
    }
    file << header;
    file.close(); // to write changes
    // std::ios_base::app | std::ios_base::in | std::ios_base::out

    std::fstream input("csdb.db");
    FieldHeader new_header;
    input >> new_header;
    input.close();

    std::cout << new_header.GetName() << " type values: " << (int)new_header.GetType() << " " << (int)new_header.GetOptions() << std::endl;

    return 0;
}
