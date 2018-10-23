#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>

void show_msg(const char* msg)
{
  al_show_native_message_box( nullptr, "Native message app info", "",
    msg, NULL, 0 );
  return;
}

int main(int, char**)
{
  //show_msg("Start Allegro\n");
  if(!al_init())
  {
    show_msg("couldn't initialize allegro\n");
    return 1;
  }
  ALLEGRO_TEXTLOG* textlog = al_open_native_text_log("app log",
    ALLEGRO_TEXTLOG_MONOSPACE | ALLEGRO_TEXTLOG_NO_CLOSE);
  al_append_native_text_log(textlog, "initialize allegro\n");

  if(!al_install_keyboard())
  {
    show_msg("couldn't initialize keyboard\n");
    return 1;
  }

  ALLEGRO_TIMER* timer = al_create_timer(1.0f / 30.0f);
  if(!timer)
  {
    show_msg("couldn't initialize timer\n");
    return 1;
  }

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  if(!queue)
  {
    show_msg("couldn't initialize queue\n");
    return 1;
  }

  ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
  if(!disp)
  {
    show_msg("couldn't initialize display\n");
    return 1;
  }

  ALLEGRO_FONT* font = al_create_builtin_font();
  if(!font)
  {
    show_msg("couldn't initialize font\n");
    return 1;
  }

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_timer_event_source(timer));

  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;

  al_start_timer(timer);
  while(!done)
  {
    al_wait_for_event(queue, &event);
    switch(event.type)
    {
      case ALLEGRO_EVENT_TIMER:
          // game logic goes here.
          redraw = true;
          break;
      case ALLEGRO_EVENT_KEY_DOWN:
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
          done = true;
          break;
    }

    if(redraw && al_is_event_queue_empty(queue))
    {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
      al_flip_display();
      redraw = false;
    }
  }

  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  al_close_native_text_log(textlog);

  return 0;
}

  /*
  //#include <allegro5/allegro_ttf.h>

  if(!al_init()) show_msg("Can't init Allegro");
  ALLEGRO_DISPLAY* disp = al_create_display(320, 200);
  if(nullptr == disp) show_msg("Can't create display");
  al_rest(3.0f);


  if(!al_install_keyboard()) show_msg("Can't install keyboard");
  if(!al_init_ttf_addon()) show_msg("Can't init ttf addon");

  ALLEGRO_FONT* font = al_load_ttf_font("../DejaVuSansMono.ttf", 16, ALLEGRO_TTF_MONOCHROME);
  if(nullptr == font) show_msg("Error load font");

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  if(nullptr == timer) show_msg("Can't create timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  if(nullptr == queue) show_msg("Can't create event_queue");

  show_msg("Init complete");

  ALLEGRO_EVENT event;
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_timer_event_source(timer));

  bool redraw = true;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER) redraw = true;
        else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
        //else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
          break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(240, 240, 240));
            al_draw_text(font, al_map_rgb(16, 16, 16), 160, 90, ALLEGRO_ALIGN_CENTRE, "Hello, World!");
            al_flip_display();
            redraw = false;
        }
    }

  al_destroy_event_queue(queue);
  al_destroy_timer(timer);
  al_destroy_font(font);
  al_destroy_display(disp);
  */
