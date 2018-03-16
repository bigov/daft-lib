/*
Немного теории

# Контрольные циклы

Можно создавать необходимое число контрольных циклов для обработки различных
событий (TODO: уточнить в документации особенности uv_default_loop()). Цикл
создается вызовом функции с указанием выделеного блока памяти:

```
  std::vector<uv_loop_t> vL(sizeof(uv_loop_t));
  uv_loop_t *loop = vL.data();

```
А можно использовать (один) дефолтный цикл:

```
  uv_loop_t *loop = uv_default_loop();

```
*/
#include <uv.h>
#include <iostream>
#include <vector>

void wait_for_a_while(uv_idle_t* handle)
{
  static int64_t counter = 0;
  static int64_t c1 = 0;
  static int echo = 0;

  counter++;
  if (counter >= 10e6) uv_idle_stop(handle);

  c1++;
  if (c1 > 1e6)
  {
    std::cout << ++echo << "\n";
    c1 = 0;
  }

  return;
}


int main() {

  //std::vector<uv_loop_t> vL(sizeof(uv_loop_t));
  //uv_loop_t *loop = vL.data();
  uv_loop_t *loop = uv_default_loop();

  uv_idle_t idler;                         // обработчик задежки
  uv_idle_init(loop, &idler);
  uv_idle_start(&idler, wait_for_a_while); // регистрация функции обработчика
  
  uv_run(loop, UV_RUN_DEFAULT);
  uv_loop_close(loop);

  return 0;
}
