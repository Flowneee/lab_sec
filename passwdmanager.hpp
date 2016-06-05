#ifndef __PASSWDMANAGER_H__
#define __PASSWDMANAGER_H__

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

#define PASSWD_PATH CONFDIR"/passwd"
#define VRF_SHA256_PATH CONFDIR"/vrf.sha256"
#define TMP_PATH "/tmp/lab_sec_tmp"

static unsigned char IVEC[] = IV;

#include <string>
#include <fstream>
#include <vector>

#include "user.hpp"

class PasswdManager {
public:
    PasswdManager() {};
    explicit PasswdManager(std::wstring passwd_file_path);
    virtual ~PasswdManager();

    std::vector<User>* get_users();
    User* get_user_by_login(std::wstring login);
    void write(std::wstring passwd_file_path);
    void write() { this->write(this->passwd_file_path); }
    bool read_from_file(std::wstring passwd_file_path);
    bool read_from_stream(std::wistream& input);
    bool is_correct_user(std::wstring login, std::wstring password);
    User* add_user(std::wstring login);
    void set_default(std::wstring passwd_file_path = PASSWD_PATH);
    void set_password_hash(unsigned char (&in)[32]); // пароль для базы пользователей
private:
    std::wstring passwd_file_path;
    unsigned char password_hash[32];
    std::vector<User> users;  // массив пользователей

    void create_default_file();
};

#endif
