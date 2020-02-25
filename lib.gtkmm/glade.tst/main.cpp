/* Filename: main.cpp
 *
 */
#include <gtkmm.h>
#include <iostream>

Gtk::Window* win0 = nullptr;

static void close_app()
{
  if(win0) win0->hide();
  return;
}

int main(int argc, char** argv)
{
  Glib::RefPtr<Gtk::Application>
    app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  //Load the GtkBuilder file and instantiate its widgets:
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("../win0.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch(...)
  {
    std::cerr << "FAILURE: undefined exception.\n";
    return EXIT_FAILURE;
  }

  refBuilder->get_widget("myWindow", win0);
  if(win0)
  {
    win0->set_size_request(300, 200);
    win0->set_border_width(10);
    Gtk::Button* myButton = nullptr;
    refBuilder->get_widget("myButton", myButton);
    if(myButton)
      myButton->signal_clicked().connect(sigc::ptr_fun(close_app));
    win0->show_all_children();
    app->run(*win0);
  }

  delete win0;
  std::cout << "complete\n";

  return EXIT_SUCCESS;
}
