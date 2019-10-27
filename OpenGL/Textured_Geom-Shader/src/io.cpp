//============================================================================
//
// file: io.cpp
//
// Библиотека функций ввода-вывода
//
//============================================================================
#include <sys/stat.h>
#include "io.hpp"

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

/*
////////
// Генератор случайных положительных short
//
short random_short()
{
	return 
		static_cast<short>(random_int() % std::numeric_limits<short>::max());
}
*/

////////
// Чтение файла в формате PNG
//
pngImg get_png_img(const std::string& FName)
{
  const char* filename = FName.c_str();
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


///
/// \brief read_chars_file
/// \param FNname
/// \param Buffer
/// \details Чтение в буфер содержимого текстового файла
/// !!!ВНИМАНИЕ!!!
/// Для шейдеров поддерживается только формат файлов UNIX.
/// DOS-файлы "\n\r" НЕ ПОДДЕРЖИВАЮТСЯ
///
std::unique_ptr<char[]> read_chars_file(const std::string& FileName)
{
  // проверка наличия файла
  struct stat Buf;
  if (stat (FileName.c_str(), &Buf) != 0) ERR("Missing file: " + FileName);

  // открытие файла
  std::ifstream file(FileName, std::ios::in|std::ios::ate);
  file.exceptions(std::ios_base::badbit|std::ios_base::failbit);
  if (!file.is_open()) ERR("Can't open " + FileName);

  auto size = static_cast<long long>(file.tellg());
  if(size < 1) return nullptr;

  auto data_size = static_cast<size_t>(size) + 1;
  auto data = std::make_unique<char[]>(data_size);

  file.seekg(0, std::ios::beg);
  file.read(data.get(), size);
  file.close();

  data[data_size - 1] = '\0';
  return data;
}

////
// Вывод текстовой информацияя информации
//
void info(const std::string & info)
{
  std::cout << info << std::endl;
  return;
}

