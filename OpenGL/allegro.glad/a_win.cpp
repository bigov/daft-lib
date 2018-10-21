#include "a_win.hpp"

ALLEGRO_DISPLAY*     display = nullptr;
ALLEGRO_EVENT        event = {};
ALLEGRO_EVENT_QUEUE* queue = nullptr;
ALLEGRO_TIMER*       timer = nullptr;

//### Создание окна
void window_create(void)
{
  if(!al_init()) ERR("failed to initialize allegro!\n");
  al_install_keyboard();
  timer = al_create_timer(1.0 / 30.0);
  queue = al_create_event_queue();
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_timer_event_source(timer));

  al_set_new_display_flags(ALLEGRO_OPENGL);
  al_set_new_display_option(ALLEGRO_OPENGL_MAJOR_VERSION, 3, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_OPENGL_MINOR_VERSION, 2, ALLEGRO_SUGGEST);
  display = al_create_display(640, 480);
  if(nullptr == display) ERR ("failed to create display!\n");
  al_set_current_opengl_context(display);

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

