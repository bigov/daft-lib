/* filename: main.cpp (gtkmm example)
 *
 */
#include <iostream>
#include <gtkmm.h>

class hw: public Gtk::Window
{
  public:
    hw(int, int);
    ~hw(void) {};

  protected:
    Gtk::Box mBoxExt {Gtk::ORIENTATION_VERTICAL};
    Gtk::Box mBoxIn1 {Gtk::ORIENTATION_VERTICAL, 10};
    Gtk::Box mBoxIn2 {Gtk::ORIENTATION_HORIZONTAL, 10};

    Gtk::RadioButton::Group Gr {};
    Gtk::RadioButton
        mRb1 {}, mRb2 {}, mRb3 {};

    Gtk::Separator mSeparator {};

    Gtk::Button mButtonCancel {};
    Gtk::Button mButtonAccept {};

    void on_close(void);
};

void hw::on_close(void)
{
  hide();
  return;
}

hw::hw(int w, int h)
{
  set_title("Примеры");
  set_default_size(w, h);
  set_border_width(8);
  add(mBoxExt);
  mBoxExt.pack_start(mBoxIn1);
  mBoxExt.pack_start(mSeparator);
  mBoxExt.pack_start(mBoxIn2);
  mBoxIn1.set_border_width(20);
  mBoxIn2.set_border_width(10);

  mRb1.set_label("пункт А");
  mRb1.set_group(Gr);

  mRb2.set_label("пункт Б");
  mRb2.set_group(Gr);

  mRb3.set_label("пункт В");
  mRb3.set_group(Gr);

  mBoxIn1.pack_start(mRb1);
  mBoxIn1.pack_start(mRb2);
  mBoxIn1.pack_start(mRb3);

  mButtonCancel.add_label("_Отмена", true);
  mButtonAccept.add_label("_Применить", true);
  mBoxIn2.pack_start(mButtonCancel);
  mBoxIn2.pack_start(mButtonAccept);

  mButtonCancel.set_can_default();
  mButtonCancel.grab_default();

  mButtonCancel.set_size_request(80, -1);
  mButtonAccept.set_size_request(80, -1);

  mButtonCancel.signal_clicked().connect(sigc::mem_fun(*this, on_close));
  mButtonAccept.signal_clicked().connect(sigc::mem_fun(*this, on_close));

  show_all_children();

  return;
}


int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv, "gtkmm.example");
  hw Win {180, 120};
  return app->run(Win);
}
