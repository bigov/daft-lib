/* Filename: appwin.cpp
 *
 */
#include "appwin.hpp"

///
/// Инициализация (главного) окна приложения
///
app_win::app_win(void)
{
  set_size_request(500, 300);
  set_title("gtkmm demo");
  set_border_width(10);

  add(BoxMain);
  BoxMain.pack_end(BoxBtns, Gtk::PACK_SHRINK);

  BoxBtns.set_layout(Gtk::BUTTONBOX_END);
  BoxBtns.set_spacing(10);
  BoxBtns.add(BtnOk);
  BoxBtns.add(BtnClose);

  BtnOk.signal_clicked().connect(sigc::mem_fun(*this, hide));
  BtnClose.signal_clicked().connect(sigc::mem_fun(*this, hide));

  show_all_children();
  return;
}

///
/// Настраиваемый перехватчик событий клавиатуры
///
bool app_win::on_key_press_event(GdkEventKey* event)
{
  if(event->keyval == GDK_KEY_Escape)
  {
    hide();
    return true;
  }
  return Gtk::Window::on_key_press_event(event);
}
