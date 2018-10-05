#ifndef GL_CONSOLE_HPP
#define GL_CONSOLE_HPP

#include <ctype.h>          // toupper, isprint
#include <limits.h>         // INT_MIN, INT_MAX
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#include <iostream>
#include <vector>

#include "gl_core33.h"

#include "imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "GLFW/glfw3.h"

struct gl_console
{
     gl_console(void);
    ~gl_console(void);

    char                  InputBuf[256];
    ImVector<char*>       Items;
    bool                  ScrollToBottom;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImVector<const char*> Commands;

  static int Stricmp(const char* str1, const char* str2);
  static int Strnicmp(const char* str1, const char* str2, int n);

  static char* Strdup(const char *str);
  static void  Strtrim(char* str);
  void ClearLog();
  void AddLog(const char* fmt, ...);
  void Draw(const char* title, bool* p_open);
  void ExecCommand(const char* command_line);
  static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
  int TextEditCallback(ImGuiInputTextCallbackData* data);

};

#endif

