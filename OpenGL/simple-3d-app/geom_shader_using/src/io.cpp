//============================================================================
//
// file: io.cpp
//
// Библиотека функций ввода-вывода
//
//============================================================================
#include <sys/stat.h>
#include "io.hpp"

namespace tr
{

// цвет буквы/глифа
unsigned char _R = 33, _G = 33, _B = 33; // TODO: можно управлять


////////
// Это просто ссылка для сокращения размера кода при обращении к данным
unsigned char * pngImg::d(void)
{
	return img.data();
}

////////
// Генератор случайных положительных int
//
int random_int()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
   return std::rand();
}

////////
// Генератор случайных положительных short
//
short random_short()
{
	return
		static_cast<short>(random_int() % std::numeric_limits<short>::max());
}



////////
// Загрузка средствами библиотеки freetype пиксельной маски одного символа
//
fntImg _load_char(FT_ULong L, const FT_Face & face )
{
	// Загрузка символа, указанного в переменной "L"
	// TODO: разобраться с UTF-8 и кириллицей
	if(FT_Load_Char(face, L, FT_LOAD_RENDER))
		ERR("Err load char " + L);

	fntImg result {};
	FT_GlyphSlot slot = face->glyph;

	result.left =	slot->bitmap_left;
	result.top = slot->bitmap_top;
	result.x = static_cast<int>(slot->advance.x);
	result.y = static_cast<int>(slot->advance.y);

	auto b = face->glyph->bitmap;
	result.w = static_cast<int>(b.width);
	result.h = static_cast<int>(b.rows);

	for(unsigned int y = b.rows; y > 0; y--)
	for(unsigned int x = 0; x < b.width; x++)
	{
		result.img.push_back(_R);
		result.img.push_back(_G);
		result.img.push_back(_B);
 		unsigned char _A = b.buffer[(y-1) * b.width + x];
		//if(_A == 0) _A = 150;
		result.img.push_back(_A);

		 //result.img.push_back(b.buffer[(y-1) * b.width + x]); // прозрачность
	}
	return result;
}

////////
// Загрузка пиксельных масок шрифта для строки символов
//
void FontMap::load(const std::string & filepath, int font_size)
{
	FT_Face face;
	FT_Library library;

	const char * font_file_name = filepath.c_str();

  if (FT_Init_FreeType(&library))
		ERR("Err init freetye lib");
	if (FT_New_Face(library, font_file_name, 0, &face))
		ERR("Err load font file");

	// Выбор размера шрифта в (pt) с учетом разрешения дисплея (100 dpi)
	unsigned dpi = 100; // TODO значеним разрешения экрана управлять
	if (FT_Set_Char_Size(face, font_size * 64, 0, dpi, 0))
		ERR("Err set font size = " + font_size);

	//std::unordered_map<wchar_t, fntImg> chars;
	std::wstring key = L"0123456789 .,;:|\\/+-=(){}[]><~?!@#$%^&*\"'";
		key += L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЭЬЮЯ";
		key += L"абвгдеёжзийклмнопрстуфхцчшщъэьюя";
		key += L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		key += L"abcdefghijklmnopqrstuvwxyz";

	for(auto& k: key)
		chars.emplace(k, _load_char(static_cast<FT_ULong>(k), face));

	FT_Done_Face(face);
  FT_Done_FreeType(library);
	return;
}
	////////
	// Чтение файла в формате PNG
	//
	/*
	pngImg get_png_img(const std::string & f_n)
	{
		const char * filename = f_n.c_str();
		#if not defined PNG_SIMPLIFIED_READ_SUPPORTED
			ERR("FAILURE: you must update the \"libpng\".");
		#endif

		png_image info;
		memset(&info, 0, sizeof info);
		info.version = PNG_IMAGE_VERSION;

		if (!png_image_begin_read_from_file(&info, filename))
			ERR("Can't read PNG image file");

		info.format = PNG_FORMAT_RGBA;
		pngImg res = {
			static_cast<int>(info.width),
			static_cast<int>(info.height),
			std::vector<unsigned char>(PNG_IMAGE_SIZE(info), '\0')
		};

		if (!png_image_finish_read(&info, NULL, res.img.data(), 0, NULL ))
		{
			png_image_free(&info);
			ERR(info.message);
		}

		return res;
	}
*/
	////////
	// Преобразователь типов
	//
	// Упаковывает два коротких в одно целое. Используется для формирования
	// массива текстур в контенте OpenGL
	//
	int sh2int(short sh1, short sh2)
	{
		short sh_T[2] = {sh1, sh2};
		int * int_T = reinterpret_cast<int*>(sh_T);
		return *int_T;
	}

	////////
	// Чтение содержимого текстового файла
	//
	std::vector<char> get_txt_chars(const std::string & fname)
	{
		// проверка наличия файла
		struct stat buffer;
		if (stat (fname.c_str(), &buffer) != 0) ERR("Missing file: " + fname);

		// чтение файла
		std::ifstream file(fname, std::ios::in|std::ios::ate);
		file.exceptions(std::ios_base::badbit|std::ios_base::failbit);
		if (!file.is_open()) ERR("Can't open " + fname);
		auto size = static_cast<long long>(file.tellg());
		std::vector<char> content (static_cast<size_t>(size + 1), '\0');
		file.seekg(0, std::ios::beg);
		file.read(content.data(), size);
		file.close();
		return content;
	}

	////
	// Вывод текстовой информацияя информации
	//
	void info(const std::string & info)
	{
		std::cout << info << std::endl;
		return;
	}

} //namespace tr
