///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-287-g77fa8e08-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "mainwin_ui.h"

///////////////////////////////////////////////////////////////////////////
using namespace UI;

MainWin::MainWin( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_btnAdd = new wxButton( this, rgID_ADD_RESOURCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE );

	m_btnAdd->SetBitmapMargins( wxSize( 0,0 ) );
	m_btnAdd->SetMinSize( wxSize( 32,32 ) );

	bSizer5->Add( m_btnAdd, 0, wxLEFT|wxTOP, 5 );

	m_btnDel = new wxButton( this, rgID_DEL_RESOURCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE );

	m_btnDel->SetBitmapMargins( wxSize( 0,0 ) );
	m_btnDel->SetMinSize( wxSize( 32,32 ) );

	bSizer5->Add( m_btnDel, 0, wxLEFT|wxTOP, 5 );


	bSizer1->Add( bSizer5, 0, wxEXPAND, 5 );

	m_treeListRes = new wxTreeListCtrl( this, rgID_RES_TREE_LIST, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );

	bSizer1->Add( m_treeListRes, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Real Path："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer4->Add( m_staticText2, 0, wxBOTTOM|wxLEFT|wxTOP, 8 );

	m_filePickerRes = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_SMALL|wxFLP_USE_TEXTCTRL );
	bSizer4->Add( m_filePickerRes, 1, wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer4, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Virtual Path："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer41->Add( m_staticText21, 0, wxBOTTOM|wxLEFT|wxTOP, 8 );

	m_textRelative = new wxTextCtrl( this, rgID_FILENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer41->Add( m_textRelative, 1, wxALL|wxEXPAND, 5 );

	m_btnUpdate = new wxButton( this, rgID_UPDATE, wxT("√"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btnUpdate->SetMinSize( wxSize( 32,-1 ) );

	bSizer41->Add( m_btnUpdate, 0, wxALL, 5 );


	bSizer3->Add( bSizer41, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );

	m_btnBox = new wxBoxSizer( wxHORIZONTAL );


	bSizer1->Add( m_btnBox, 0, wxALIGN_RIGHT|wxBOTTOM|wxTOP, 8 );


	this->SetSizer( bSizer1 );
	this->Layout();
}

MainWin::~MainWin()
{
}
