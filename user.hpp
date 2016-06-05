#ifndef __USER_H__
#define __USER_H__

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
#include <bitset>
#include <functional>
#include <vector>

#include "validator.hpp"


enum UserStrType { simple, detailed, sys };
enum ChangePasswordStatus { OK, NEW_NOT_VALID, OLD_INCORRECT, NEW_DONT_MATCH };

class User
{
public:
    std::wstring login;
    bool isAdmin;
    bool isBlocked;
    bool isNew;
    int validatorData;


    User() {};
    User(std::wstring login, bool isAdmin, bool isBlocked, bool isNew,
	 int validatorData, std::wstring hash)
	: login(login), isAdmin(isAdmin), isBlocked(isBlocked), isNew(isNew),
          validatorData(validatorData), hash(hash) {};
    explicit User(std::wstring str);
    virtual ~User() {};

    std::wstring str(UserStrType type = simple);

    ChangePasswordStatus change_password(std::wstring old_password,
                                         std::wstring new_password,
                                         std::wstring new_password2);
    bool compare_password(std::wstring password);
private:
    bool validate_password(std::wstring password);
    std::wstring hash;
};

#endif
