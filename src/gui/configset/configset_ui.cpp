///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-287-g77fa8e08-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "configset_ui.h"

///////////////////////////////////////////////////////////////////////////
using namespace UI;

ConfigSet::ConfigSet( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );


	bSizer7->Add( 0, 10, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	bSizer8->SetMinSize( wxSize( -1,30 ) );
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Function Prefix: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer8->Add( m_staticText1, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textFunctionPrefix = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_textFunctionPrefix, 1, wxEXPAND, 5 );


	bSizer7->Add( bSizer8, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxHORIZONTAL );

	bSizer81->SetMinSize( wxSize( -1,30 ) );
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Source Path: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer81->Add( m_staticText11, 0, wxALIGN_CENTER|wxALL, 5 );

	m_filePickerSourcePath = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_SMALL|wxFLP_USE_TEXTCTRL );
	bSizer81->Add( m_filePickerSourcePath, 1, wxEXPAND, 5 );


	bSizer7->Add( bSizer81, 0, wxALL|wxEXPAND, 5 );

	m_btnBox = new wxStdDialogButtonSizer();
	m_btnBoxOK = new wxButton( this, wxID_OK );
	m_btnBox->AddButton( m_btnBoxOK );
	m_btnBoxCancel = new wxButton( this, wxID_CANCEL );
	m_btnBox->AddButton( m_btnBoxCancel );
	m_btnBox->Realize();

	bSizer7->Add( m_btnBox, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer7 );
	this->Layout();
}

ConfigSet::~ConfigSet()
{
}
