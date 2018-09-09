// Исходый код из
// https://blog2k.ru/archives/3530
// 

#include <ft2build.h>
#include FT_FREETYPE_H
 
int main()
{
    // Библиотека FreeType
    FT_Library library = 0;
 
    // Инициализация библиотеки
    FT_Init_FreeType(&library);
 
    // Шрифт
    FT_Face face = 0;
 
    // Загрузка шрифта
    FT_New_Face(library, "tahoma.ttf", 0, &face);
 
    // Установка размера пикселя
    FT_Set_Pixel_Sizes(face, 24, 12);
 
    // Код символа (юникод)
    const FT_ULong charCode = L'W';
 
    // Загрузка глифа из шрифта с его отрисовкой
    FT_Load_Char(face, charCode, FT_LOAD_RENDER);
 
    // Получение готового к использованию глифа
    FT_GlyphSlot glyph = face->glyph;
 
    // Получение размеров глифа
    const int width = glyph->bitmap.width;
    const int height = glyph->bitmap.rows;
    const int pitch = glyph->bitmap.pitch;
 
    // Вывод символа в консоли
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Получение прозрачности точки (x, y)
            const int a = glyph->bitmap.buffer[y * pitch + x];
 
            if (a > 127)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
 
    // Удаление шрифта
    FT_Done_Face(face);
    face = 0;
 
    // Удаление библиотеки
    FT_Done_FreeType(library);
    library = 0;
}
