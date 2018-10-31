/* Filename: main.cpp
 *
 */
#include "appwin.hpp"

int main(int argc, char* argv[])
{
  auto MyApp = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  app_win AppWin {}; return MyApp->run(AppWin);
}
