//============================================================================
//
// file: io.hpp
//
//
//
//============================================================================
#ifndef __IO_HPP__
#define __IO_HPP__
#include "tools.hpp"

struct pngImg
{
  int w = 0;
  int h = 0;
  std::vector<unsigned char> img = std::vector<unsigned char>(0);
  unsigned char * d(void);
};

struct fntImg : pngImg
{
  int left = 0;
  int top = 0;
  int x = 0;
  int y = 0;
};

extern pngImg get_png_img(const std::string & FName);
extern std::unique_ptr<char[]> read_chars_file(const std::string& FileName);
extern void info(const std::string &);
extern int random_int(void);

struct FontMap
{
  std::unordered_map<wchar_t, fntImg> chars;
  void load(const std::string & file_path, int font_size_in_pt);
};


#endif //__IO_HPP__
