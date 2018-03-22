//-----------------------------------------------------------------------------
//
// file: main.cpp
//
// Пример использования функции OpenGL 3.3 core 
//
//-----------------------------------------------------------------------------
#include "ttf.hpp"

//## Наложение на картинку текстовой строки
// TODO контроль границ
//
void TTF::write_wstring(pngImg &image, const std::wstring &text)
{
	for (const auto & wChar: text)
	{
		Symbol S = chars[wChar];
		for (int32_t _y = 0; _y < S.height; ++_y)
		for (int32_t _x = 0; _x < S.width; ++_x)
		{
			// нормализованное значение прозрачности и иконке
			float a = static_cast<float>(S.ico[_y * S.width + _x]) / 255.0f;
			// индекс пикселя на исходной картинке
			unsigned i = 4 * ((_height + Y + _y - S.base) * image.w + X + _x);
			image.img[i] = static_cast<uint8_t>
				(static_cast<float>(image.img[i]) * (1.f - a) + _r * a);
			i += 1;
			image.img[i] = static_cast<uint8_t>
				(static_cast<float>(image.img[i]) * (1.f - a) + _g * a);
			i += 1;
			image.img[i] = static_cast<uint8_t>
				(static_cast<float>(image.img[i]) * (1.f - a) + _b * a);
			i += 1;
			image.img[i] = static_cast<uint8_t>
				(static_cast<float>(image.img[i]) * (1.f - a) + _a * a);
		}
		X += S.width;
		// TODO контроль координат и перенос курсора
	}
	return;
}

//## Начальные координаты строки (сверху-слева)
//
void TTF::set_cursor(uint32_t x, uint32_t y)
{
	X = x; Y = y;
	return;
}

//## Установка цвета текста
//
void TTF::set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	set_color(r, g, b);
	_a = static_cast<float>(a);
	return;
}
void TTF::set_color(uint8_t r, uint8_t g, uint8_t b)
{
	_r = static_cast<float>(r);
	_g = static_cast<float>(g);
	_b = static_cast<float>(b);
	return;
}

//## Загрузка в оперативную память изображений символов шрифта
//
void TTF::load_chars(std::wstring in_chars_string)
{
	FT_Library ftLibrary = 0;
	FT_Init_FreeType(&ftLibrary);
	FT_Face ftFace = 0;
	FT_New_Face(ftLibrary, font.c_str(), 0, &ftFace);
	FT_Set_Pixel_Sizes(ftFace, pixel_width, 0);

	for (const uint32_t &charcode: in_chars_string)
	{
		try {chars.at(charcode);} catch(...)
		{ 
			FT_Glyph glyph = getGlyph(ftFace, charcode);
			if (!glyph) glyph = getGlyph(ftFace, L'.');
			if (!glyph) continue;
			FT_BitmapGlyph bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
			Symbol sym {};
			sym.base   = bitmapGlyph->top;
    	sym.height = bitmapGlyph->bitmap.rows;
			_height = std::max(_height, sym.height + 2); //отступ от Y курсора
			sym.width  = static_cast<int32_t>(glyph->advance.x >> 16);
			sym.ico.assign(sym.width * sym.height, 0);
			for (int32_t _y = 0; _y < sym.height; ++_y)
			for (uint32_t _x = 0; _x < bitmapGlyph->bitmap.width; ++_x)
   			sym.ico[bitmapGlyph->left + _x + _y * sym.width] = 
					bitmapGlyph->bitmap.buffer[_x + _y * bitmapGlyph->bitmap.pitch];
			chars[charcode] = std::move(sym);
			FT_Done_Glyph(glyph);
		}
	}

	FT_Done_Face(ftFace);
  FT_Done_FreeType(ftLibrary);
	return;
}

