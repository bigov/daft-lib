#ifndef WFT2_HPP
#define WFT2_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_BBOX_H

//#include FT_MODULE_H
//#include FT_CFF_DRIVER_H

#include <freetype/ftglyph.h>

namespace tr {

///
/// \brief The wft_lib class
///
class wft_lib
{
  private:
    wft_lib(const wft_lib &) = delete;
    wft_lib &operator =(const wft_lib &) = delete;

    FT_Library FtLib {};

  public:
    wft_lib(void);
    ~wft_lib(void) { FT_Done_FreeType(FtLib); }
    operator FT_Library() const { return FtLib; }

};

class wft_glyph;

///
/// \brief The wft_face class
///
class wft_face
{
  private:
    wft_face(const wft_face &) = delete;
    wft_face &operator =(const wft_face &) = delete;

    wft_lib wFtLib {};
    FT_Face FtFace {};

  public:
    wft_face(const char *filename, int face_index = 0);
    ~wft_face(void) { FT_Done_Face(FtFace); }
    operator FT_Face() const { return FtFace; }

    void set_pixel_size(FT_UInt w, FT_UInt h);
    void select_size(FT_Int strike_index);
    FT_BitmapGlyph get_bitmap_glyph(const FT_ULong char_code, FT_Int32 mode );
    FT_BitmapGlyph glyph_to_bitmap(FT_Glyph& wftGlyph );

    FT_Glyph get_glyph(uint32_t charcode, FT_Int32 load_flags = FT_LOAD_RENDER);
    FT_Pos get_kerning(uint32_t char_first, uint32_t char_second, FT_UInt kern_mode = FT_KERNING_DEFAULT);
};


struct letter
{
    char ch = 0;
    FT_Pos xMin   = 0;
    FT_Pos yMin   = 0;
    FT_Pos width  = 0;
    FT_Pos height = 0;
};




} // namespace tr

#endif // WFT2_HPP
