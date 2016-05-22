#include <experimental/filesystem>
#include <locale>
#include <codecvt>

#include "passwdmanager.hpp"
#include "functions.hpp"

const std::locale utf8_locale = std::locale(std::locale(),
                                            new std::codecvt_utf8<wchar_t>());

PasswdManager::PasswdManager(std::wstring passwd_file_path)
{
    this->passwd_file_path = passwd_file_path;
    if (!std::experimental::filesystem::exists(wstring_to_string(passwd_file_path))) {
	this->create_default_file();
    }
    std::wfstream passwd(wstring_to_string(passwd_file_path),
                        std::wfstream::in | std::wfstream::out);
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
    this->passwd_file_path = passwd_file_path;
    if (!std::experimental::filesystem::exists(wstring_to_string(passwd_file_path))) {
	this->create_default_file();
    }
    std::wfstream passwd(wstring_to_string(passwd_file_path),
                         std::fstream::in | std::wfstream::out);
    passwd.imbue(utf8_locale);
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

bool PasswdManager::is_correct_user(std::wstring login, std::wstring password)
{
    for (auto i: this->users) {
        if (i.login == login && i.compare_password(password)) {
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
    std::wofstream passwd(wstring_to_string(this->passwd_file_path));
    passwd.imbue(utf8_locale);
    if (!std::experimental::filesystem::exists(this->passwd_file_path)) {
        throw std::runtime_error("Невозможно создать passwd");
    }
    passwd << "ADMIN:1:0:1:1:" << std::endl;
    passwd.close();
}

void PasswdManager::write(std::wstring passwd_file_path)
{

    std::wofstream passwd(wstring_to_string(passwd_file_path),
                          std::wofstream::trunc);
    passwd.imbue(utf8_locale);
    for (auto i: this->users) {
        passwd << i.str(sys) << std::endl;
        auto status = passwd.rdstate();
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
