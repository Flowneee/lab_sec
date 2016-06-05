#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

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

std::string exec(const char* cmd);
std::string get_total_system_memory();
std::string get_dislay_vertical_size();
std::string get_keyboard_model();
std::string get_file_or_directory_hard_drive_label();
std::string get_whoami();

#endif
