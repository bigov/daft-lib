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
    //signals
    void on_chexkbox_editable_toggled();
    void on_checkbox_visibility_toggled();
    void on_button_close();

    Gtk::Box mHBox { Gtk::ORIENTATION_HORIZONTAL };
    Gtk::Box mVBox { Gtk::ORIENTATION_VERTICAL };
    Gtk::Entry mEntry {};
    Gtk::CheckButton
      mCheckButtonEditable {"Editable"},
      mCheckButtonVisible {"Visible"};
    Gtk::Button mButtonClose {"Close"};
 };

#endif //APPWIN_HPP

