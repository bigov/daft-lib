/* filename: main.cpp (gtkmm example)
 *
 */
#include <iostream>
#include <gtkmm.h>

class hw: public Gtk::Window
{
  public:
    hw(int, int);
    virtual ~hw(void);

  protected:
    Gtk::Box mBox     {};
    Gtk::Frame mFrame {};
    Gtk::Button mBtn1 {};
    Gtk::Button mBtn2 {};

    void sig_b1(void);
    void sig_b2(void);
};

hw::~hw(void)
{
  return;
}

hw::hw(int w, int h)
{
  set_border_width(8);
  set_default_size(w, h);

  mBtn1.signal_clicked().connect(sigc::mem_fun(*this, sig_b1));
  mBtn1.add_pixlabel("open.xpm", "open");

  mBtn2.signal_clicked().connect(sigc::mem_fun(*this, sig_b2));
  mBtn2.add_label("_HELLO!", true);

  mFrame.set_label(" framed location ");
  mFrame.add(mBox);

  mBox.set_border_width(8);
  mBox.pack_start(mBtn1);
  mBox.pack_start(mBtn2);

  add(mFrame);
  show_all_children();

  return;
}

void hw::sig_b1(void)
{
  std::cout << "Need to open file?\n";
  return;
}

void hw::sig_b2(void)
{
  std::cout << "Hello, all!\n";
  return;
}

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv, "gtkmm.example");
  hw Win {200, 100};
  return app->run(Win);
}
