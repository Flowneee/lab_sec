#include <experimental/filesystem>

#include "passwdmanager.hpp"
#include "functions.hpp"

PasswdManager::PasswdManager(std::wstring passwd_file_path)
{
    if (!std::experimental::filesystem::exists(wstring_to_string(passwd_file_path))) {
	this->create_default_file();
    }
    std::wfstream passwd(wstring_to_string(passwd_file_path),
                        std::wfstream::in | std::wfstream::out);
    this->m_passwd_file_path = passwd_file_path;
    std::wstring tmp;
    while(passwd >> tmp) {
        this->users.push_back(User(tmp));
    }
    passwd.close();
}

PasswdManager::~PasswdManager()
{
}

void PasswdManager::read_from_file(std::wstring passwd_file_path)
{
    if (!std::experimental::filesystem::exists(wstring_to_string(passwd_file_path))) {
	this->create_default_file();
    }
    std::wfstream passwd(wstring_to_string(passwd_file_path),
                         std::fstream::in | std::wfstream::out);
    this->m_passwd_file_path = passwd_file_path;
    std::wstring tmp;
    while(passwd >> tmp) {
        this->users.push_back(User(tmp));
    }
    passwd.close();
}

std::vector<User>* PasswdManager::get_users()
{
    return &(this->users);
}

bool PasswdManager::is_correct_user(std::wstring login, std::wstring passwd)
{
    for (auto i: this->users) {
        if (i.login == login && i.passwd == passwd) {
            return true;
        }
    }
    return false;
}

User* PasswdManager::get_user_by_login(std::wstring login)
{
    for (auto &i: this->users) {
        if (i.login == login) {
            return &i;
        }
    }
    return nullptr;
}

void PasswdManager::create_default_file()
{
    std::wofstream passwd("passwd");
    if (!std::experimental::filesystem::exists("passwd")) {
        throw std::runtime_error("Невозможно создать passwd");
    }
    passwd << "ADMIN:1:0:0:1:admin555" << std::endl;
    passwd << "bashlykova:0:0:0:1:basha89" << std::endl;
    passwd.close();
}

void PasswdManager::write(std::wstring passwd_file_path)
{

    std::wofstream passwd(wstring_to_string(passwd_file_path),
                          std::wofstream::trunc);
    for (auto i: this->users) {
        passwd << i.str(sys) << std::endl;
    }
    passwd.close();
}

User* PasswdManager::add_user(std::wstring login)
{
    if (this->get_user_by_login(login) == nullptr) {
        User user(login, false, false, true, true, L"");
        this->users.push_back(user);
        return &(this->users.back());
    }
    return nullptr;
}
