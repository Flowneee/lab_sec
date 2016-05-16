#ifndef __MAIN_H__
#define __MAIN_H__

#include <wx/wx.h>

bool isRunFirstTime();

class MainApp : public wxApp
{
public:
    virtual bool OnInit();
};

DECLARE_APP(MainApp)

#endif
