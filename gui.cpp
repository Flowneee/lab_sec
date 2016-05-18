#include "gui.hpp"
#include "user.hpp"
#include "functions.hpp"

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
    if (!this->login()) {
        this->Close();
    }
    this->configure_controls();
    this->Show();
}

void MainFrame::configure_controls()
{
    // настройка блокировки кнопок
    if (!(this->current_user.isAdmin)) {
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

    if (this->current_user.isAdmin) {
        for (auto &i: *(this->passwd_manager.get_users())) {
            this->fill_row(this->listCtrl1->
                           InsertItem(this->listCtrl1->GetItemCount(), ""), &i);
        }
    }
    else {
        this->fill_row(this->listCtrl1->
                       InsertItem(this->listCtrl1->GetItemCount(), ""),
                       &this->current_user);
    }
}

void MainFrame::button1OnButtonClick(wxCommandEvent &event)
{
    User* new_user = nullptr;
    int ret = AddUserDialog(static_cast<wxWindow*>(this), &(this->passwd_manager),
                            &new_user).ShowModal();
    if ((ret == 0) && (new_user != nullptr)) {
        this->fill_row(this->listCtrl1->
                       InsertItem(this->listCtrl1->GetItemCount(), ""), new_user);
    }

}

void MainFrame::button2OnButtonClick(wxCommandEvent &event)
{

}

void MainFrame::button3OnButtonClick(wxCommandEvent &event)
{

}

void MainFrame::button4OnButtonClick(wxCommandEvent &event)
{

}

void MainFrame::button5OnButtonClick(wxCommandEvent &event)
{

}

void MainFrame::OnClose(wxCloseEvent& event)
{
    this->passwd_manager.write();
    this->Destroy();
}

bool MainFrame::login()
{
    std::wstring login, passwd;
    bool success = false;
    LoginDialog* d = new LoginDialog(NULL, &login, &passwd);
    d->ShowModal();
    delete d;
    if (this->passwd_manager.is_correct_user(login, passwd)) {
        success = true;
    }
    else {
        for (int counter = 2; counter >= 1; counter--) {
            login = L"";
            passwd = L"";
            std::wstring label =
                L"Неправильный логин или пароль!\nОсталось попыток: " +
                std::to_wstring(counter);
            LoginDialog* d = new LoginDialog(NULL, &login, &passwd, label);
            d->ShowModal();
            delete d;
            if (this->passwd_manager.is_correct_user(login, passwd)) {
                success = true;
                break;
            }
        }
    }
    if (success) {
        this->current_user = *(this->passwd_manager.get_user_by_login(login));
    }
    return success;
}

void MainFrame::fill_row(int index, User *user)
{
    this->listCtrl1->SetItem(index, 0, user->login);
    this->listCtrl1->SetItem(index, 1, bool_to_wstring(user->isAdmin, "ru"));
    this->listCtrl1->SetItem(index, 2, bool_to_wstring(user->isBlocked, "ru"));
    this->listCtrl1->SetItem(index, 3, bool_to_wstring(user->isNew, "ru"));
    this->listCtrl1->SetItem(index, 4, bool_to_wstring(user->isComplexityLimited,
                                                       "ru"));
}

User* MainFrame::get_selected_user()
{
    std::wstring login = L"";
    return this->passwd_manager.get_user_by_login(login);
}



//**********LoginDialog**********
LoginDialog::LoginDialog(wxWindow* parent, std::wstring* login,
                         std::wstring* passwd, std::wstring label)
    : BaseLoginDialog(parent)
{
    this->login = login;
    this->passwd = passwd;
    if (label != L"") {
        this->staticText3->SetLabel(label);
        this->staticText3->Show(true);
        this->Fit();
    }
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::button1OnButtonClick(wxCommandEvent& event)
{
    *this->login  = this->textCtrl1->GetValue().ToStdWstring();
    *this->passwd = this->textCtrl2->GetValue().ToStdWstring();
    this->EndModal(0);
}

void LoginDialog::OnClose(wxCloseEvent& event)
{
    this->GetParent()->Close();
}



//**********AddUserDialog**********
AddUserDialog::AddUserDialog(wxWindow* parent, PasswdManager* passwd_manager,
                             User** new_user)
    : BaseAddUserDialog(parent), passwd_manager(passwd_manager), new_user(new_user)
{
}

AddUserDialog::~AddUserDialog()
{
}

void AddUserDialog::button7OnButtonClick(wxCommandEvent &event)
{
    std::wstring s = this->textCtrl3->GetValue().ToStdWstring();
    *(this->new_user) = this->passwd_manager->add_user(s);
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
