#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <ios>

enum UserStrType { simple, detailed, sys };

class User
{
public:
    std::string login;
    bool isAdmin;
    bool isNew;
    bool isBlocked;
    bool isComplexityLimited;
    std::string passwd;


    User() {};
    User(std::string login, bool isAdmin, bool isNew,
	 bool isBlocked, bool isComplexityLimited, std::string passwd)
	: login(login), isAdmin(isAdmin), isNew(isNew),
	  isBlocked(isBlocked), isComplexityLimited(isComplexityLimited),
          passwd(passwd) {};
    explicit User(std::string str);
    virtual ~User() {};

    std::string str(UserStrType type = simple);
private:

};

#endif
