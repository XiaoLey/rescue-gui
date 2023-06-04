///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-287-g77fa8e08-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

namespace UI
{
	///////////////////////////////////////////////////////////////////////////////
	/// Class ConfigSet
	///////////////////////////////////////////////////////////////////////////////
	class ConfigSet : public wxPanel
	{
		private:

		protected:
			wxStaticText* m_staticText1;
			wxStaticText* m_staticText11;

		public:
			wxTextCtrl* m_textFunctionPrefix;
			wxFilePickerCtrl* m_filePickerSourcePath;
			wxStdDialogButtonSizer* m_btnBox;
			wxButton* m_btnBoxOK;
			wxButton* m_btnBoxCancel;

			ConfigSet( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 391,143 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

			~ConfigSet();

	};

} // namespace UI

