#include <wx/wx.h>
#include "mainwin/mainwin.h"

class MyApp : public wxApp
{
    bool OnInit() override
    {
        auto *app = new MainWin();
        app->Show();
        app->Center();
        return true;
    }
};


wxIMPLEMENT_APP(MyApp);  // NOLINT
