#include "user.hpp"
#include "functions.hpp"

std::wstring User::str(UserStrType type)
{
    std::wstringstream sstr;
    switch (type) {
        case detailed:
            sstr << L"Login: " << this->login << L" isAdmin: " << this->isAdmin
                 << L" isBlocked: " << this->isBlocked << L" isNew: " << this->isNew
                 << L" isComplexityLimited: " << this->validatorData
                 << L" Password: " << this->password;
            break;
        case simple:
            sstr << this->login << ' ' << this->password;
            break;
        case sys:
            sstr << this->login << ':' << this->isAdmin << ':' << this->isBlocked
                 << ':' << this->isNew << ':' << this->validatorData
                 << ':' << this->password;
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
        this->password = L"";
    }
    else {
        this->password = v[5];
    }
}

bool User::compare_password(std::wstring password)
{
    return password == this->password;
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
    this->password = new_password;
    return OK;
}
