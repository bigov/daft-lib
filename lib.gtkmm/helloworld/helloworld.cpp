#include "helloworld.hpp"
#include <iostream>

hello_world::hello_world() : mButton("Hello World")
{
  set_border_width(10);

  mButton.signal_clicked().connect(sigc::mem_fun(*this, 
      &hello_world::on_button_clicked));

  add(mButton);
  mButton.show();
}

hello_world::~hello_world() { }

void hello_world::on_button_clicked()
{
  std::cout << "Hello-button is cliked" << std::endl;
  return;
}
