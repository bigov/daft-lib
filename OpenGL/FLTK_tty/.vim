setlocal ff=unix
set omnifunc=omni#cpp#complete#Main

" OmniCppComplete
let OmniCpp_NamespaceSearch = 1
let OmniCpp_GlobalScopeSearch = 1
let OmniCpp_ShowAccess = 1
let OmniCpp_ShowPrototypeInAbbr = 1 " show function parameters
let OmniCpp_MayCompleteDot = 1      " autocomplete after .
let OmniCpp_MayCompleteArrow = 1    " autocomplete after ->
let OmniCpp_MayCompleteScope = 1    " autocomplete after ::
let OmniCpp_DefaultNamespaces = ["std", "_GLIBCXX_STD"]
"
" automatically open and close the popup menu / preview window
au CursorMovedI,InsertLeave * if pumvisible() == 0|silent! pclose|endif
set completeopt=menuone,menu,longest
set completeopt=preview              " добавляет вверху окно с информацией

" Библиотека FLTK 1.4.x (настройка и сырцы)
let g:inc_dirs = " -isystem \"../../../LIBS/include/fltk-1.4.0\""
let g:inc_dirs.= " -isystem \"../../../LIBS/SRC/fltk-1.4.0\""

let g:syntastic_cpp_compiler="clang++"
let g:syntastic_cpp_compiler_options="-std=c++17 -Werror -Wall -Wextra
  \ -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor
  \ -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code
  \ -Weffc++ -Wold-style-cast ".g:inc_dirs

if match($OS, "Windows_NT") > -1
  let g:syntastic_cpp_compiler_options.=" -DMINGW64"
endif

