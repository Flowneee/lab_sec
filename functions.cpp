#include "functions.hpp"


std::wstring string_to_wstring(const std::string& str)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    return converter.from_bytes(str);
}

std::string wstring_to_string(const std::wstring& wstr)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    return converter.to_bytes(wstr);
}

std::map<std::string, std::string[2]> bool_to_string_translates =
    {
        {"en", {"true", "false"}},
        {"ru", {"Да", "Нет"}}
    };

std::string bool_to_string(bool in, std::string locale)
{
    return (in ? bool_to_string_translates[locale][0] :
            bool_to_string_translates[locale][1]);
}

std::wstring bool_to_wstring(bool in, std::string locale)
{
    return (in ? string_to_wstring(bool_to_string_translates[locale][0]) :
            string_to_wstring(bool_to_string_translates[locale][1]));
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream sstr(str);
    std::string token;
    while (std::getline(sstr, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::wstring> wsplit(const std::wstring &str, wchar_t delimiter)
{
    std::vector<std::wstring> tokens;
    std::wstringstream sstr(str);
    std::wstring token;
    while (std::getline(sstr, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


std::wstring hash_str(std::wstring in)  // хеширование гаммированием строки 12345678
{
    std::string str = "12345678";
    std::string p = wstring_to_string(in);
    char G = p[2];
    char A = p[0];
    char C = p[1];
    std::wstringstream out;
    out << std::hex;
    for (auto i: str) {
        out << (i ^ G);
        G = (G*A + C) % 256;
    }
    return out.str();
}

#include <openssl/sha.h>
#include <openssl/aes.h>

bool simpleSHA256(void* input, unsigned long length, unsigned char* md)
{
    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, (unsigned char*)input, length))
        return false;

    if(!SHA256_Final(md, &context))
        return false;

    return true;
}
