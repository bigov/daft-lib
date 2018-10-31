/* Filename: appwin.cpp
 *
 */
#include "appwin.hpp"

app_win::app_win(void)
{
  //set_size_request(200, 200);
  set_title("demo");
  set_border_width(8);
  add(Frame);
  Frame.add(BoxVert);
  Frame.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
  BoxVert.set_border_width(4);


  BoxVert.add(m_InfoBar);
  BoxVert.add(TextView);
  BoxVert.add(BtnQuit);

 TextView.set_size_request(300, 200);

  auto Con = dynamic_cast<Gtk::Container*>(m_InfoBar.get_content_area());
  Con->add(m_Message_Label);
  m_Message_Label.set_text("Information support service.");
  m_InfoBar.add_button("_OK", 0);

  BtnQuit.signal_clicked().connect(sigc::mem_fun(*this,
              &app_win::hide) );

  show_all();
  return;
}

