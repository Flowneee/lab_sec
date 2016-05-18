///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 18 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WXFB_GUI_H__
#define __WXFB_GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class BaseMainFrame
///////////////////////////////////////////////////////////////////////////////
class BaseMainFrame : public wxFrame 
{
	private:
	
	protected:
		wxListCtrl* listCtrl1;
		wxButton* button1;
		wxButton* button2;
		wxButton* button3;
		wxButton* button4;
		wxButton* button5;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void button1OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void button2OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void button3OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void button4OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void button5OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		BaseMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Управление пользователями"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 848,244 ), long style = wxCAPTION|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~BaseMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseLoginDialog
///////////////////////////////////////////////////////////////////////////////
class BaseLoginDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* staticText1;
		wxTextCtrl* textCtrl1;
		wxStaticText* staticText2;
		wxTextCtrl* textCtrl2;
		wxButton* button1;
		wxStaticText* staticText3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void button1OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		BaseLoginDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Вход"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~BaseLoginDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseAddUserDialog
///////////////////////////////////////////////////////////////////////////////
class BaseAddUserDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* staticText4;
		wxTextCtrl* textCtrl3;
		wxButton* button7;
		wxButton* button8;
		
		// Virtual event handlers, overide them in your derived class
		virtual void button7OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void button8OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		BaseAddUserDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Добавить пользователя"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~BaseAddUserDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseChangePasswordDialog
///////////////////////////////////////////////////////////////////////////////
class BaseChangePasswordDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* staticText5;
		wxTextCtrl* m_textCtrl4;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_textCtrl5;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_textCtrl6;
		wxButton* button9;
		wxButton* button10;
		
		// Virtual event handlers, overide them in your derived class
		virtual void button9OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void button10OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		BaseChangePasswordDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Смена пароля"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~BaseChangePasswordDialog();
	
};

#endif //__WXFB_GUI_H__
