#include <functional>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Simple_Terminal.H>

Fl_Simple_Terminal *Tty = nullptr;
Fl_Input* Input = nullptr;

class History {
  public:
  void log (const char* msg){ Tty->printf( "%s\n", msg ); }
  void up  (void){ log("Up is pressed."); };
  void down(void){ log("Down is pressed."); };
  void add (const char* msg){ log(msg + 2); };
};

class MyInput : public Fl_Input {
    History hist;
public:
    template <typename...Args>
    MyInput(Args&&...args) : Fl_Input(std::forward<Args>(args)...) { }

    int handle(int ev) override {
       if (ev != FL_KEYDOWN) return Fl_Input::handle(ev);
       auto key = Fl::event_key();
       if (key == FL_Up) {
           hist.up();
           return 1;
       } else if (key == FL_Down) {
           hist.down();
           return 1;
       } else if (key == FL_Enter) {
           hist.add(value());
           value("$ ");
           return 1;
       }
       return Fl_Input::handle(ev);
    }
};

int main(int, char**) {
  int width = 500; int tty_h = 500; int inp_h = 24;
  Fl_Window *Win = new Fl_Window(width, tty_h + inp_h, "App");
  Win->begin();
  Tty = new Fl_Simple_Terminal(0, 0, width, tty_h);
  Input = new MyInput(0, tty_h - 3, width, inp_h, nullptr);
  Input->insert("$ ");
  Win->end();
  Win->resizable(Tty);
  Win->show();
  Fl::focus(Input);
  return Fl::run();
}

