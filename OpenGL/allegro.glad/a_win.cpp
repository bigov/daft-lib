#include "a_win.hpp"

ALLEGRO_DISPLAY*     display = nullptr;
ALLEGRO_EVENT        event = {};
ALLEGRO_EVENT_QUEUE* queue = nullptr;
ALLEGRO_TIMER*       timer = nullptr;

//### Создание окна
void window_create(void)
{
  if(!al_init()) ERR("failed to initialize allegro!\n");

  uint32_t version = al_get_allegro_version();
  unsigned int major = version >> 24;
  unsigned int minor = (version >> 16) & 255;
  unsigned int revision = (version >> 8) & 255;
  unsigned int release = version & 255;
  std::cout << "Allegro version: "
    << major << "." << minor << "." << revision << "." << release << "\n";

  al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED
                         | ALLEGRO_RESIZABLE);
  al_set_new_display_option(ALLEGRO_OPENGL_MAJOR_VERSION, 3, ALLEGRO_REQUIRE);
  al_set_new_display_option(ALLEGRO_OPENGL_MINOR_VERSION, 2, ALLEGRO_REQUIRE);

  display = al_create_display(640, 480); 
  if(nullptr == display) ERR ("failed to create display!\n");
  al_set_current_opengl_context(display);

  al_install_keyboard();
  timer = al_create_timer(1.0 / 30.0);
  queue = al_create_event_queue();
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_timer_event_source(timer));

  std::cout<<"al opengl version: "
    << std::hex << al_get_opengl_version() << std::endl;

  std::cout << "disp options: OPENGL_MAJOR = "
  << al_get_display_option(display, ALLEGRO_OPENGL_MAJOR_VERSION) << ", "
  << "OPENGL_MINOR = "
  << al_get_display_option(display, ALLEGRO_OPENGL_MINOR_VERSION) << "\n";

  return;
}

//### Оконный цикл
void window_update(void)
{
  al_flip_display();
  al_wait_for_event(queue, &event);
  return;
}

//### Очистка памяти
void window_destroy(void)
{
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  return;
}

bool window_run(void)
{
  return !((event.type == ALLEGRO_EVENT_KEY_DOWN) ||
           (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE));
}

