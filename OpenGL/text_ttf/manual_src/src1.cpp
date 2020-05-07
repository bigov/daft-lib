// ������� ��� ��
// https://blog2k.ru/archives/3530
// 

#include <ft2build.h>
#include FT_FREETYPE_H
 
int main()
{
    // ���������� FreeType
    FT_Library library = 0;
 
    // ������������� ����������
    FT_Init_FreeType(&library);
 
    // �����
    FT_Face face = 0;
 
    // �������� ������
    FT_New_Face(library, "tahoma.ttf", 0, &face);
 
    // ��������� ������� �������
    FT_Set_Pixel_Sizes(face, 24, 12);
 
    // ��� ������� (������)
    const FT_ULong charCode = L'W';
 
    // �������� ����� �� ������ � ��� ����������
    FT_Load_Char(face, charCode, FT_LOAD_RENDER);
 
    // ��������� �������� � ������������� �����
    FT_GlyphSlot glyph = face->glyph;
 
    // ��������� �������� �����
    const int width = glyph->bitmap.width;
    const int height = glyph->bitmap.rows;
    const int pitch = glyph->bitmap.pitch;
 
    // ����� ������� � �������
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // ��������� ������������ ����� (x, y)
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
 
    // �������� ������
    FT_Done_Face(face);
    face = 0;
 
    // �������� ����������
    FT_Done_FreeType(library);
    library = 0;
}
