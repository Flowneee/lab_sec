#include <string>
#include <fstream>
#include <vector>

#include "user.hpp"

class PasswdManager
{
public:
    PasswdManager() {};
    explicit PasswdManager(std::string passwd_file_path);
    virtual ~PasswdManager();

    std::vector<User> get_users();
    bool get_user_by_login(std::string login, User* user);
    void write(std::string passwd_file_path);
    void write() { this->write(this->m_passwd_file_path); }
    void read_from_file(std::string passwd_file_path);
    bool is_correct_user(std::string login, std::string passwd);
private:
    std::fstream m_passwd_file;
    std::string m_passwd_file_path;

    std::vector<User> users; // массив пользователей

    void create_default_file();
};
