///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-287-g77fa8e08-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/treelist.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/textctrl.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

namespace UI
{
	#define rgID_ADD_RESOURCE 1000
	#define rgID_DEL_RESOURCE 1001
	#define rgID_RES_TREE_LIST 1002
	#define rgID_FILENAME 1003
	#define rgID_UPDATE 1004

	///////////////////////////////////////////////////////////////////////////////
	/// Class MainWin
	///////////////////////////////////////////////////////////////////////////////
	class MainWin : public wxPanel
	{
		private:

		protected:
			wxStaticText* m_staticText2;
			wxStaticText* m_staticText21;
			wxButton* m_btnUpdate;

		public:
			wxButton* m_btnAdd;
			wxButton* m_btnDel;
			wxTreeListCtrl* m_treeListRes;
			wxFilePickerCtrl* m_filePickerRes;
			wxTextCtrl* m_textRelative;
			wxBoxSizer* m_btnBox;

			MainWin( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 590,504 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

			~MainWin();

	};

} // namespace UI

