//----------------------------------------------------------------------------
//
// file: main.cpp
//
// Пример использования функции OpenGL 3.3 core 
//
//----------------------------------------------------------------------------
#include "tools.hpp"

struct Symbol
{
  int32_t base   = 0; // расстояние от базовой линии
  int32_t width  = 0; // ширина символа
  int32_t height = 0; // высота символа
	std::vector<uint8_t> ico {};
};

class TTF
{
	public:
		TTF(std::string f, FT_UInt w): font(std::move(f)), pixel_width(w) {};
		~TTF() {};
		void load_chars(std::wstring chars_row);
		std::map<uint32_t, Symbol> chars {};
		void write_wstring(pngImg &image, const std::wstring &text);
		void set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void set_color(uint8_t r, uint8_t g, uint8_t b);
		void set_cursor(uint32_t x, uint32_t y);

	private:
		int X = 0, Y = 0, // координаты курсора
		_height = 0; // отступ курсора равен высоте самого высокого символа
		float _r = 20.f, _g = 20.f, _b = 20.f, _a = 255.f;
		std::string font {};
		FT_UInt pixel_width = 0;
};
