#ifndef GTKMM_EXAMPLE_IDLEEXAMPLE_H
#define GTKMM_EXAMPLE_IDLEEXAMPLE_H

#include <gtkmm.h>
#include <iostream>

class IdleExample : public Gtk::Window
{
public:
  IdleExample();

protected:
  // Signal Handlers:
  bool on_timer();
  bool on_idle();
  void on_button_clicked();

  // Member data:
  Gtk::Box m_Box {Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::Button m_ButtonQuit { "_Quit", true };
  Gtk::ProgressBar m_ProgressBar_c {};
  Gtk::ProgressBar m_ProgressBar_d {};
};

#endif // GTKMM_EXAMPLE_IDLEEXAMPLE_H

