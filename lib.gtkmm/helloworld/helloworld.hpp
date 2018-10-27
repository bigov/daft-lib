#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <gtkmm.h>

class hello_world : public Gtk::Window
{
  public:
    hello_world();
    virtual ~hello_world();

  protected:
    //Signal handlers:
    void on_button_clicked();

    //Member wiget:
    Gtk::Box WinBox {Gtk::ORIENTATION_VERTICAL};
    Gtk::Button mButton;
    Gtk::Label InfoLabel {};
};

#endif // HELLOWORLD_H
