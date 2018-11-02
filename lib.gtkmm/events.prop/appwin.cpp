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
  BoxMain.add(mGrid);

  mGrid.set_orientation(Gtk::ORIENTATION_VERTICAL);
  mGrid.add(mLabel);
  mGrid.add(mEntry);
  mGrid.add(BtnCheck);

  BtnCheck.set_active();

  add_events(Gdk::KEY_RELEASE_MASK);

  mEntry.signal_key_release_event().connect(
    sigc::mem_fun(*this, &app_win::entryKeyRelease));

  mGrid.signal_key_release_event().connect(
    sigc::mem_fun(*this, &app_win::gridKeyRelease));

  signal_key_release_event().connect(sigc::mem_fun(*this, &app_win::windowKeyReleaseBefore), false);
  signal_key_release_event().connect(sigc::mem_fun(*this, &app_win::windowKeyRelease));

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

///
//
//
bool app_win::entryKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Entry" << std::endl;

  if(BtnCheck.get_active())
  {
    return false;
  }

  return true;
}

///
//
//
bool app_win::gridKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Grid" << std::endl;

  //Let it propagate:
  return false;
}

///
//
//
bool app_win::windowKeyReleaseBefore(GdkEventKey* /* event */ )
{
  std::cout << "Window before" << std::endl;
  return false;
}

///
//
//
bool app_win::on_key_release_event(GdkEventKey* key_event)
{
  std::cout << "Window overridden" << std::endl;

  // call base class function (to get the normal behaviour)
  return Gtk::Window::on_key_release_event(key_event);
}

//
// This will set the entry's text in the label, every time a key is pressed.
//
bool app_win::windowKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Window after";

  //checking if the entry is on focus, otherwise the label would get changed by pressing keys
  //on the window (when the entry is not on focus), even if m_checkbutton_can_propagate wasn't active
  if(mEntry.has_focus())
  {
    mLabel.set_text(mEntry.get_text());
    std::cout << ", " << mEntry.get_text();
  }
  std::cout << std::endl;

  return true;
}
