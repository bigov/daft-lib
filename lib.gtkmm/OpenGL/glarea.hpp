#ifndef GLAREA_HPP
#define GLAREA_HPP

#include <iostream>
#include <string>
#include <vector>

#include <gtkmm.h>
#include <giomm/resource.h>
#include <epoxy/gl.h>

extern bool render_gl_content(const Glib::RefPtr<Gdk::GLContext>&);

class win_gl : public Gtk::Window
{
public:
  win_gl();
  ~win_gl() {};

protected:
  Gtk::Box    MainBox  { Gtk::ORIENTATION_VERTICAL, false };
  Gtk::GLArea WinGlArea  { };
  Gtk::Button BtnQuit { "Quit" };
  bool on_timer(int);
};

#endif // GLAREA_HPP
