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
    virtual void OnClose(wxCloseEvent& event);
    virtual void button1OnButtonClick(wxCommandEvent& event);
    virtual void button2OnButtonClick(wxCommandEvent& event);
    virtual void button3OnButtonClick(wxCommandEvent& event);
    virtual void button4OnButtonClick(wxCommandEvent& event);
    virtual void button5OnButtonClick(wxCommandEvent& event);

    PasswdManager passwd_manager;
    User current_user;
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
    void initialize_frame(); // начальная настройка фрейма после логина
    bool login(); // функция, вызывающая диалог логина
    void configure_controls();
    void fill_row(int index, User* user);

    User* get_selected_user();
};

class LoginDialog : public BaseLoginDialog
{
private:
    std::wstring* login;
    std::wstring* passwd;
protected:
    virtual void button1OnButtonClick(wxCommandEvent& event);
    virtual void OnClose(wxCloseEvent& event);
public:
    LoginDialog(wxWindow* parent, std::wstring* login, std::wstring* passwd,
                std::wstring label = L"");
    virtual ~LoginDialog();
};

class AddUserDialog : public BaseAddUserDialog
{
private:
    PasswdManager* passwd_manager;
    User** new_user;
protected:
    virtual void button7OnButtonClick(wxCommandEvent& event);
    virtual void button8OnButtonClick(wxCommandEvent& event);
public:
    AddUserDialog(wxWindow* parent, PasswdManager* passwd_manager, User** new_user);
    virtual ~AddUserDialog();
};

class ChangePasswordDialog : public BaseChangePasswordDialog
{
private:
    PasswdManager* passwd_manager;
protected:
    virtual void button9OnButtonClick(wxCommandEvent& event);
    virtual void button10OnButtonClick(wxCommandEvent& event);
}

#endif
