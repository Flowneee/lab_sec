#include <iostream>
#include <vector>
#include <sstream>
#include <locale>
#include <string>
#include <openssl/sha.h>
#include <openssl/aes.h>

#include "functions.hpp"
#include "validator.hpp"

int main (int argc, char *argv[])
{
    std::wstring password;
    std::wcin >> password;
    unsigned char key[SHA256_DIGEST_LENGTH];
    simpleSHA256(reinterpret_cast<void*>(const_cast<wchar_t*>(password.c_str())),
                 password.length() * sizeof(wchar_t),
                 key);
    for (int i = 0; i < 32; i++) {
        std::cout << (unsigned int)key[i];
    }
    return 0;
}
