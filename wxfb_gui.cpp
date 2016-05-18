///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 18 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxfb_gui.h"

///////////////////////////////////////////////////////////////////////////

BaseMainFrame::BaseMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 848,244 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	listCtrl1 = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer1->Add( listCtrl1, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	button1 = new wxButton( this, wxID_ANY, wxT("Добавить пользователя"), wxDefaultPosition, wxSize( 233,34 ), 0 );
	button1->SetMinSize( wxSize( 233,34 ) );
	
	bSizer2->Add( button1, 1, wxALL|wxEXPAND, 5 );
	
	button2 = new wxButton( this, wxID_ANY, wxT("Сменить пароль"), wxDefaultPosition, wxSize( 233,34 ), 0 );
	button2->SetMinSize( wxSize( 233,34 ) );
	
	bSizer2->Add( button2, 1, wxALL|wxEXPAND, 5 );
	
	button3 = new wxButton( this, wxID_ANY, wxT("Заблокировать пользователя"), wxDefaultPosition, wxSize( 233,34 ), 0 );
	button3->SetMinSize( wxSize( 233,34 ) );
	
	bSizer2->Add( button3, 1, wxALL|wxEXPAND, 5 );
	
	button4 = new wxButton( this, wxID_ANY, wxT("Установить сложность пароля"), wxDefaultPosition, wxSize( 233,34 ), 0 );
	button4->SetMinSize( wxSize( 233,34 ) );
	
	bSizer2->Add( button4, 1, wxALL|wxEXPAND, 5 );
	
	button5 = new wxButton( this, wxID_ANY, wxT("Выход из программы"), wxDefaultPosition, wxSize( 233,34 ), 0 );
	button5->SetMinSize( wxSize( 233,34 ) );
	
	bSizer2->Add( button5, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer2, 0, 0, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( BaseMainFrame::OnClose ) );
	button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button1OnButtonClick ), NULL, this );
	button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button2OnButtonClick ), NULL, this );
	button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button3OnButtonClick ), NULL, this );
	button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button4OnButtonClick ), NULL, this );
	button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button5OnButtonClick ), NULL, this );
}

BaseMainFrame::~BaseMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( BaseMainFrame::OnClose ) );
	button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button1OnButtonClick ), NULL, this );
	button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button2OnButtonClick ), NULL, this );
	button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button3OnButtonClick ), NULL, this );
	button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button4OnButtonClick ), NULL, this );
	button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::button5OnButtonClick ), NULL, this );
	
}

BaseLoginDialog::BaseLoginDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	staticText1 = new wxStaticText( this, wxID_ANY, wxT("Логин"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText1->Wrap( -1 );
	fgSizer1->Add( staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	textCtrl1->SetMinSize( wxSize( 200,-1 ) );
	
	fgSizer1->Add( textCtrl1, 0, wxALL|wxEXPAND, 5 );
	
	staticText2 = new wxStaticText( this, wxID_ANY, wxT("Пароль"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText2->Wrap( -1 );
	fgSizer1->Add( staticText2, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	fgSizer1->Add( textCtrl2, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( fgSizer1, 0, wxALL|wxEXPAND, 5 );
	
	button1 = new wxButton( this, wxID_ANY, wxT("Войти"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( button1, 0, wxALL|wxEXPAND, 5 );
	
	staticText3 = new wxStaticText( this, wxID_ANY, wxT("\n"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText3->Wrap( -1 );
	staticText3->Hide();
	
	bSizer3->Add( staticText3, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	bSizer3->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( BaseLoginDialog::OnClose ) );
	button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseLoginDialog::button1OnButtonClick ), NULL, this );
}

BaseLoginDialog::~BaseLoginDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( BaseLoginDialog::OnClose ) );
	button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseLoginDialog::button1OnButtonClick ), NULL, this );
	
}

BaseAddUserDialog::BaseAddUserDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	staticText4 = new wxStaticText( this, wxID_ANY, wxT("Логин"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText4->Wrap( -1 );
	bSizer7->Add( staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	textCtrl3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	textCtrl3->SetMinSize( wxSize( 200,-1 ) );
	
	bSizer7->Add( textCtrl3, 0, wxALL, 5 );
	
	
	bSizer6->Add( bSizer7, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	button7 = new wxButton( this, wxID_ANY, wxT("Добавить пользователя"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( button7, 0, wxALL|wxEXPAND, 5 );
	
	button8 = new wxButton( this, wxID_ANY, wxT("Отмена"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( button8, 0, wxALL, 5 );
	
	
	bSizer6->Add( bSizer8, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer6 );
	this->Layout();
	bSizer6->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	button7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseAddUserDialog::button7OnButtonClick ), NULL, this );
	button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseAddUserDialog::button8OnButtonClick ), NULL, this );
}

BaseAddUserDialog::~BaseAddUserDialog()
{
	// Disconnect Events
	button7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseAddUserDialog::button7OnButtonClick ), NULL, this );
	button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseAddUserDialog::button8OnButtonClick ), NULL, this );
	
}

BaseChangePasswordDialog::BaseChangePasswordDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	staticText5 = new wxStaticText( this, wxID_ANY, wxT("Старый пароль"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText5->Wrap( -1 );
	fgSizer2->Add( staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrl4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	#ifdef __WXGTK__
	if ( !m_textCtrl4->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl4->SetMaxLength(  );
	}
	#else
	m_textCtrl4->SetMaxLength(  );
	#endif
	m_textCtrl4->SetMinSize( wxSize( 200,-1 ) );
	
	fgSizer2->Add( m_textCtrl4, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Новый пароль"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer2->Add( m_staticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrl5 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	#ifdef __WXGTK__
	if ( !m_textCtrl5->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl5->SetMaxLength(  );
	}
	#else
	m_textCtrl5->SetMaxLength(  );
	#endif
	fgSizer2->Add( m_textCtrl5, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Еще раз новый пароль"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer2->Add( m_staticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrl6 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	#ifdef __WXGTK__
	if ( !m_textCtrl6->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl6->SetMaxLength(  );
	}
	#else
	m_textCtrl6->SetMaxLength(  );
	#endif
	fgSizer2->Add( m_textCtrl6, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer9->Add( fgSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	button9 = new wxButton( this, wxID_ANY, wxT("Сменить пароль"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( button9, 1, wxALL|wxEXPAND, 5 );
	
	button10 = new wxButton( this, wxID_ANY, wxT("Отмена"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( button10, 0, wxALL, 5 );
	
	
	bSizer9->Add( bSizer10, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	button9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseChangePasswordDialog::button9OnButtonClick ), NULL, this );
	button10->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseChangePasswordDialog::button10OnButtonClick ), NULL, this );
}

BaseChangePasswordDialog::~BaseChangePasswordDialog()
{
	// Disconnect Events
	button9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseChangePasswordDialog::button9OnButtonClick ), NULL, this );
	button10->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseChangePasswordDialog::button10OnButtonClick ), NULL, this );
	
}
