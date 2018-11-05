/* gtkmm example
 *
 */
#include <gtkmm.h>

class app_win: public Gtk::Window
{
  public:
    app_win();
    virtual ~app_win() {}

  protected:
    Gtk::Box m_box { Gtk::ORIENTATION_VERTICAL };
    Gtk::Label label { "Привет!\n" };
    Gtk::Button m_Button1 {"OK"};

  private:
    bool on_key_press_event (GdkEventKey* event) override;
};

app_win::app_win()
{
  set_border_width(10);
  add(m_box);
  m_box.set_border_width(10);
  m_box.add(label);
  m_box.pack_end(m_Button1, Gtk::PACK_SHRINK);
  m_Button1.signal_clicked().connect(sigc::mem_fun(*this, hide));
  show_all_children();
}

/// Обработчик нажатий клавиатуры
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

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv, "");
  app_win window {};
  return app->run(window);
}
