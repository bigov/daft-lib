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
  const std::string exampleString("FreeType amazing!"); // Выводимая строка

  struct symbol_info
  {
    int32_t x = 0, y = 0;
    FT_Glyph Glyph {};
    FT_BitmapGlyph BitmapGlyph {};
  };

  size_t bytes_per_pixel = 4;
  auto image_size = static_cast<size_t>(win_width * win_height);
  std::vector<symbol_info> Text {};
  int32_t top = 0;
  uint32_t bottom = 0;
  uint32_t prev_char = 0;

  tr::wft_face FontFace {"../font/DejaVu Sans Mono for Powerline.ttf"};
  FontFace.set_pixel_size(0, 12);

  FT_Pos posX = 0; // Позиция текущего символа в формате FT_Pos - "26.6"
  for (size_t i = 0; i < exampleString.size(); ++i)
  {
      const uint32_t charcode = exampleString[i];
      Text.push_back( {0, 0, FontFace.get_glyph(charcode)} );
      auto& Symbol = Text.back();

      if (!Symbol.Glyph) continue; // Нужного глифа в шрифте может не оказаться
      Symbol.BitmapGlyph = FontFace.glyph_to_bitmap(Symbol.Glyph);
      posX += FontFace.get_kerning(prev_char, charcode);
      prev_char = charcode;
      Symbol.x = (posX >> 6) + Symbol.BitmapGlyph->left;
      Symbol.y = -Symbol.BitmapGlyph->top;

      // glyph->advance имеет формат 16.16, поэтому для приведения
      // его к формату 26.6 необходимо сдвинуть число на 10 бит враво
      posX += Symbol.Glyph->advance.x >> 10;

      // Вычисляем самую верхнюю позицию
      top = std::min(top, Symbol.y);

      // Вычисляем самую нижнюю позицию
      bottom = std::max(bottom, (Symbol.y + Symbol.BitmapGlyph->bitmap.rows));
  }
  const int32_t imageW = posX >> 6 ;
  const int32_t imageH = bottom - top;                // Высота строки (изображения)

  std::vector<uint8_t> image(imageW * imageH, 0x00);  // буфер для сохранения данных
  for (const symbol_info& Symbol: Text)
  {
    for (uint32_t srcY = 0; srcY < Symbol.BitmapGlyph->bitmap.rows; ++srcY)
    {
      for (uint32_t srcX = 0; srcX < Symbol.BitmapGlyph->bitmap.width; ++srcX)
      {
        image[Symbol.x + srcX + (Symbol.y + srcY - top) * imageW] =
            Symbol.BitmapGlyph->bitmap.buffer[srcX + srcY * Symbol.BitmapGlyph->bitmap.pitch];
      }
    }
  }

  for(auto& Symbol: Text) { FT_Done_Glyph(Symbol.Glyph); }

  size_t border = 20;
  size_t i = 0;                      // число скопированных пикселей
  size_t i_max = imageH * imageW;    // сумма пикселей источника, которые надо скопировать
  size_t src_start = 0;              // индекс в начале строки источника
  // индекс начального пикселя приемника
  size_t dst_start = bytes_per_pixel * (border + border * win_width);

  std::vector<unsigned char> texture(image_size * bytes_per_pixel, 0xFF);
  while(i < i_max)
  {
    size_t row_n = imageW;
    size_t dst = dst_start;
    size_t src = src_start;
    while(row_n > 0)
    {
      uint8_t c = image[src];
      texture[dst + 0] = 0x20;
      texture[dst + 1] = 0x20;
      texture[dst + 2] = 0x20;
      texture[dst + 3] = c;
      dst += 4;
      src += 1;
      row_n -= 1;
      i += 1;
    }
    src_start += imageW;                      // переход на начало следующей строки источника
    dst_start += win_width * bytes_per_pixel; // переход на начало следующей строки приемника
  }

  // Сохраняем изображение в PNG формате с прозрачностью
  savePNG(image.data(), imageW, imageH);
  opengl_window_show(texture.data(), win_width, win_height);
  exit(EXIT_SUCCESS);
}

