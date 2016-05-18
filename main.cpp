#include <fstream>
#include <string>
#include "main.hpp"
#include "gui.hpp"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
    MainFrame* main_window = new MainFrame(NULL);
    this->SetTopWindow(main_window);
    reinterpret_cast<MainFrame*>(this->GetTopWindow())->initialize_frame();
    return true;
}
