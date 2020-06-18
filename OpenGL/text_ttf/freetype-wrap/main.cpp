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

//  tr::wft_face FontFace {"../font/DejaVu Sans Mono for Powerline.ttf"};
  tr::wft_face FontFace {"../font/LiberationSans-Regular.ttf"};
  FontFace.set_pixel_size(0, 15);

  auto Bitmap = FontFace.make_bitmap_text("Привет вам, друзья!");

  size_t border = 20;
  size_t i = 0;                                // число скопированных пикселей
  size_t i_max = Bitmap.width * Bitmap.height; // число пикселей источника
  size_t src_start = 0;
  size_t dst_start = bytes_per_pixel * (border + border * win_width);
  std::vector<unsigned char> texture(image_size * bytes_per_pixel, 0xFF);

  while(i < i_max)
  {
    size_t row_n = Bitmap.width;
    size_t dst = dst_start;
    size_t src = src_start;
    while(row_n > 0)
    {
      uint8_t c = Bitmap.Bits[src];
      texture[dst + 0] = 0x20;
      texture[dst + 1] = 0x20;
      texture[dst + 2] = 0x20;
      texture[dst + 3] = c;
      dst += 4;
      src += 1;
      row_n -= 1;
      i += 1;
    }
    src_start += Bitmap.width;                      // переход на начало следующей строки источника
    dst_start += win_width * bytes_per_pixel; // переход на начало следующей строки приемника
  }

  // Сохраняем изображение в PNG формате с прозрачностью
  savePNG(Bitmap.Bits.data(), Bitmap.width, Bitmap.height);
  opengl_window_show(texture.data(), win_width, win_height);
  exit(EXIT_SUCCESS);
}

