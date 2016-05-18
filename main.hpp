#ifndef __MAIN_H__
#define __MAIN_H__

#include <wx/wx.h>

class MainApp : public wxApp
{
public:
    virtual bool OnInit();
};

DECLARE_APP(MainApp)

#endif
