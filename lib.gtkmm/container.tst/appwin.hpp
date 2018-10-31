/* Filename: appwin.hpp
 *
 */
#ifndef APPWIN_HPP
#define APPWIN_HPP
//#include <iostream>
#include <gtkmm.h>

class app_win : public Gtk::Window
{
  public:
    app_win();
    ~app_win() {}

  protected:
    Gtk::Box BoxVert{Gtk::ORIENTATION_VERTICAL};
    Gtk::Frame Frame {};
    Gtk::TextView TextView {};
    Gtk::InfoBar m_InfoBar {};
    Gtk::Label m_Message_Label {};
    Gtk::Button BtnQuit {"Закрыть"};
 };

#endif //APPWIN_HPP

