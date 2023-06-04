/**
 * @file      configset.h
 * @brief     Configure the Settings dialog box
 * @author    Xiao Ley(xiao.ley\@outlook.com)
 * @date      2023-05-31
 * @version   0.1
 * @copyright Copyright (c) 2023 Xiao Ley. All rights reserved.
 **********************************************************************************
 * @par Change Log:
 * <table>
 *     <tr><th>Date         <th>Version  <th>Author   <th>Description</tr>
 *     <tr><td>2023-05-31   <td>0.1      <td>Xiao Ley <td>Create an initial version</tr>
 * </table>
 **********************************************************************************
 */

#ifndef RESCUE_GUI_CONFIGSET_H__
#define RESCUE_GUI_CONFIGSET_H__

#include <wx/wx.h>
#include "common.h"
#include "configset_ui.h"

class ConfigSet final : public wxDialog
{
public:
    explicit ConfigSet(wxWindow *parent);
    ~ConfigSet() final;

    void SetFunctionPrefix(const wxString &functionPrefix);
    void GetFunctionPrefix(wxString *functionPrefix);

    void SetSourcePath(const wxString &sourcePath);
    void GetSourcePath(wxString *sourcePath);

protected:

private:
    UI::ConfigSet *ui;

    wxDECLARE_EVENT_TABLE();
};

#endif  //! RESCUE_GUI_CONFIGSET_H__
