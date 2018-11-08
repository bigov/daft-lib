setlocal ff=unix
set omnifunc=omni#cpp#complete#Main
let OmniCpp_NamespaceSearch = 1
let OmniCpp_GlobalScopeSearch = 1
let OmniCpp_ShowAccess = 1
let OmniCpp_ShowPrototypeInAbbr = 1 " show function parameters
let OmniCpp_MayCompleteDot = 1 " autocomplete after .
let OmniCpp_MayCompleteArrow = 1 " autocomplete after ->
let OmniCpp_MayCompleteScope = 1 " autocomplete after ::
au CursorMovedI,InsertLeave * if pumvisible() == 0|silent! pclose|endif
set completeopt=menuone,menu,longest

if !exists("g:include_dirs")
  let g:include_dirs=''
endif

" Путь к файлу с настройкой локального пути к внешним библиотекам.
" В нем должна быть строка вида: let g:tp_libs='d:/dev/WORKSPACE/LIBS'
let s:tp_file_name='../../deps/tplibs.vim'
if filereadable(s:tp_file_name)
  exec('source '.s:tp_file_name)
  let g:include_dirs.=' -isystem '.g:tp_libs
endif

let g:syntastic_cpp_compiler_options="--std=c++17 -Werror -Wall -Wextra
 \ -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor
 \ -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code
 \ -Weffc++ -Wold-style-cast".g:include_dirs

let g:syntastic_cpp_compiler="c++"

if match($OS, "Windows_NT") > -1
  let g:syntastic_cpp_compiler_options.=" -DMINGW64"
  set path=.\**
endif

