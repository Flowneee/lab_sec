#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <string>
#include <locale>
#include <codecvt>
#include <map>
#include <array>
#include <vector>
#include <sstream>


extern std::map<std::string, std::string[2]> bool_to_string_translates;

std::wstring string_to_wstring(const std::string& str);
std::string wstring_to_string(const std::wstring& wstr);

std::string bool_to_string(bool in, std::string locale = "en");
std::wstring bool_to_wstring(bool in, std::string locale = "en");

std::vector<std::string> split(const std::string &str, char delimiter);
std::vector<std::wstring> wsplit(const std::wstring &str, wchar_t delimiter);


#endif
