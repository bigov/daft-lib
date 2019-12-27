//
//
// Файл: main.cpp (FLTK 1.3 demo)
//
// Компилируется командой
//  g++ --static -std=c++11 `fltk-config --cxxflags` main.cpp `fltk-config --ldflags`
//
// Где конфиги выдают опции -
//
// $ fltk-config --cxxflags
//   -I/mingw64/include -mwindows -DWIN32 -DUSE_OPENGL32 -march=x86-64 -mtune=generic\
//   -O2 -pipe -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
//
// $ fltk-config --ldflags
// -L/mingw64/lib -mwindows -pipe -Wl,--enable-auto-import -Wl,--enable-runtime-pseudo-reloc \
//    -lfltk -lole32 -luuid -lcomctl32
//
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180);
  Fl_Box *box = new Fl_Box(0,0,340,180, "Привет из FLTK!");
  box->labelfont(FL_BOLD);
  box->labelsize(24);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
