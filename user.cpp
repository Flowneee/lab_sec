#include "user.hpp"

#include <sstream>
#include <vector>

std::string User::str(UserStrType type)
{
    std::stringstream sstr;
    switch (type) {
        case detailed:
            sstr << "Login: " << this->login << " isAdmin: " << this->isAdmin
                 << " isNew: " << this->isNew << " isBlocked: " << this->isBlocked
                 << " isComplexityLimited: " << this->isComplexityLimited
                 << " Password: " << this->passwd;
            break;
        case simple:
            sstr << this->login << ' ' << this->passwd;
            break;
        case sys:
            sstr << this->login << ':' << this->isAdmin << ':' << this->isNew
                 << ':' << this->isBlocked << ':' << this->isComplexityLimited
                 << ':' << this->passwd;
            break;
    }
    return sstr.str();
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

User::User(std::string str)
{
    std::vector<std::string> v = split(str, ':');
    this->login               = v[0];
    this->isAdmin             = std::stoi(v[1]);
    this->isNew               = std::stoi(v[2]);
    this->isBlocked           = std::stoi(v[3]);
    this->isComplexityLimited = std::stoi(v[4]);
    this->passwd              = v[5];
}
