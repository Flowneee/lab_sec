#ifndef __PASSWDMANAGER_H__
#define __PASSWDMANAGER_H__

#define PASSWD_PATH CONFDIR"/passwd"
#define TMP_PATH "/tmp/lab_sec_tmp"

static unsigned char IVEC[] = "dsczfegrthy56ju8";

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
