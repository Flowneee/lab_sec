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
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class BaseMainFrame
///////////////////////////////////////////////////////////////////////////////
class BaseMainFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText5;
		wxListBox* m_listBox1;

		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }


	public:

		BaseMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Управление пользователями"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 799,510 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );

		~BaseMainFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseLoginDialog
///////////////////////////////////////////////////////////////////////////////
class BaseLoginDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrl1;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrl2;
		wxButton* m_button1;
		wxStaticText* m_staticText3;

		// Virtual event handlers, overide them in your derived class
		virtual void LoginDialogOnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void m_button1OnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		BaseLoginDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Вход"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxCLOSE_BOX );
		~BaseLoginDialog();

};

#endif //__WXFB_GUI_H__
