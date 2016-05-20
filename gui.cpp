#include "gui.hpp"
#include "user.hpp"
#include "functions.hpp"
#include "main.hpp"

#include <wx/msgdlg.h>


MainFrame::MainFrame(wxWindow* parent) : BaseMainFrame(parent)
{
    this->passwd_manager.read_from_file(L"passwd");
}

MainFrame::~MainFrame()
{
}

void MainFrame::initialize_frame()
{
    int ret = LoginDialog(static_cast<wxWindow*>(this)).ShowModal();
    if (ret == -1 || ret == wxID_CANCEL) {
        this->Close(false);
        return;
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
    ChangePasswordDialog(static_cast<wxWindow*>(this)).ShowModal();
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

void MainFrame::OnClose(wxCloseEvent& event)
{
    this->passwd_manager.write();
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
        wxMessageDialog(NULL, (L"Введите новый пароль для введеного пользователя!"))
            .ShowModal();
        int ret = SetPasswordDialog(static_cast<MainFrame*>(this->GetParent()),
                                    user).ShowModal();
        if (ret == -1 || ret == wxID_CANCEL) {
            this->show_error(L"Вы не установили пароль для пользователя!");
            this->clear_input(2);
            return;
        }
        else {
            user->isNew = false;
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
void ChangePasswordDialog::button9OnButtonClick(wxCommandEvent& event)
{
    User* selected_user = static_cast<MainFrame*>(this->GetParent())->get_selected_user();
    this->change_password_for_user(selected_user);
}

void ChangePasswordDialog::button10OnButtonClick(wxCommandEvent& event)
{
    this->EndModal(-1);
}

void ChangePasswordDialog::OnClose(wxCloseEvent& event)
{
    this->SetReturnCode(-1);
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


SetPasswordDialog::SetPasswordDialog(wxWindow* parent, User* user)
    : ChangePasswordDialog(parent), user(user)
{
    this->SetLabel(L"Установка пароля");
    this->textCtrl4->Disable();
    this->textCtrl4->Hide();
    this->staticText5->Disable();
    this->staticText5->Hide();
    this->Fit();
}

void SetPasswordDialog::button9OnButtonClick(wxCommandEvent& event)
{
    this->change_password_for_user(this->user);
}
