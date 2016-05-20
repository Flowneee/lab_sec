#include <iostream>
#include <vector>
#include <sstream>
#include <locale>
#include <string>

#include "functions.hpp"
#include "validator.hpp"

int main (int argc, char *argv[])
{
    std::wstring password = L"AФ12,.";
    std::wcout << latin(password) << std::endl << cyrillic(password) << std::endl
               << number(password) << std::endl << punctuation(password) <<std::endl;
    return 0;
}
