#ifndef __GUI_H__
#define __GUI_H__

#include <string>
#include <vector>

#include "wxfb_gui.h"
#include "passwdmanager.hpp"
#include "user.hpp"


class MainFrame : public BaseMainFrame
{
private:

protected:
    virtual void m_button1OnButtonClick(wxCommandEvent& event);
    virtual void m_button2OnButtonClick(wxCommandEvent& event) {event.Skip();};
    virtual void OnCloseFrame(wxCommandEvent& event);

    PasswdManager passwd_manager;
    User current_user;
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
    void initialize_frame(); // начальная настройка фрейма после логина
    bool login(); // функция, вызывающая диалог логина
};

class LoginDialog : public BaseLoginDialog
{
private:
    std::string* m_login;
    std::string* m_passwd;
protected:
    virtual void m_button1OnButtonClick(wxCommandEvent& event);
    virtual void LoginDialogOnClose(wxCloseEvent& event);
public:
    LoginDialog(wxWindow* parent, std::string* login, std::string* passwd,
                std::wstring label = L"");
    virtual ~LoginDialog();
};

#endif
