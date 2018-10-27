#include "helloworld.hpp"
#include <iostream>

hello_world::hello_world() : mButton("Hello World")
{
  set_border_width(10);

  mButton.signal_clicked().connect(sigc::mem_fun(*this, 
      &hello_world::on_button_clicked));

  add(WinBox);
  WinBox.set_border_width(4);

  WinBox.pack_start(InfoLabel);
  InfoLabel.set_markup("First <b>Hello Word</b> application\n");

  WinBox.pack_start(mButton);

  show_all();
}

hello_world::~hello_world() { }

void hello_world::on_button_clicked()
{
  std::cout << "Hello-button is cliked" << std::endl;
  return;
}
