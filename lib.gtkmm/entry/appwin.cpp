/* Filename: appwin.cpp
 *
 */
#include "appwin.hpp"

app_win::app_win(void)
{
  set_size_request(200, 100);
  set_title("Gtk::Entry example");
  set_border_width(8);

  add(mVBox);

  mEntry.set_max_length(50);
  mEntry.set_text("Hello");
  mEntry.set_text(mEntry.get_text() + " world");
  mEntry.select_region(0, 4);

  mVBox.add(mEntry);
  mVBox.add(mHBox);
  mHBox.set_border_width(8);

  mHBox.add(mCheckButtonEditable);
  mCheckButtonEditable.signal_toggled().connect(
    sigc::mem_fun(*this, &app_win::on_chexkbox_editable_toggled));
  mCheckButtonEditable.set_active(true);

  mHBox.add(mCheckButtonVisible);
  mCheckButtonVisible.signal_toggled().connect(
    sigc::mem_fun(*this, &app_win::on_checkbox_visibility_toggled));
  mCheckButtonVisible.set_active(true);

  mVBox.add(mButtonClose);
  mButtonClose.signal_clicked().connect(
    sigc::mem_fun(*this, &app_win::on_button_close));
  mButtonClose.set_can_default();
  mButtonClose.grab_default();

  show_all_children();

  return;
}

void app_win::on_checkbox_visibility_toggled(void)
{
  mEntry.set_visibility(mCheckButtonVisible.get_active());
  return;
}

void app_win::on_chexkbox_editable_toggled(void)
{
  mEntry.set_editable(mCheckButtonEditable.get_active());
  return;
}

void app_win::on_button_close(void)
{
  hide();
  return;
}

