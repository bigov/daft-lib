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
image::image(const FT_Bitmap& Bitmap)
{
  width = Bitmap.width;
  rows = Bitmap.rows;
  Bits.resize(width * rows, 0xFF);
  memcpy(Bits.data(), Bitmap.buffer, Bits.size());
}


///
/// \brief paint_over
/// \param Src
/// \param Dst
/// \param x
/// \param y
///
void paint_over(const image& Src, image& Dst, unsigned int x, unsigned int y)
{
  if((Src.width + x  > Dst.width ) || (Src.rows + y > Dst.rows ))
  {
    std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
                            << "ERROR: (Src.width + x  > Dst.width ) || (Src.rows + y > Dst.rows )" << std::endl;
    return;
  }

  unsigned int i = 0;                             // число скопированных пикселей
  unsigned int i_max = Src.rows * Src.width;      // сумма пикселей источника, которые надо скопировать
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
image wft_face::get_symbol(uint32_t symbol_code, image Result)
{
  FT_Error error = FT_Load_Char(FtFace, symbol_code, FT_LOAD_RENDER);
  if( error )
  {
    std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
                        << "FT_Load_Char(FtFace, symbol_code, FT_LOAD_RENDER) failed" << std::endl;
    return Result;
  }
  image Src {FtFace->glyph->bitmap};
  if(Result.Bits.empty()) return Src;

  auto _Re = Result;
  Result.width += FtFace->glyph->bitmap.width;

  if(Result.rows < FtFace->glyph->bitmap.rows)
  {
    Result.rows = FtFace->glyph->bitmap.rows;
  }

  if(Result.rows > FtFace->glyph->bitmap.rows)
  {
    //
  }

  Result.Bits.resize(Result.width * Result.rows, 0xFF );
  paint_over(_Re, Result, 0, 0);
  paint_over(Src, Result, _Re.width, 0);
  return Result;
}


///
/// \brief wft_face::get_symbols_row
/// \param TextUnicode
/// \return
///
image wft_face::get_symbols_row(const std::vector<uint32_t>& TextUnicode)
{
  image Result {};

  for(auto symbol: TextUnicode)
  {
    Result = get_symbol(symbol, Result);
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
