//
// Created by XiaoLey on 2023/05/31.
//

#include "configset.h"


wxBEGIN_EVENT_TABLE(ConfigSet, wxDialog)
wxEND_EVENT_TABLE()


ConfigSet::ConfigSet(wxWindow *parent) :
    wxDialog(parent, wxID_ANY, wxT("Config Setting"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE),
    ui(new UI::ConfigSet(this))
{
    ui->m_filePickerSourcePath->SetPickerCtrlGrowable();
    ui->m_filePickerSourcePath->SetTextCtrlGrowable();

    ui->m_btnBox->GetAffirmativeButton()->SetDefault();  // set the default button

    wxDialog::Fit();  // automatically resize windows
}


ConfigSet::~ConfigSet() = default;


void ConfigSet::SetFunctionPrefix(const wxString &functionPrefix)
{
    ui->m_textFunctionPrefix->SetValue(functionPrefix);
}


void ConfigSet::GetFunctionPrefix(wxString *functionPrefix)
{
    *functionPrefix = ui->m_textFunctionPrefix->GetValue();
}


void ConfigSet::SetSourcePath(const wxString &sourcePath)
{
    ui->m_filePickerSourcePath->SetPath(sourcePath);
}


void ConfigSet::GetSourcePath(wxString *sourcePath)
{
    *sourcePath = ui->m_filePickerSourcePath->GetPath();
}
