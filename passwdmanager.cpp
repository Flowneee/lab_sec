#include <experimental/filesystem>

#include "passwdmanager.hpp"

PasswdManager::PasswdManager(std::string passwd_file_path)
{
    if (!std::experimental::filesystem::exists(passwd_file_path)) {
	this->create_default_file();
    }
    this->m_passwd_file.open(passwd_file_path.c_str(),
                             std::fstream::in | std::fstream::out);
    this->m_passwd_file_path = passwd_file_path;
    std::string tmp;
    while(this->m_passwd_file >> tmp) {
        this->users.push_back(User(tmp));
    }
}

PasswdManager::~PasswdManager()
{
}

void PasswdManager::read_from_file(std::string passwd_file_path)
{
    this->m_passwd_file.open(passwd_file_path.c_str(),
                             std::fstream::in | std::fstream::out);
    this->m_passwd_file_path = passwd_file_path;
    std::string tmp;
    while(this->m_passwd_file >> tmp) {
        this->users.push_back(User(tmp));
    }
}

std::vector<User> PasswdManager::get_users()
{
    return this->users;
}

bool PasswdManager::is_correct_user(std::string login, std::string passwd)
{
    for (auto i: this->users) {
        if (i.login == login && i.passwd == passwd) {
            return true;
        }
    }
    return false;
}

bool PasswdManager::get_user_by_login(std::string login, User* user)
{
    for (auto i: this->users) {
        if (i.login == login) {
            *user = i;
            return true;
        }
    }
    return false;
}

void PasswdManager::create_default_file()
{
    std::ofstream passwd("passwd");
    if (!std::experimental::filesystem::exists("passwd")) {
        throw std::runtime_error("Невозможно создать passwd");
    }
    passwd << "ADMIN:1:0:0:1:admin555" << std::endl;
    passwd << "bashlykova:0:0:0:1:basha89" << std::endl;
    passwd.close();
}

void PasswdManager::write(std::string passwd_file_path)
{
    this->m_passwd_file.seekp(std::ios_base::beg);
    for (auto i: this->users) {
        this->m_passwd_file << i.str(sys);
    }
}
