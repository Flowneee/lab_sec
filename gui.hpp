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
    virtual void listCtrl1OnListItemSelected(wxListEvent& event);

    PasswdManager passwd_manager;
    User* current_user;
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
    void initialize_frame(); // начальная настройка фрейма после логина
    void configure_controls();
    void fill_row(int index, User* user);
    User* get_selected_user();
    PasswdManager* get_passwd_manager();
    void set_current_user(User* user);
    void update_frame();
};

class LoginDialog : public BaseLoginDialog
{
public:
    LoginDialog(wxWindow* parent) : BaseLoginDialog(parent) {};
    virtual ~LoginDialog() {};

    int login(std::wstring login, std::wstring);
    virtual void clear_input(char arg = 3); // 0 - NONE, 1 - LOGIN, 2 - PASSWORD, 3 - BOTH
    void show_error(std::wstring message);
protected:
    virtual void button1OnButtonClick(wxCommandEvent& event);
private:
    int login_attempts = 3;
};

class AddUserDialog : public BaseAddUserDialog
{
public:
    AddUserDialog(wxWindow* parent,  User** new_user)
        : BaseAddUserDialog(parent), new_user(new_user) {};
    virtual ~AddUserDialog() {};
private:
    User** new_user;
protected:
    virtual void button7OnButtonClick(wxCommandEvent& event);
    virtual void button8OnButtonClick(wxCommandEvent& event);
};

class ChangePasswordDialog : public BaseChangePasswordDialog
{
public:
    ChangePasswordDialog(wxWindow* parent) : BaseChangePasswordDialog(parent) {};
    virtual ~ChangePasswordDialog() {};
protected:
    virtual void button9OnButtonClick(wxCommandEvent& event);
    virtual void button10OnButtonClick(wxCommandEvent& event);
    virtual void OnClose(wxCloseEvent& event);
    void change_password_for_user(User* user);
};

class SetPasswordDialog : public ChangePasswordDialog
{
public:
    SetPasswordDialog(wxWindow* parent, User* user);
    virtual ~SetPasswordDialog() {};
protected:
    virtual void button9OnButtonClick(wxCommandEvent& event);
private:
    User* user;
};


#endif
