/**
 * lab_sec
 * Copyright (C) 2016  Kononov Andrey <flowneee@protonmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <wx/msgdlg.h>
#include <experimental/filesystem>
#include <algorithm>

#include "gui.hpp"
#include "user.hpp"
#include "functions.hpp"
#include "main.hpp"
#include "crypto.hpp"


MainFrame::MainFrame(wxWindow* parent) : BaseMainFrame(parent)
{
    this->write_on_close = true;
}

MainFrame::~MainFrame()
{
}

void MainFrame::initialize_frame()
{
    int ret;
    if (!this->verify_pc()) {
        wxMessageDialog(NULL, L"Данный исполняемый файл не предназначен для "
                        "запуска на этом компьютере или этим пользователем!",
                        L"Ошибка", wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
        this->write_on_close = false;
        this->Close(false);
        return;
    }
    if (std::experimental::filesystem::file_size(PASSWD_PATH) < 6) {
        this->passwd_manager.set_default();
        ret = EncryptPasswordDialog(static_cast<wxWindow*>(this)).ShowModal();
        if (ret == -1 || ret == wxID_CANCEL) {
            this->write_on_close = false;
            this->Close(false);
            return;
        }
        User* user = this->passwd_manager.get_user_by_login(L"ADMIN");
        ret = ChangePasswordDialog(static_cast<wxWindow*>(this), user).ShowModal();
        if (ret == -1 || ret == wxID_CANCEL) {
            this->write_on_close = false;
            this->Close(false);
            return;
        }
        this->set_current_user(user);
    }
    else {
        ret = DecryptPasswordDialog(static_cast<wxWindow*>(this)).ShowModal();
        if (ret == -1 || ret == wxID_CANCEL) {
            this->write_on_close = false;
            this->Close(false);
            return;
        }
        ret = LoginDialog(static_cast<wxWindow*>(this)).ShowModal();
        if (ret == -1 || ret == wxID_CANCEL) {
            this->write_on_close = false;
            this->Close(false);
            return;
        }
    }
    this->configure_controls();
    this->Show();
}

void MainFrame::configure_controls()
{
    // настройка блокировки кнопок
    if (!(this->current_user->isAdmin)) {
        this->button1->Disable(); this->button1->Hide();
        this->button3->Disable(); this->button3->Hide();
        this->button4->Disable(); this->button4->Hide();
    }

    // настройка листа
    this->listCtrl1->AppendColumn(L"Логин");
    this->listCtrl1->SetColumnWidth(this->listCtrl1->AppendColumn(L"Администратор"),
                                    wxLIST_AUTOSIZE_USEHEADER);
    this->listCtrl1->SetColumnWidth(this->listCtrl1->AppendColumn(L"Заблокирован"),
                                    wxLIST_AUTOSIZE_USEHEADER);
    this->listCtrl1->SetColumnWidth(this->listCtrl1->AppendColumn(L"Нужна смена пароля"),
                                    wxLIST_AUTOSIZE_USEHEADER);
    this->listCtrl1->SetColumnWidth(this->listCtrl1->AppendColumn(L"Сложность пароля"),
                                    wxLIST_AUTOSIZE_USEHEADER);

    if (this->current_user->isAdmin) {
        for (auto &i: *(this->passwd_manager.get_users())) {
            this->fill_row(this->listCtrl1->
                           InsertItem(this->listCtrl1->GetItemCount(), ""), &i);
        }
    }
    else {
        this->fill_row(this->listCtrl1->
                       InsertItem(this->listCtrl1->GetItemCount(), ""),
                       this->current_user);
    }
}

void MainFrame::button1OnButtonClick(wxCommandEvent &event)
{
    User* new_user = nullptr;
    int ret = AddUserDialog(static_cast<wxWindow*>(this), &new_user).ShowModal();
    if ((ret == 0) && (new_user != nullptr)) {
        int item = this->listCtrl1->InsertItem(this->listCtrl1->GetItemCount(), "");
        this->fill_row(item, new_user);
        this->listCtrl1->SetItemState(item, 0, wxLIST_STATE_SELECTED);
    }
}

void MainFrame::button2OnButtonClick(wxCommandEvent &event)
{
    if (this->get_selected_user() == nullptr) {
        wxMessageDialog(NULL, L"Выберите пользователя.", L"Ошибка",
                        wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
        return;
    }
    ChangePasswordDialog(static_cast<wxWindow*>(this),
                         this->get_selected_user()).ShowModal();
}

void MainFrame::button3OnButtonClick(wxCommandEvent &event)
{
    this->get_selected_user()->isBlocked = !this->get_selected_user()->isBlocked;
    this->update_frame();
}

void MainFrame::button4OnButtonClick(wxCommandEvent &event)
{
    if (this->get_selected_user() == nullptr) {
        wxMessageDialog(NULL, L"Выберите пользователя.", L"Ошибка",
                        wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
        return;
    }
    if (this->get_selected_user()->validatorData) {
        this->get_selected_user()->validatorData = 0;
    }
    else {
        this->get_selected_user()->validatorData = 1;
    }
    this->update_frame();
}

void MainFrame::button5OnButtonClick(wxCommandEvent &event)
{
    this->Close();
}

void MainFrame::button12OnButtonClick(wxCommandEvent& event)
{
    std::string disclaimer = "lab_sec\n\
Copyright (C) 2016  Kononov Andrey <flowneee@protonmail.com>\n\
\n\
This program is free software; you can redistribute it and/or\n\
modify it under the terms of the GNU General Public License\n\
as published by the Free Software Foundation; either version 2\n\
of the License, or (at your option) any later version.\n\
\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program; if not, write to the Free Software\n\
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.";
    wxMessageDialog(NULL, disclaimer, L"О программе").ShowModal();
}

void MainFrame::OnClose(wxCloseEvent& event)
{
    if (this->write_on_close) {
        this->passwd_manager.write();
    }
    event.Skip();
}

void MainFrame::listCtrl1OnListItemSelected(wxListEvent& event)
{
    this->update_frame();
}

void MainFrame::set_current_user(User* user)
{
    this->current_user = user;
}

void MainFrame::update_frame()
{
    User* user = this->get_selected_user();
    this->fill_row(this->listCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL,
                                                wxLIST_STATE_SELECTED), user);
    if (user->isBlocked) {
        this->button3->SetLabel(L"Разблокировать пользователя");
    }
    else {
        this->button3->SetLabel(L"Заблокировать пользователя");
    }
    if (user->validatorData) {
        this->button4->SetLabel(L"Отключить сложность пароля");
    }
    else {
        this->button4->SetLabel(L"Установить сложность пароля");
    }
}

void MainFrame::fill_row(int index, User *user)
{
    this->listCtrl1->SetItem(index, 0, user->login);
    this->listCtrl1->SetItem(index, 1, bool_to_wstring(user->isAdmin, "ru"));
    this->listCtrl1->SetItem(index, 2, bool_to_wstring(user->isBlocked, "ru"));
    this->listCtrl1->SetItem(index, 3, bool_to_wstring(user->isNew, "ru"));
    this->listCtrl1->SetItem(index, 4, bool_to_wstring(user->validatorData, "ru"));
}

User* MainFrame::get_selected_user()
{
    long item_index = -1;
    if ((item_index = this->listCtrl1->GetNextItem(item_index, wxLIST_NEXT_ALL,
                                                   wxLIST_STATE_SELECTED)) == wxNOT_FOUND) {
        return nullptr;
    }
    std::wstring login = this->listCtrl1->GetItemText(item_index, 0).ToStdWstring();
    return this->passwd_manager.get_user_by_login(login);
}

PasswdManager* MainFrame::get_passwd_manager()
{
    return &(this->passwd_manager);
}

bool MainFrame::verify_pc()
{
    // сбор информации о компьютере
    std::stringstream vrf;
    vrf << get_whoami() << ' '  // получение текущего пользователя
        << get_keyboard_model() << ' '  // получение модели клавиатуры
        << get_dislay_vertical_size() << ' '  // получение количества пикселей по вертикали
        << get_total_system_memory() << ' '  // получение количества памяти
        << get_file_or_directory_hard_drive_label();  // получение количества пикселей по вертикали
    std::stringstream command;

    // формирование команды для проверки информации о компьютере
    command << "/bin/bash -c 'openssl dgst -sha256 -verify <(echo -e \"" << PUBLIC_KEY
            << "\") -signature \"" << wstring_to_string(VRF_SHA256_PATH)
            << "\" <(echo \"" << vrf.str() << "\")'";

    // проверка информации, сохранение во временной переменной и сравннение с эталоном
    std::string result = exec(command.str().c_str());
    return result.substr(0, result.size() - 1) == "Verified OK";
}


//**********LoginDialog**********
void LoginDialog::button1OnButtonClick(wxCommandEvent& event)
{
    std::wstring login    = this->textCtrl1->GetValue().ToStdWstring();
    std::wstring password = this->textCtrl2->GetValue().ToStdWstring();
    User* user = static_cast<MainFrame*>(this->GetParent())->get_passwd_manager()
        ->get_user_by_login(login);
    if (user == nullptr) {
        this->show_error(L"Пользователя с таким логином не существует!");
        this->clear_input(3);
        return;
    }
    if (user->isBlocked) {
        this->show_error(L"Этот пользователь заблокирован!");
        this->clear_input(3);
        return;
    }
    if (user->isNew) {
        wxMessageDialog(NULL, (L"Установите новый пароль для пользователя!"))
            .ShowModal();
        int ret = ChangePasswordDialog(static_cast<MainFrame*>(this->GetParent()),
                                    user).ShowModal();
        if (ret == -1 || ret == wxID_CANCEL) {
            this->show_error(L"Вы не установили пароль для пользователя!");
            this->clear_input(2);
            return;
        }
        else {
            goto success_login;
        }
        return;
    }
    if (!user->compare_password(password)) {
        this->login_attempts--;
        if (this->login_attempts > 0) {
            this->show_error(L"Неправильный пароль!\nОсталось попыток: "
                             + std::to_wstring(this->login_attempts));
        }
        else {
            this->show_error(L"Неправильный пароль!\nУ вас не осталось попыток!");
            this->EndModal(-1);
        }
        return;
    }
success_login:
    static_cast<MainFrame*>(this->GetParent())->set_current_user(user);
    this->EndModal(0);
}

void LoginDialog::clear_input(char arg)
{
    switch (arg){
    case 0:
        return;
    case 1:
        this->textCtrl1->SetValue(L"");
        return;
    case 2:
        this->textCtrl2->SetValue(L"");
        return;
    case 3:
        this->textCtrl1->SetValue(L"");
        this->textCtrl2->SetValue(L"");
        return;
    default:
        return;
    }
}

void LoginDialog::show_error(std::wstring message)
{
    wxMessageDialog(NULL, message, L"Ошибка",
                    wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
}



//**********AddUserDialog**********
void AddUserDialog::button7OnButtonClick(wxCommandEvent &event)
{
    std::wstring s = this->textCtrl3->GetValue().ToStdWstring();
    *(this->new_user) = static_cast<MainFrame*>(this->GetParent())->
        get_passwd_manager()->add_user(s);
    if (this->new_user == nullptr) {
        wxMessageDialog(static_cast<wxWindow*>(this),
                        L"Пользователь с таким логином уже существует",
                        L"Ошибка", wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
        this->textCtrl3->SetValue(L"");
        return;
    }
    this->EndModal(0);
}

void AddUserDialog::button8OnButtonClick(wxCommandEvent &event)
{
    this->EndModal(-1);
}



//**********ChangePasswordDialog**********
ChangePasswordDialog::ChangePasswordDialog(wxWindow* parent, User* user)
    : BaseChangePasswordDialog(parent), user(user)
{
    if (user->isNew) {
        this->new_password_mode();
    }
}

void ChangePasswordDialog::button9OnButtonClick(wxCommandEvent& event)
{
    this->change_password_for_user(this->user);
}

void ChangePasswordDialog::button10OnButtonClick(wxCommandEvent& event)
{
    this->EndModal(-1);
}

void ChangePasswordDialog::change_password_for_user(User *user)
{
    std::wstring validation_error;
    int ret = user->change_password(
        this->textCtrl4->GetValue().ToStdWstring(),
        this->textCtrl5->GetValue().ToStdWstring(),
        this->textCtrl6->GetValue().ToStdWstring());
    switch (ret) {
    case OK:
        this->EndModal(0);
        break;
    case OLD_INCORRECT:
        wxMessageDialog(NULL, L"Вы неправильно ввели старый пароль!", L"Ошибка",
                        wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
        break;
    case NEW_DONT_MATCH:
        wxMessageDialog(NULL, L"Новый пароль не совпадает!", L"Ошибка",
                        wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
        break;
    case NEW_NOT_VALID:
        validation_error = L"Новый пароль недостаточно сложный!\n";
        validation_error += L"Текущие требования к паролю:\n";
        validation_error += L"Наличие латинских букв, символов кириллицы, цифр и знаков препинания";
        wxMessageDialog(NULL, validation_error, L"Ошибка",
                        wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
        break;
    }
    this->textCtrl4->SetValue(L"");
    this->textCtrl5->SetValue(L"");
    this->textCtrl6->SetValue(L"");
}

void ChangePasswordDialog::new_password_mode()
{
    this->SetLabel(L"Установка пароля");
    this->textCtrl4->Disable();
    this->textCtrl4->Hide();
    this->staticText5->Disable();
    this->staticText5->Hide();
    this->Fit();
}


//**********DecryptPasswordDialog**********
DecryptPasswordDialog::DecryptPasswordDialog(wxWindow* parent)
    : BaseCryptoPasswordDialog(parent)
{
    this->SetLabel(L"Расшифровка файла");
    this->staticText8->SetLabel(L"Пароль для расшифровки");
}

void DecryptPasswordDialog::button11OnButtonClick(wxCommandEvent& event)
{
    // чтение файла с пользователями
    /*std::ifstream encrypted_passwd(wstring_to_string(PASSWD_PATH),
                         std::ios::binary | std::ios::ate);
    std::streamsize size = encrypted_passwd.tellg();
    encrypted_passwd.seekg(0, std::ios::beg);
    unsigned char encrypted_buffer[size];
    encrypted_passwd.read(reinterpret_cast<char*>(encrypted_buffer), size);
    encrypted_passwd.close();*/

    // вычисление хеша введенного пароля
    unsigned char password_hash[32];
    sha_256(this->textCtrl7->GetValue().ToStdWstring(),
            reinterpret_cast<unsigned char*>(&password_hash));
    static_cast<MainFrame*>(this->GetParent())->get_passwd_manager()
        ->set_password_hash(password_hash);


    // расшифровка файла и запись его во временный
    /*unsigned char *decrypted_buffer;
    en_de_crypt(false, encrypted_buffer, &decrypted_buffer, size,
                password_hash, IVEC);

    std::string tmp_name = "/tmp/lab_sec_decrypted";
    std::ofstream tmp(tmp_name, std::ios::binary);
    tmp.write(reinterpret_cast<const char*>(decrypted_buffer), size);
    tmp.close();*/

    // чтение базы пользователей из временого фала и его удаление
    if (static_cast<MainFrame*>(this->GetParent())
        ->get_passwd_manager()->read_from_file(PASSWD_PATH))
    {
        this->EndModal(0);
        return;
    }
    else {
        wxMessageDialog(NULL, L"Вы неправильно ввели пароль от базы пользоватлей!",
                        L"Ошибка", wxOK | wxCENTRE | wxICON_WARNING).ShowModal();
        this->EndModal(-1);
        return;
    }

}


//**********EncryptPasswordDialog**********
EncryptPasswordDialog::EncryptPasswordDialog(wxWindow* parent)
    : BaseCryptoPasswordDialog(parent)
{
    this->SetLabel(L"Установка пароля базы");
    this->staticText8->SetLabel(L"Пароль для базы");
    //this->Fit();
}

void EncryptPasswordDialog::button11OnButtonClick(wxCommandEvent& event)
{
    unsigned char password_hash[32];
    sha_256(this->textCtrl7->GetValue().ToStdWstring(),
            reinterpret_cast<unsigned char*>(&password_hash));
    static_cast<MainFrame*>(this->GetParent())->get_passwd_manager()
        ->set_password_hash(password_hash);
    this->EndModal(0);
}
