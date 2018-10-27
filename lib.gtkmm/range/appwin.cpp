/* Filename: appwin.cpp
 *
 */
#include <iostream>
#include "appwin.hpp"

///
/// Конструктор класса
///
app_win::app_win()
{
  set_title("range controls");
  set_default_size(300, 350);

  //VScale:
  m_VScale.set_digits(1);
  m_VScale.set_value_pos(Gtk::POS_TOP);
  m_VScale.set_draw_value();
  m_VScale.set_inverted(); // highest value at top

  //HScale:
  m_HScale.set_digits(1);
  m_HScale.set_value_pos(Gtk::POS_TOP);
  m_HScale.set_draw_value();

  add(m_VBox_Top);
  m_VBox_Top.pack_start(m_VBox2);
  m_VBox2.set_border_width(10);
  m_VBox2.pack_start(m_HBox_Scales);

  //Put VScale and HScale (above scrollbar) side-by-side.
  m_HBox_Scales.pack_start(m_VScale);
  m_HBox_Scales.pack_start(m_VBox_HScale);

  m_VBox_HScale.pack_start(m_HScale);
  m_VBox_HScale.pack_start(m_Scrollbar);

  //CheckButton:
  m_CheckButton.set_active();
  m_CheckButton.signal_toggled().connect(
    sigc::mem_fun(*this, &app_win::on_checkbutton_toggled) );
  m_VBox2.pack_start(m_CheckButton, Gtk::PACK_SHRINK);

  //Position ComboBox:
  //Create the Tree model:
  ComboBoxPosition.set_model(refTreeColumns);
  ComboBoxPosition.pack_start(TreeColumns.ColTitle);

  //Fill the ComboBox's Tree Model:
  Gtk::TreeModel::Row row = *(refTreeColumns->append());
  row[TreeColumns.PosType] = Gtk::POS_TOP;
  row[TreeColumns.ColTitle] = "Top";

  row = *(refTreeColumns->append());
  row[TreeColumns.PosType] = Gtk::POS_BOTTOM;
  row[TreeColumns.ColTitle] = "Bottom";

  row = *(refTreeColumns->append());
  row[TreeColumns.PosType] = Gtk::POS_LEFT;
  row[TreeColumns.ColTitle] = "Left";

  row = *(refTreeColumns->append());
  row[TreeColumns.PosType] = Gtk::POS_RIGHT;
  row[TreeColumns.ColTitle] = "Right";

  m_VBox2.pack_start(m_HBox_Combo, Gtk::PACK_SHRINK);
  m_HBox_Combo.pack_start(
    *Gtk::manage(new Gtk::Label("Scale Value Position:", 0)), Gtk::PACK_SHRINK);
  m_HBox_Combo.pack_start(ComboBoxPosition);
  ComboBoxPosition.signal_changed().connect(
    sigc::mem_fun(*this, &app_win::on_combo_position) );
  ComboBoxPosition.set_active(0); // Top

  //Digits:
  m_HBox_Digits.pack_start(
    *Gtk::manage(new Gtk::Label("Scale Digits:", 0)), Gtk::PACK_SHRINK);
  m_Scale_Digits.set_digits(0);
  m_adjustment_digits->signal_value_changed().connect(
    sigc::mem_fun(*this, &app_win::on_adjustment1_value_changed));
  m_HBox_Digits.pack_start(m_Scale_Digits);

  //Page Size:
  m_HBox_PageSize.pack_start(
    *Gtk::manage(new Gtk::Label("Scrollbar Page Size:", 0)), Gtk::PACK_SHRINK);
  m_Scale_PageSize.set_digits(0);
  m_adjustment_pagesize->signal_value_changed().connect(
    sigc::mem_fun(*this, &app_win::on_adjustment2_value_changed));
  m_HBox_PageSize.pack_start(m_Scale_PageSize);

  m_VBox2.pack_start(m_HBox_Digits, Gtk::PACK_SHRINK);
  m_VBox2.pack_start(m_HBox_PageSize, Gtk::PACK_SHRINK);
  m_VBox_Top.pack_start(m_Separator, Gtk::PACK_SHRINK);
  m_VBox_Top.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);

  m_Button_Quit.set_can_default();
  m_Button_Quit.grab_default();
  m_Button_Quit.signal_clicked().connect(
        sigc::mem_fun(*this, &app_win::on_button_quit));
  m_Button_Quit.set_border_width(10);

  show_all_children();
}

///
/// \brief app_win::on_checkbutton_toggled
///
void app_win::on_checkbutton_toggled()
{
  m_VScale.set_draw_value(m_CheckButton.get_active());
  m_HScale.set_draw_value(m_CheckButton.get_active());
}

///
/// \brief app_win::on_combo_position
///
void app_win::on_combo_position()
{
  Gtk::TreeModel::iterator iter = ComboBoxPosition.get_active();
  if(!iter) return;

  Gtk::TreeModel::Row row = *iter;
  if(!row) return;

  const Gtk::PositionType postype = row[TreeColumns.PosType];

  m_VScale.set_value_pos(postype);
  m_HScale.set_value_pos(postype);

  return;
}

///
/// \brief app_win::on_adjustment1_value_changed
///
void app_win::on_adjustment1_value_changed()
{
  auto val = static_cast<int>( m_adjustment_digits->get_value());
  m_VScale.set_digits( val );
  m_HScale.set_digits( val );
  return;
}

///
/// \brief app_win::on_adjustment2_value_changed
///
void app_win::on_adjustment2_value_changed()
{
  const double val = m_adjustment_pagesize->get_value();
  m_adjustment->set_page_size(val);
  m_adjustment->set_page_increment(val);

  // Note that we don't have to emit the "changed" signal
  // because gtkmm does this for us.
}

///
/// \brief app_win::on_button_quit
///
void app_win::on_button_quit()
{
  hide();
  return;
}
