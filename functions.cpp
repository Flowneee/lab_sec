/**
 * lab_sec
 * Copyright (C) 2016  Kononov Andrey <flowneee@protonmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <memory>
#include <experimental/filesystem>

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

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}


std::string get_total_system_memory()
{
    std::string result = exec("grep MemTotal /proc/meminfo | awk -F'[ ]+' '{print $2}'");
    return result.substr(0, result.size() - 1);
}

std::string get_dislay_vertical_size()
{
    std::string result = exec("read RES_Y <<<$(xdpyinfo | awk -F'[ x]+' '/dimensions:/{print $4}'); echo $RES_Y");
    return result.substr(0, result.size() - 1);
}

std::string get_keyboard_model()
{
    std::string result = exec("setxkbmap -query | grep model | awk -F'[ ]+' '{print $2}'");
    return result.substr(0, result.size() - 1);
}

std::string get_file_or_directory_hard_drive_label()
{
    std::string path = std::experimental::filesystem::current_path();
    std::string command = "df --output=source \"";
    command += path;
    command += "\" | grep /";
    std::string result = exec(command.c_str());
    return result.substr(0, result.size() - 1);
}

std::string get_whoami()
{
    std::string result = exec("whoami");
    return result.substr(0, result.size() - 1);
}
