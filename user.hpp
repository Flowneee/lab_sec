#ifndef __USER_H__
#define __USER_H__

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
	 int validatorData, std::wstring password)
	: login(login), isAdmin(isAdmin), isBlocked(isBlocked), isNew(isNew),
          validatorData(validatorData), password(password) {};
    explicit User(std::wstring str);
    virtual ~User() {};

    std::wstring str(UserStrType type = simple);

    ChangePasswordStatus change_password(std::wstring old_password,
                                         std::wstring new_password,
                                         std::wstring new_password2);
    bool compare_password(std::wstring password);
private:
    bool validate_password(std::wstring password);
    std::wstring password;
};

#endif
