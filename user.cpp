#include "user.hpp"
#include "functions.hpp"


std::wstring User::str(UserStrType type)
{
    std::wstringstream sstr;
    switch (type) {
        case detailed:
            sstr << "Login: " << this->login << " isAdmin: " << this->isAdmin
                 << " isBlocked: " << this->isBlocked << " isNew: " << this->isNew
                 << " isComplexityLimited: " << this->isComplexityLimited
                 << " Password: " << this->passwd;
            break;
        case simple:
            sstr << this->login << ' ' << this->passwd;
            break;
        case sys:
            sstr << this->login << ':' << this->isAdmin << ':' << this->isBlocked
                 << ':' << this->isNew << ':' << this->isComplexityLimited
                 << ':' << this->passwd;
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
    this->isComplexityLimited = std::stoi(v[4]);
    this->passwd              = v[5];
}
