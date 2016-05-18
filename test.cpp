#include <iostream>
#include <vector>
#include <sstream>
#include <locale>

#include "functions.hpp"

int main (int argc, char *argv[])
{
    bool a = true;
    std::wcout << bool_to_wstring(a, "ru") << std::endl;
    std::wcout << bool_to_wstring(!a) << std::endl;
    return 0;
}
