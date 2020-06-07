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
/// \brief wft_face::set_pixel_size
/// \param w
/// \param h
///
void wft_face::select_size(FT_Int strike_index)
{
  FT_Error error = FT_Select_Size(FtFace, strike_index);
  if(error) std::cerr << "FT_Select_Size(FtFace, strike_index) failed" << std::endl;
}


///
/// \brief wft_face::get_glyph
/// \param char_code
/// \param mode
/// \return
///
FT_BitmapGlyph wft_face::get_bitmap_glyph(const FT_ULong char_code, FT_Int32 mode )
{
  FT_Glyph glyph {};

  //FT_Error error = FT_Load_Glyph(FtFace, index, FT_LOAD_NO_SCALE | FT_LOAD_NO_BITMAP);

  // load char's glyph
  FT_Error error = FT_Load_Char(FtFace, char_code, mode);
  if( error ) std::cerr << "FT_Load_Char(FtFace, char_code, mode) failed" << std::endl;

  // extract glyph image
  error = FT_Get_Glyph( FtFace->glyph, &glyph );
  if( error ) std::cerr << "FT_Get_Glyph( FtFace->glyph, &glyph ) failed" << std::endl;

  // convert to a bitmap (default render mode + destroying old)
  if ( glyph->format != FT_GLYPH_FORMAT_BITMAP )
  {
    error = FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 );
    if( error ) std::cerr << "FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 ) failed" << std::endl;
  }

  auto glyph_bitmap = reinterpret_cast<FT_BitmapGlyph>(glyph); // access bitmap content by typecasting
  FT_Done_Glyph( glyph );

  return glyph_bitmap;
}


///
/// \brief wft_face::glyph_to_bitmap
/// \param wFtGlyph
/// \return
///
FT_BitmapGlyph wft_face::glyph_to_bitmap(FT_Glyph& Glyph )
{
  if ( Glyph->format != FT_GLYPH_FORMAT_BITMAP )
  {
    FT_Error error = FT_Glyph_To_Bitmap( &Glyph, FT_RENDER_MODE_NORMAL, 0, 1 );
    if( error ) std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
        << "FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 ) failed" << std::endl;
  }
  return reinterpret_cast<FT_BitmapGlyph>(Glyph);
}


///
/// \brief wft_face::get_glyph
/// \param charcode
/// \return
///
FT_Glyph wft_face::get_glyph(uint32_t charcode, FT_Int32 load_flags)
{
  FT_Glyph TmpGlyph = {};

  FT_Error error = FT_Load_Char(FtFace, charcode, load_flags);
  if( error ) std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
                        << "FT_Load_Char failed" << std::endl;

  error = FT_Get_Glyph(FtFace->glyph, &TmpGlyph );
  if( error ) std::cerr << std::endl << __PRETTY_FUNCTION__ << std::endl
                        << "FT_Get_Glyph(FtFace->glyph, &glyph) failed" << std::endl;

  return TmpGlyph;
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


/*
///
/// \brief wft_glyph::~wft_glyph
///
wft_glyph::~wft_glyph(void)
{
  if(FtGlyph != nullptr) FT_Done_Glyph(FtGlyph);
}

///
/// \brief ttf::Run
/// \param symbol
/// \return
///
letter wft_glyph::get_letter(const char *symbol)
{
  letter L {};
  L.ch = *symbol;
  load_glyph(symbol);
  if (!check_outline_exist()) throw std::runtime_error("Outline check failed.");
  get_bbox(L);
  return L;
}


///
/// \brief ttf::load_glyph
/// \param symbol
///
void wft_glyph::load_glyph(const char *symbol) const
{
  FT_ULong code = static_cast<FT_ULong>(symbol[0]);

  // For simplicity, use the charmap FreeType provides by default;
  // in most cases this means Unicode.
  FT_UInt index = FT_Get_Char_Index(wFtFace, code);

  FT_Error error = FT_Load_Glyph(wFtFace, index, FT_LOAD_NO_SCALE | FT_LOAD_NO_BITMAP);
  if (error) std::cerr << "FT_Load_Glyph() failed" << std::endl;
}


///
/// \brief ttf::check_outline_exist
/// \return
///
bool wft_glyph::check_outline_exist() const
{
  FT_Face face = wFtFace;
  FT_GlyphSlot slot = face->glyph;
  FT_Outline &outline = slot->outline;
  if (slot->format != FT_GLYPH_FORMAT_OUTLINE) return false;          // Should never happen.  Just an extra check.
  if (outline.n_contours <= 0 || outline.n_points <= 0) return false; // Can happen for some font files.
  FT_Error error = FT_Outline_Check(&outline);
  return (false == error);
}


///
/// \brief ttf::get_bbox
///
void wft_glyph::get_bbox(letter& Ch)
{
  FT_Face face = wFtFace;
  FT_GlyphSlot slot = face->glyph;
  FT_Outline &outline = slot->outline;
  FT_BBox boundingBox;
  FT_Outline_Get_BBox(&outline, &boundingBox);

  Ch.xMin = boundingBox.xMin;
  Ch.yMin = boundingBox.yMin;
  Ch.width = boundingBox.xMax - Ch.xMin;
  Ch.height = boundingBox.yMax - Ch.yMin;
}
*/

} // namespace tr
