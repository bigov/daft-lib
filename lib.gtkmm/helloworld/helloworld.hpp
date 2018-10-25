#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class hello_world : public Gtk::Window
{
  public:
    hello_world();
    virtual ~hello_world();

  protected:
    //Signal handlers:
    void on_button_clicked();

    //Member wiget:
    Gtk::Button mButton;
};

#endif // HELLOWORLD_H
