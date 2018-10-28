/* Filename: glarea.cpp
 *
 * Example using Gtk::GLArea - a widget that allows custom drawing
 * using OpenGL calls.
 *
 */
#include "glarea.hpp"

///----------------------------------------------------------------------------
/// \brief win_gl::win_gl
///
win_gl::win_gl()
{
  set_title("GL Area");
  set_default_size(550, 495);

  add(MainBox);
  MainBox.set_spacing(6);
  MainBox.add(WinGlArea);

  WinGlArea.set_hexpand(true);
  WinGlArea.set_vexpand(true);
  //Функция, вызываемая из "GLArea.queue_draw()"
  WinGlArea.signal_render().connect(sigc::ptr_fun(&render_gl_content));
  WinGlArea.set_auto_render(true);

  MainBox.add(BtnQuit);
  BtnQuit.signal_clicked().connect(sigc::mem_fun(*this, &win_gl::hide));

  // Init OpenGL content
  show_all();
  WinGlArea.make_current();

  // Create timer
  sigc::slot<bool> my_slot = sigc::bind(
        sigc::mem_fun(*this, &win_gl::on_timer), 0 );
  sigc::connection conn =
        Glib::signal_timeout().connect(my_slot, 50);

  return;
}

///----------------------------------------------------------------------------
/// \brief win_gl::on_timer
///
bool win_gl::on_timer(int)
{
  // Тут вызывается функция, привязанная в конструкторе класса
  // через вызов "WinGlArea.signal_render().connect(...)"
  WinGlArea.queue_draw();
  return true;
}
