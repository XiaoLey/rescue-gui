//
// Created by XiaoLey on 2023/05/28.
//

#ifndef RESCUE_GUI_MAINWIN_H__
#define RESCUE_GUI_MAINWIN_H__

#include <wx/wx.h>
#include "common.h"
#include "mainwin_ui.h"

class MainWin final : public wxFrame
{
public:
    explicit MainWin();
    ~MainWin() final;

protected:
    void OnShow(wxShowEvent &e);
    void OnMenuClose(wxCommandEvent &e);
    void OnMenuCreateResourceProject(wxCommandEvent &e);
    void OnMenuOpenResourceProject(wxCommandEvent &e);
    void OnAddResourceBtnClicked(wxCommandEvent &e);
    void OnDelResourceBtnClicked(wxCommandEvent &e);
    void OnSaveBtnClicked(wxCommandEvent &e);
    void OnSaveAsBtnClicked(wxCommandEvent &e);
    void OnGenerateBtnClicked(wxCommandEvent &e);
    void OnUpdateBtnClicked(wxCommandEvent &e);
    void OnTreeListResItemActivated(wxTreeListEvent &e);
    void OnTextCtrlFilenameEnter(wxCommandEvent &e);
    void OnTreeListResSetFocus(wxFocusEvent &e);

    void ClearAll();

    wxString GetJsonByTreeListData();

private:
    static void SplitPathAndFilename(const wxString &pathAndFilename, wxString *path, wxString *filename);

private:
    UI::MainWin *ui;
    wxString m_resProjectPath;

    wxDECLARE_EVENT_TABLE();
};


#endif  // RESCUE_GUI_MAINWIN_H__
