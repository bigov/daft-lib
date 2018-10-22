/* gtkmm example
 *
 */
#include <gtkmm.h>

int main(int argc, char* argv[])
{
  auto app =
    Gtk::Application::create(argc, argv, "gtkmm.example");

  Gtk::Window window;
  window.set_border_width(8);
  Gtk::Frame m_frame;
  Gtk::Box m_box;
  Gtk::Button m_Button1("hi");
  Gtk::Button m_Button2("by");

  window.set_default_size(200, 200);
  m_frame.set_label(" framed location ");
  m_box.set_border_width(8);

  m_box.pack_start(m_Button1);
  m_box.pack_start(m_Button2);

  m_frame.add(m_box);
  window.add(m_frame);
  window.show_all_children();
  return app->run(window);
}
