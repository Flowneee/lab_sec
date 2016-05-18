#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <ios>

enum UserStrType { simple, detailed, sys };

class User
{
public:
    std::wstring login;
    bool isAdmin;
    bool isBlocked;
    bool isNew;
    bool isComplexityLimited;
    std::wstring passwd;


    User() {};
    User(std::wstring login, bool isAdmin, bool isBlocked, bool isNew,
	 bool isComplexityLimited, std::wstring passwd)
	: login(login), isAdmin(isAdmin), isBlocked(isBlocked), isNew(isNew),
	  isComplexityLimited(isComplexityLimited),
          passwd(passwd) {};
    explicit User(std::wstring str);
    virtual ~User() {};

    std::wstring str(UserStrType type = simple);
private:

};

#endif
