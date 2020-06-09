#ifndef WFT2_HPP
#define WFT2_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H

//#include FT_BBOX_H
//#include FT_MODULE_H
//#include FT_CFF_DRIVER_H

#include <freetype/ftglyph.h>

namespace tr {

struct symbol {
    symbol(void) {};
    symbol(const FT_GlyphSlot& Slot);

    std::vector<unsigned char> Bits {};
    unsigned int width = 0;
    unsigned int height = 0;
    int left = 0;
    int top = 0;
    int hor_bear_y = 0;
};


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

    void get_bbox(symbol& Image);

  public:
    wft_face(const char *filename, int face_index = 0);
    ~wft_face(void) { FT_Done_Face(FtFace); }
    operator FT_Face() const { return FtFace; }

    void set_pixel_size(FT_UInt w, FT_UInt h);
    FT_Pos get_kerning(uint32_t char_first, uint32_t char_second, FT_UInt kern_mode = FT_KERNING_DEFAULT);
    symbol get_symbol(uint32_t symbol_code);
    symbol get_symbols_row(const std::vector<uint32_t>& TextUnicode);
};


} // namespace tr

#endif // WFT2_HPP
