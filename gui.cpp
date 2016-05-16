#include "gui.hpp"
#include "user.hpp"

MainFrame::MainFrame(wxWindow* parent) : BaseMainFrame(parent)
{
    this->passwd_manager.read_from_file("passwd");
}

MainFrame::~MainFrame()
{
}

void MainFrame::initialize_frame()
{
    if (!this->login()) {
        this->Close();
    }
    wxArrayString user_list = {};
    if (this->current_user.isAdmin) {
        for (auto i: this->passwd_manager.get_users()) {
            user_list.Add(i.login);
        }
    }
    else {
        user_list.Add(this->current_user.login);
    }
    this->m_listBox1->InsertItems(user_list, 0);
    this->Show();
}

void MainFrame::m_button1OnButtonClick(wxCommandEvent& event)
{
}

void MainFrame::OnCloseFrame(wxCommandEvent& event)
{
    this->Destroy();
}

bool MainFrame::login()
{
    std::string login, passwd;
    bool success = false;
    LoginDialog* d = new LoginDialog(NULL, &login, &passwd);
    d->ShowModal();
    delete d;
    if (this->passwd_manager.is_correct_user(login, passwd)) {
        success = true;
    }
    else {
        for (int counter = 2; counter >= 1; counter--) {
            login = "";
            passwd = "";
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
        this->passwd_manager.get_user_by_login(login, &(this->current_user));
    }
    return success;
}



//**********LoginDialog**********
LoginDialog::LoginDialog(wxWindow* parent, std::string* login,
                         std::string* passwd, std::wstring label)
    : BaseLoginDialog(parent)
{
    this->m_login = login;
    this->m_passwd = passwd;
    this->m_staticText3->SetLabel(label);
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::m_button1OnButtonClick(wxCommandEvent& event)
{
    *this->m_login  = this->m_textCtrl1->GetValue().ToStdString();
    *this->m_passwd = this->m_textCtrl2->GetValue().ToStdString();
    this->EndModal(0);
}

void LoginDialog::LoginDialogOnClose(wxCloseEvent& event)
{
    this->GetParent()->Close();
}
