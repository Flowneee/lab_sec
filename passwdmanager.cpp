#include <experimental/filesystem>
#include <locale>
#include <codecvt>
#include <cstdio>
#include <wx/msgdlg.h>
#include <exception>

#include "passwdmanager.hpp"
#include "functions.hpp"
#include "crypto.hpp"


const std::locale utf8_locale = std::locale(std::locale(),
                                            new std::codecvt_utf8<wchar_t>());

PasswdManager::PasswdManager(std::wstring passwd_file_path)
{
    this->read_from_file(passwd_file_path);
}

PasswdManager::~PasswdManager()
{
}

void PasswdManager::set_default(std::wstring passwd_file_path)
{
    this->passwd_file_path = passwd_file_path;
    this->users.push_back(User(L"ADMIN:1:0:1:1:"));
}

bool PasswdManager::read_from_file(std::wstring passwd_file_path)
{
    /*this->passwd_file_path = passwd_file_path;
    // чтение файла с пользователями
    std::ifstream encrypted_passwd(wstring_to_string(passwd_file_path),
                                   std::ios::binary | std::ios::ate);
    std::streamsize size = encrypted_passwd.tellg();
    encrypted_passwd.seekg(0, std::ios::beg);
    unsigned char encrypted_buffer[size];
    encrypted_passwd.read(reinterpret_cast<char*>(encrypted_buffer), size);
    encrypted_passwd.close();

    // расшифровка файла и запись его во временный
    unsigned char *decrypted_buffer;
    en_de_crypt(false, encrypted_buffer, &decrypted_buffer, size,
                this->password_hash, IVEC);

    std::ofstream tmp(TMP_PATH, std::ios::binary);
    tmp.write(reinterpret_cast<const char*>(decrypted_buffer), size);
    tmp.close();

    // чтение пользователей из расшифрованного файла
    std::wfstream decrypted_passwd(TMP_PATH,
                                   std::fstream::in | std::wfstream::out);
    decrypted_passwd.imbue(utf8_locale);
    bool ret =  this->read_from_stream(decrypted_passwd);
    decrypted_passwd.close();
    std::experimental::filesystem::remove(TMP_PATH);
    return ret;*/
    this->passwd_file_path = passwd_file_path;
    FILE* fin = fopen(wstring_to_string(this->passwd_file_path).c_str(), "rb");
    FILE* fout = fopen(TMP_PATH, "wb");
    en_de_crypt_files(false, fin, fout, this->password_hash, IVEC);
    fclose(fin);
    fclose(fout);

    std::wfstream decrypted_passwd(TMP_PATH,
                                   std::fstream::in | std::wfstream::out);
    decrypted_passwd.imbue(utf8_locale);
    bool ret =  this->read_from_stream(decrypted_passwd);
    decrypted_passwd.close();
    std::experimental::filesystem::remove(TMP_PATH);
    return ret;

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
    // запись текущей базы во временный файл
    /*std::wofstream out_passwd(TMP_PATH, std::wofstream::trunc);
    out_passwd.imbue(utf8_locale);
    for (auto i: this->users) {
        out_passwd << i.str(sys) << std::endl;
    }
    out_passwd.close();

    // чтение базы в бинарном виде
    std::ifstream decrypted_passwd(TMP_PATH,
                                   std::ios::binary | std::ios::ate);
    std::streamsize size = decrypted_passwd.tellg();
    decrypted_passwd.seekg(0, std::ios::beg);
    unsigned char decrypted_buffer[size];
    decrypted_passwd.read(reinterpret_cast<char*>(decrypted_buffer), size);
    decrypted_passwd.close();

    unsigned char *encrypted_buffer;
    en_de_crypt(true, decrypted_buffer, &encrypted_buffer, size,
                this->password_hash, IVEC);

    // запись зашифрованного файла в постоянный
    std::ofstream encrypted_passwd(wstring_to_string(passwd_file_path),
                                   std::ios::binary | std::ios::trunc);
    encrypted_passwd.write(reinterpret_cast<char*>(encrypted_buffer), size);
    encrypted_passwd.close();
    std::experimental::filesystem::remove(TMP_PATH);*/

    std::wofstream out_passwd(TMP_PATH, std::wofstream::trunc);
    out_passwd.imbue(utf8_locale);
    for (auto i: this->users) {
        out_passwd << i.str(sys) << std::endl;
    }
    out_passwd.close();

    FILE* fin = fopen(TMP_PATH, "rb");
    FILE* fout = fopen(wstring_to_string(this->passwd_file_path).c_str(), "wb");
    en_de_crypt_files(true, fin, fout, this->password_hash, IVEC);
    fclose(fin);
    fclose(fout);
    std::experimental::filesystem::remove(TMP_PATH);
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

bool PasswdManager::read_from_stream(std::wistream& input)
{
    std::wstring tmp;
    try {  // затычка чтобы не падало, если некорректный символ при чтении
        input >> tmp;
    }
    catch (std::exception& e) {}
    if (!input.good() || tmp.size() < 5 || tmp.substr(0, 5) != L"ADMIN") {
        return false;
    }
    input.seekg(0);
    while(input >> tmp) {
        this->users.push_back(User(tmp));
    }
    return true;
}

void PasswdManager::set_password_hash(unsigned char (&in)[32])
{
    for (int i = 0; i < 32; i++) {
        this->password_hash[i] = in[i];
    }
}
