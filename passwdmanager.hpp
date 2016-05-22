#ifndef __PASSWDMANAGER_H__
#define __PASSWDMANAGER_H__

#define PASSWD_PATH CONFDIR"/passwd"

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
    void read_from_file(std::wstring passwd_file_path);
    bool is_correct_user(std::wstring login, std::wstring password);
    User* add_user(std::wstring login);
private:
    std::wstring passwd_file_path;

    std::vector<User> users;  // массив пользователей

    void create_default_file();
};

#endif
