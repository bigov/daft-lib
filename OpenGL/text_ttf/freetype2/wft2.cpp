#include "wft2.hpp"

namespace tr {


///
/// \brief wft::wft
///
wft_lib::wft_lib(void)
{
  FT_Error error = FT_Init_FreeType(&FtLib);
  if (error) std::cerr << "FT_Init_FreeType() failed" << std::endl;
}


///
/// \brief wft_face::wft_face
/// \param library
/// \param filename
///
wft_face::wft_face(const char *filename, int face_index)
{
  FT_Error error = FT_New_Face(wFtLib, filename, face_index, &FtFace);
  if (error) std::cerr << "FT_New_Face() failed" << std::endl;
}


///
/// \brief wft_face::set_pixel_size
/// \param w
/// \param h
///
void wft_face::set_pixel_size(FT_UInt w, FT_UInt h)
{
  FT_Error error = FT_Set_Pixel_Sizes(FtFace, w, h);
  if(error) std::cerr << "FT_Set_Pixel_Sizes() failed" << std::endl;
}


///
/// \brief wft_face::get_kerning
/// \param leftCharcode
/// \param rightCharcode
/// \return Кернинг двух символов в формате 26.6
///
FT_Pos wft_face::get_kerning(uint32_t char_first, uint32_t char_second, FT_UInt kern_mode)
{
  if(char_first == 0) return 0;
  FT_UInt IndexFirst = FT_Get_Char_Index(FtFace, char_first);
  FT_UInt IndexSecond = FT_Get_Char_Index(FtFace, char_second);
  FT_Vector delta {};
  FT_Error error = FT_Get_Kerning(FtFace, IndexFirst, IndexSecond, kern_mode, &delta);
  if( error ) std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
                        << "FT_Get_Kerning(FtFace, IndexFirst, IndexSecond, FT_KERNING_DEFAULT, &delta) failed"
                        << std::endl;
  return delta.x;
}


///
/// \brief image::image
/// \param Bitmap
///
symbol::symbol(const FT_GlyphSlot& Slot)
{
  left = Slot->bitmap_left;
  top = Slot->bitmap_top;
  width = Slot->bitmap.width;
  height = Slot->bitmap.rows;
  hor_bear_y = Slot->metrics.horiBearingY;
  Bits.resize(width * height, 0xFF);
  memcpy(Bits.data(), Slot->bitmap.buffer, Bits.size());
}


///
/// \brief paint_over
/// \param Src
/// \param Dst
/// \param x
/// \param y
///
void paint_over(const symbol& Src, symbol& Dst, unsigned int x, unsigned int y)
{
  if((Src.width + x  > Dst.width ) || (Src.height + y > Dst.height ))
  {
    std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
                            << "ERROR: (Src.width + x  > Dst.width ) || (Src.height + y > Dst.height )" << std::endl;
    return;
  }

  unsigned int i = 0;                             // число скопированных пикселей
  unsigned int i_max = Src.height * Src.width;      // сумма пикселей источника, которые надо скопировать
  unsigned int src_row_start = 0;                 // индекс в начале строки источника
  unsigned int dst_row_start = x + y * Dst.width; // индекс начального пикселя приемника

  while(i < i_max)
  {
    unsigned int row_n = Src.width;
    unsigned int dst = dst_row_start;
    unsigned int src = src_row_start;
    while(row_n > 0)
    {
      Dst.Bits[dst] = Src.Bits[src];
      dst += 1;
      src += 1;
      row_n -= 1;
      i += 1;
    }
    src_row_start += Src.width; // переход на начало следующей строки источника
    dst_row_start += Dst.width; // переход на начало следующей строки приемника
  }
}


///
/// \brief wft_face::get_symbol
/// \param symbol_code
/// \return
///
symbol wft_face::get_symbol(uint32_t symbol_code)
{
  FT_Error error = FT_Load_Char(FtFace, symbol_code, FT_LOAD_RENDER);

  if( error )
  {
    std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
                        << "FT_Load_Char(FtFace, symbol_code, FT_LOAD_RENDER) failed" << std::endl;
    return symbol {};
  }

  return symbol {FtFace->glyph};
}


///
/// \brief wft_face::get_symbols_row
/// \param TextUnicode
/// \return
///
symbol wft_face::get_symbols_row(const std::vector<uint32_t>& TextUnicode)
{
  symbol Result {};
  std::vector<symbol> TmpArray {};

  for(auto s: TextUnicode)
  {
    auto TS = get_symbol(s);

    Result.height = std::max(Result.height, TS.height - TS.hor_bear_y + TS.height);
    Result.width += TS.width + TS.left;
    TmpArray.push_back(TS);
  }

  Result.Bits.resize(Result.width * Result.height, 0x88);

  int x = 0;
  for(auto& Symbol: TmpArray)
  {
    paint_over(Symbol, Result, x + Symbol.left, 0);
    x += Symbol.width;
  }
  /*
  int32_t top = 0;
  uint32_t bottom = 0;
  uint32_t prev_char = 0;

  FT_Pos posX = 0; // Позиция текущего символа в формате FT_Pos - "26.6"
  for (auto symbol_code: TextUnicode)
  {
    FT_Error error = FT_Load_Char(FtFace, symbol_code, FT_LOAD_RENDER);
    if( error ) std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
                          << "FT_Load_Char(FtFace, symbol_code, FT_LOAD_RENDER) failed" << std::endl;

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
*/

  return Result;
}

} // namespace tr
