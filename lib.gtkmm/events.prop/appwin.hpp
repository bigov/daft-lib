/* Filename: appwin.hpp
 *
 */
#ifndef APPWIN_HPP
#define APPWIN_HPP
#include <iostream>
#include <gtkmm.h>

class app_win : public Gtk::Window
{
  public:
    app_win();
    virtual ~app_win() {}

  protected:
    Gtk::Box BoxMain {Gtk::ORIENTATION_VERTICAL};
    Gtk::ButtonBox BoxBtns {Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Button BtnClose{"Close"};
    Gtk::Button BtnOk   {"Ok"   };

    Gtk::Grid        mGrid    { };
    Gtk::Label       mLabel   { "A LABEL" };
    Gtk::Entry       mEntry   { };
    Gtk::CheckButton BtnCheck { "Allow propagate" };

  private:
    //Override default signal handler:
    bool on_key_press_event     (GdkEventKey* event) override;
    bool on_key_release_event   (GdkEventKey* event) override;

    bool entryKeyRelease        (GdkEventKey* event);
    bool gridKeyRelease         (GdkEventKey* event);
    bool windowKeyReleaseBefore (GdkEventKey* event);
    bool windowKeyRelease       (GdkEventKey* event);

};

#endif //APPWIN_HPP

