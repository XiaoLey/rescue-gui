//
// Created by XiaoLey on 2023/05/28.
//

#include <wx/mstream.h>
#include <wx/process.h>
#include <wx/stdpaths.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include "mainwin.h"
#include "configset/configset.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "res/resources.h"

#define FUNCTION_PREFIX "rescue"
#define SOURCE_PATH     "resources.c"


wxBEGIN_EVENT_TABLE(MainWin, wxFrame)
    EVT_SHOW(MainWin::OnShow)
    EVT_MENU(wxID_NEW, MainWin::OnMenuCreateResourceProject)
    EVT_MENU(wxID_OPEN, MainWin::OnMenuOpenResourceProject)
    EVT_MENU(wxID_SAVE, MainWin::OnSaveBtnClicked)
    EVT_MENU(wxID_SAVEAS, MainWin::OnSaveAsBtnClicked)
    EVT_MENU(rgID_GENERATE, MainWin::OnGenerateBtnClicked)
    EVT_MENU(wxID_EXIT, MainWin::OnMenuClose)
    EVT_BUTTON(rgID_ADD_RESOURCE, MainWin::OnAddResourceBtnClicked)
    EVT_BUTTON(rgID_DEL_RESOURCE, MainWin::OnDelResourceBtnClicked)
    EVT_BUTTON(wxID_SAVE, MainWin::OnSaveBtnClicked)
    EVT_BUTTON(rgID_GENERATE, MainWin::OnGenerateBtnClicked)
    EVT_BUTTON(rgID_UPDATE, MainWin::OnUpdateBtnClicked)
    EVT_TREELIST_ITEM_ACTIVATED(wxID_ANY, MainWin::OnTreeListResItemActivated)
    EVT_TEXT_ENTER(rgID_FILENAME, MainWin::OnTextCtrlFilenameEnter)
wxEND_EVENT_TABLE()


MainWin::MainWin() :
    wxFrame(nullptr, wxID_ANY, wxT("rescue gui")),
    ui(new UI::MainWin(this))
{
    ui->m_filePickerRes->SetTextCtrlGrowable();    // automatically resize text boxes
    ui->m_filePickerRes->SetPickerCtrlGrowable();  // automatically resize button

    // 添加菜单栏
    auto menuBar  = new wxMenuBar;
    auto menuFile = new wxMenu;
    menuFile->Append(wxID_NEW);
    menuFile->Append(wxID_OPEN);
    menuFile->Append(wxID_SAVE);
    menuFile->Append(wxID_SAVEAS);
    menuFile->AppendSeparator();
    menuFile->Append(rgID_GENERATE, wxT("&Generate Source"));
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    menuBar->Append(menuFile, wxT("&File"));
    wxFrame::SetMenuBar(menuBar);

    // add a button in the bottom button box
    ui->m_btnBox->Add(new wxButton(ui, rgID_GENERATE, wxT("Generate Source")), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
    ui->m_btnBox->Add(new wxButton(ui, wxID_SAVE, wxT("Save")), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
    ui->m_btnBox->Layout();

    ui->m_treeListRes->AppendColumn(wxT("resource name"));
    ui->m_treeListRes->AppendColumn(wxT("resource path"));

    ui->m_treeListRes->Bind(wxEVT_SET_FOCUS, &MainWin::OnTreeListResSetFocus, this);

    // set icon
    do {
        size_t sz;
        char *dt;

        wxImage::AddHandler(new wxPNGHandler);

        res_copy_resource("img/add.png", &dt, &sz);
        wxMemoryInputStream streamAddImg(dt, sz);
        ui->m_btnAdd->SetBitmap(wxBitmap(streamAddImg));
        delete dt;

        res_copy_resource("img/delete.png", &dt, &sz);
        wxMemoryInputStream streamDelImg(dt, sz);
        ui->m_btnDel->SetBitmap(wxBitmap(streamDelImg));
        delete dt;
    } while (0);  // NOLINT

    // set the first directory
    ui->m_treeListRes->AppendItem(ui->m_treeListRes->GetRootItem(), wxT(FUNCTION_PREFIX));
    ui->m_treeListRes->SetItemText(ui->m_treeListRes->GetFirstItem(), 1, wxT(SOURCE_PATH));

    wxFrame::Fit();  // automatically resize windows
}


MainWin::~MainWin() = default;


void MainWin::OnShow(wxShowEvent &e)
{
// It mainly solves the problem that the GTK title bar under Linux is not calculated when the window is created
#ifdef wxWindowGTK
    wxSize sz = GetSize();
    SetClientSize(sz);
#endif
    e.Skip();
}


void MainWin::OnMenuClose(wxCommandEvent &WXUNUSED(e))
{
    Close();
}


void MainWin::OnMenuCreateResourceProject(wxCommandEvent &WXUNUSED(e))
{
    ClearAll();
}


void MainWin::OnMenuOpenResourceProject(wxCommandEvent &WXUNUSED(e))
{
    wxFileDialog dialog(this, wxT("open resource project"), wxEmptyString, wxEmptyString,
                        "All files (*)|*", wxFD_DEFAULT_STYLE | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
    if (dialog.ShowModal() == wxID_CANCEL) return;

    wxString projectPath = dialog.GetPath();
    wxFile file(projectPath);
    if (!file.IsOpened()) {
        wxLogError("failed to open file '%s'", projectPath);
        return;
    }

    wxFileInputStream stream(file);
    if (!stream.IsOk()) {
        wxLogError("failed to open file '%s'", projectPath);
        return;
    }

    char *json = new char[stream.GetLength() + 1];
    stream.ReadAll(json, stream.GetLength());
    json[stream.GetLength()] = '\0';

    using namespace rapidjson;
    Document doc;
    doc.Parse(json);

    if (!doc.IsArray()) {
        wxLogError("invalid resource project file '%s'", projectPath);
        return;
    }

    ClearAll();
    m_resProjectPath = dialog.GetPath();

    wxString prefix     = doc.GetArray()[0]["prefix"].GetString();
    wxString sourcePath = doc.GetArray()[0]["source_path"].GetString();
    ui->m_treeListRes->SetItemText(ui->m_treeListRes->GetFirstItem(), prefix);
    ui->m_treeListRes->SetItemText(ui->m_treeListRes->GetFirstItem(), 1, sourcePath);
    doc.GetArray().Erase(doc.GetArray().Begin());

    for (auto &v : doc.GetArray()) {
        auto parentItem = ui->m_treeListRes->GetFirstItem();
        auto name       = v["name"].GetString();
        auto path       = v["path"].GetString();
        auto item       = ui->m_treeListRes->AppendItem(parentItem, wxString::FromUTF8(name));
        ui->m_treeListRes->SetItemText(item, 1, wxString::FromUTF8(path));
    }

    delete[] json;

    ui->m_treeListRes->SetSortColumn(0);                           // sort
    ui->m_treeListRes->Expand(ui->m_treeListRes->GetFirstItem());  // expand the list
    ui->m_treeListRes->SetFocus();                                 // focus
}


void MainWin::OnAddResourceBtnClicked(wxCommandEvent &WXUNUSED(e))
{
    wxFileDialog dialog(this, wxT("add resource"), wxEmptyString, wxEmptyString,
                        "All files (*)|*", wxFD_DEFAULT_STYLE | wxFD_FILE_MUST_EXIST);

    if (dialog.ShowModal() == wxID_CANCEL)
        return;

    dialog.GetFilename();

    auto parentItem = ui->m_treeListRes->GetFirstItem();
    auto item       = ui->m_treeListRes->AppendItem(parentItem, dialog.GetFilename());
    ui->m_treeListRes->SetItemText(item, 1, dialog.GetPath());
    ui->m_treeListRes->SetSortColumn(0);                           // sort
    ui->m_treeListRes->Select(item);                               // select
    ui->m_treeListRes->SetFocus();                                 // focus
    ui->m_treeListRes->Expand(ui->m_treeListRes->GetFirstItem());  // expand the list
}


void MainWin::OnDelResourceBtnClicked(wxCommandEvent &WXUNUSED(e))
{
    auto curItem = ui->m_treeListRes->GetSelection();
    if (!curItem.IsOk() || curItem == ui->m_treeListRes->GetFirstItem()) {
        wxMessageBox("can't delete root item!", "error", wxOK | wxICON_ERROR);
        return;
    }

    ui->m_treeListRes->DeleteItem(curItem);
}


void MainWin::OnSaveBtnClicked(wxCommandEvent &WXUNUSED(e))
{
    wxString output = GetJsonByTreeListData();

    if (m_resProjectPath.IsEmpty()) {
        wxFileDialog dialog(this, wxT("save resource project"), wxEmptyString, wxEmptyString,
                            "All files (*)|*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
        if (dialog.ShowModal() == wxID_CANCEL) return;

        m_resProjectPath = dialog.GetPath();
    }

    wxFile file(m_resProjectPath, wxFile::write);
    if (!file.IsOpened()) {
        wxMessageBox("can't open file!", "error", wxOK | wxICON_ERROR);
        return;
    }
    file.Write(output);
    file.Close();

    wxMessageBox("save success!", "success", wxOK | wxICON_INFORMATION);
}


void MainWin::OnSaveAsBtnClicked(wxCommandEvent &e)
{
    m_resProjectPath.Clear();
    OnSaveBtnClicked(e);
}


void MainWin::OnGenerateBtnClicked(wxCommandEvent &WXUNUSED(e))
{
    auto item = ui->m_treeListRes->GetFirstChild(ui->m_treeListRes->GetFirstItem());
    if (!item.IsOk()) {
        wxMessageBox("no resource!", "error", wxOK | wxICON_ERROR);
        return;
    }

    wxString prefix     = ui->m_treeListRes->GetItemText(ui->m_treeListRes->GetFirstItem());
    wxString sourcePath = ui->m_treeListRes->GetItemText(ui->m_treeListRes->GetFirstItem(), 1);

    if (prefix.IsEmpty() || sourcePath.IsEmpty()) {
        wxMessageBox("prefix or source path is empty!", "error", wxOK | wxICON_ERROR);
        return;
    }

    if (wxFileExists(sourcePath)) {
        if (wxMessageBox("source path is exists, overwrite?", "warning", wxYES_NO | wxICON_WARNING) != wxYES)
            return;
    }

    wxFileName exePath(wxStandardPaths::Get().GetExecutablePath());
    wxString exeDir = exePath.GetPath(wxPATH_GET_VOLUME);
    wxString cmd    = exeDir + wxFileName::GetPathSeparator() + "rescue -o \"" + sourcePath + "\" -p \"" + prefix + "\" ";

    for (; item.IsOk(); item = ui->m_treeListRes->GetNextSibling(item)) {
        wxString name = ui->m_treeListRes->GetItemText(item);
        wxString path = ui->m_treeListRes->GetItemText(item, 1);
        wxString namePrefix, nameSuffix;
        SplitPathAndFilename(name, &namePrefix, &nameSuffix);

        if (namePrefix.IsEmpty())
            cmd += "-b \"" + path + "\" ";
        else
            cmd += "-r \"" + namePrefix + "\" \"" + path + "\" ";
    }

    cmd.Trim();

    wxArrayString output, error;
    long code = wxExecute(cmd, output, error, wxEXEC_SYNC);
    if (code != 0) {
        wxMessageBox("rescue not found!", "error", wxOK | wxICON_ERROR);
        return;
    }

    if (!error.IsEmpty()) {
        wxString msg;
        for (auto &v : error) msg += v + "\n";
        wxMessageBox(msg, "error", wxOK | wxICON_ERROR);
    }
    else {
        wxMessageBox("generate success!", "success", wxOK | wxICON_INFORMATION);
    }
}


void MainWin::OnUpdateBtnClicked(wxCommandEvent &WXUNUSED(e))
{
    auto path = ui->m_filePickerRes->GetPath();
    auto name = ui->m_textRelative->GetValue();

    if (path.empty() || name.empty()) {
        wxMessageBox("path or name is empty!", "error", wxOK | wxICON_ERROR);
        return;
    }

    auto curItem = ui->m_treeListRes->GetSelection();
    if (!curItem.IsOk() || curItem == ui->m_treeListRes->GetFirstItem()) {
        wxMessageBox("can't update root item!", "error", wxOK | wxICON_ERROR);
        return;
    }

    ui->m_treeListRes->SetItemText(curItem, name);
    ui->m_treeListRes->SetItemText(curItem, 1, path);
    ui->m_treeListRes->SetSortColumn(0);  // sort
    ui->m_treeListRes->SetFocus();        // focus
}


void MainWin::OnTreeListResItemActivated(wxTreeListEvent &e)
{
    if (e.GetItem() == ui->m_treeListRes->GetFirstItem()) {
        ConfigSet config(this);
        wxString functionPrefix = ui->m_treeListRes->GetItemText(ui->m_treeListRes->GetFirstItem());
        wxString sourcePath     = ui->m_treeListRes->GetItemText(ui->m_treeListRes->GetFirstItem(), 1);
        config.SetFunctionPrefix(functionPrefix);
        config.SetSourcePath(sourcePath);
        config.Center();
        if (config.ShowModal() == wxID_OK) {
            config.GetFunctionPrefix(&functionPrefix);
            config.GetSourcePath(&sourcePath);
            ui->m_treeListRes->SetItemText(ui->m_treeListRes->GetFirstItem(), functionPrefix);
            ui->m_treeListRes->SetItemText(ui->m_treeListRes->GetFirstItem(), 1, sourcePath);
        }
    }
    else {
        auto name = ui->m_treeListRes->GetItemText(e.GetItem());
        auto path = ui->m_treeListRes->GetItemText(e.GetItem(), 1);
        ui->m_filePickerRes->SetPath(path);
        ui->m_textRelative->SetValue(name);
        ui->m_textRelative->SetFocus();
    }

    e.Skip();
}


void MainWin::OnTextCtrlFilenameEnter(wxCommandEvent &e)
{
    OnUpdateBtnClicked(e);
    e.Skip();
}


void MainWin::OnTreeListResSetFocus(wxFocusEvent &e)
{
    ui->m_filePickerRes->SetPath(wxEmptyString);
    ui->m_textRelative->Clear();
    e.Skip();
}


void MainWin::ClearAll()
{
    auto item = ui->m_treeListRes->GetFirstChild(ui->m_treeListRes->GetFirstItem());
    while (item.IsOk()) {
        ui->m_treeListRes->DeleteItem(item);
        item = ui->m_treeListRes->GetFirstChild(ui->m_treeListRes->GetFirstItem());
    }

    ui->m_filePickerRes->SetPath(wxEmptyString);
    ui->m_textRelative->Clear();

    m_resProjectPath = wxEmptyString;
    ui->m_treeListRes->SetItemText(ui->m_treeListRes->GetFirstItem(), wxT(FUNCTION_PREFIX));
    ui->m_treeListRes->SetItemText(ui->m_treeListRes->GetFirstItem(), 1, wxT(SOURCE_PATH));
}


wxString MainWin::GetJsonByTreeListData()
{
    using namespace rapidjson;
    Document doc;
    doc.SetArray();

    Value cfg(kObjectType);
    wxString functionPrefix = ui->m_treeListRes->GetItemText(ui->m_treeListRes->GetFirstItem());
    wxString sourcePath     = ui->m_treeListRes->GetItemText(ui->m_treeListRes->GetFirstItem(), 1);
    cfg.AddMember("prefix", Value(functionPrefix, doc.GetAllocator()).Move(), doc.GetAllocator());
    cfg.AddMember("source_path", Value(sourcePath, doc.GetAllocator()).Move(), doc.GetAllocator());
    doc.PushBack(cfg, doc.GetAllocator());

    auto firstItem = ui->m_treeListRes->GetFirstItem();
    auto item      = ui->m_treeListRes->GetFirstChild(firstItem);
    while (item.IsOk()) {
        Value v(kObjectType);
        auto name = ui->m_treeListRes->GetItemText(item).ToUTF8().data();
        auto path = ui->m_treeListRes->GetItemText(item, 1).ToUTF8().data();
        v.AddMember("name", Value(name, doc.GetAllocator()).Move(), doc.GetAllocator());
        v.AddMember("path", Value(path, doc.GetAllocator()).Move(), doc.GetAllocator());
        doc.PushBack(v, doc.GetAllocator());
        item = ui->m_treeListRes->GetNextSibling(item);
    }

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    doc.Accept(writer);
    return wxString::FromUTF8(buffer.GetString());
}


void MainWin::SplitPathAndFilename(const wxString &pathAndFilename, wxString *path, wxString *filename)
{
    auto pos = pathAndFilename.find_last_of(wxFileName::GetPathSeparator());
    if (pos == wxString::npos) {
        *path     = wxEmptyString;
        *filename = pathAndFilename;
    }
    else {
        *path     = pathAndFilename.substr(0, pos);
        *filename = pathAndFilename.substr(pos + 1);
    }
}
