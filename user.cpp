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

#include "user.hpp"
#include "functions.hpp"
#include "crypto.hpp"

std::wstring User::str(UserStrType type)
{
    std::wstringstream sstr;
    switch (type) {
        case detailed:
            sstr << L"Login: " << this->login << L" isAdmin: " << this->isAdmin
                 << L" isBlocked: " << this->isBlocked << L" isNew: " << this->isNew
                 << L" isComplexityLimited: " << this->validatorData
                 << L" Hash: " << this->hash;
            break;
        case simple:
            sstr << this->login << ' ' << this->hash;
            break;
        case sys:
            sstr << this->login << ':' << this->isAdmin << ':' << this->isBlocked
                 << ':' << this->isNew << ':' << this->validatorData
                 << ':' << this->hash;
            break;
    }
    return sstr.str();
}

User::User(std::wstring str)
{
    std::vector<std::wstring> v = wsplit(str, ':');
    this->login               = v[0];
    this->isAdmin             = std::stoi(v[1]);
    this->isBlocked           = std::stoi(v[2]);
    this->isNew               = std::stoi(v[3]);
    this->validatorData       = std::stoi(v[4]);
    if (v.size() < 6) {
        this->hash = L"";
    }
    else {
        this->hash = v[5];
    }
}

bool User::compare_password(std::wstring password)
{
    return hash_str(password) == this->hash;
}

bool User::validate_password(std::wstring password)
{
    return latin(password) && cyrillic(password) && number(password)
        && punctuation(password);
}

ChangePasswordStatus User::change_password(std::wstring old_password,
                                           std::wstring new_password,
                                           std::wstring new_password2)
{
    if (!this->isNew && !this->compare_password(old_password)) {
        return OLD_INCORRECT;
    }
    if (new_password != new_password2) {
        return NEW_DONT_MATCH;
    }
    if (this->validatorData && !this->validate_password(new_password)) {
        return NEW_NOT_VALID;
    }
    this->isNew = false;
    this->hash = hash_str(new_password);
    return OK;
}
