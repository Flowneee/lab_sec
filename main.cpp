/**
 * lab_sec
 * Copyright (C) 2016  Kononov Andrey <flowneee@protonmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
