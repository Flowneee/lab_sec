#ifndef __GUI_H__
#define __GUI_H__

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

#include <string>
#include <vector>

#include "wxfb_gui.h"
#include "passwdmanager.hpp"
#include "user.hpp"

class MainFrame : public BaseMainFrame
{
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
    bool verify_pc();
protected:
    virtual void OnClose(wxCloseEvent& event);
    virtual void button1OnButtonClick(wxCommandEvent& event);
    virtual void button2OnButtonClick(wxCommandEvent& event);
    virtual void button3OnButtonClick(wxCommandEvent& event);
    virtual void button4OnButtonClick(wxCommandEvent& event);
    virtual void button5OnButtonClick(wxCommandEvent& event);
    virtual void button12OnButtonClick(wxCommandEvent& event);
    virtual void listCtrl1OnListItemSelected(wxListEvent& event);

    PasswdManager passwd_manager;
    User* current_user;
    bool write_on_close;
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
    ChangePasswordDialog(wxWindow* parent, User* user);
    virtual ~ChangePasswordDialog() {};
protected:
    virtual void button9OnButtonClick(wxCommandEvent& event);
    virtual void button10OnButtonClick(wxCommandEvent& event);
    void new_password_mode();
    void change_password_for_user(User* user);

    User* user;
};

class DecryptPasswordDialog : public BaseCryptoPasswordDialog
{
public:
    DecryptPasswordDialog(wxWindow* parent);
    virtual ~DecryptPasswordDialog() {};
protected:
    virtual void button11OnButtonClick(wxCommandEvent& event);
};

class EncryptPasswordDialog : public BaseCryptoPasswordDialog
{
public:
    EncryptPasswordDialog(wxWindow* parent);
    virtual ~EncryptPasswordDialog() {};
protected:
    virtual void button11OnButtonClick(wxCommandEvent& event);
};


#endif
