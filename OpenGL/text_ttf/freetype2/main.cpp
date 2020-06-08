#include <fstream>

#include "win.hpp"
#include "wft2.hpp"

using uchar = unsigned char;
using uint  = unsigned int;

uint32_t win_width = 400;
uint32_t win_height = 400;


///
/// \brief main
/// \return
///
int main(int, char**)
{
  size_t bytes_per_pixel = 4;
  auto image_size = static_cast<size_t>(win_width * win_height);

  tr::wft_face FontFace {"../font/DejaVu Sans Mono for Powerline.ttf"};
  FontFace.set_pixel_size(0, 48);

  tr::image ImG = FontFace.get_symbol(L'Й');
  //tr::image ImG = FontFace.get_symbols_row({L'.', L'В'}); //, L'а', L'с', L'я', L'!'});

  size_t border = 20;
  size_t i = 0;                        // число скопированных пикселей
  size_t i_max = ImG.width * ImG.rows; // число пикселей источника
  size_t src_start = 0;
  size_t dst_start = bytes_per_pixel * (border + border * win_width);
  std::vector<unsigned char> texture(image_size * bytes_per_pixel, 0xFF);

  while(i < i_max)
  {
    size_t row_n = ImG.width;
    size_t dst = dst_start;
    size_t src = src_start;
    while(row_n > 0)
    {
      uint8_t c = ImG.Bits[src];
      texture[dst + 0] = 0x20;
      texture[dst + 1] = 0x20;
      texture[dst + 2] = 0x20;
      texture[dst + 3] = c;
      dst += 4;
      src += 1;
      row_n -= 1;
      i += 1;
    }
    src_start += ImG.width;                      // переход на начало следующей строки источника
    dst_start += win_width * bytes_per_pixel; // переход на начало следующей строки приемника
  }

  // Сохраняем изображение в PNG формате с прозрачностью
  savePNG(ImG.Bits.data(), ImG.width, ImG.rows);
  opengl_window_show(texture.data(), win_width, win_height);
  exit(EXIT_SUCCESS);
}

