/* filename: a_win.hpp
 *
 */
#ifndef A_WIN_HPP
#define A_WIN_HPP

#include "main.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_opengl.h>

void window_create(void);
void window_update(void);
bool window_run(void);
void window_destroy(void);

#endif
