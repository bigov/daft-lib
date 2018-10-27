/* Filename: main.cpp
 *
 */
#include <gtkmm/application.h>
#include "appwin.hpp"

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  app_win MyTests;
  return app->run(MyTests);
}
