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

" Путь к файлу (vim~) с настройкой локального пути к внешним библиотекам.
" В нем должна быть строка вида:  let g:libs = ' d:/dev/WORKSPACE/LIBS'
if filereadable("../../deps/vim~")
  source ../../deps/vim~
endif

if !exists("g:include_dirs")
  let g:include_dirs=""
endif
let g:include_dirs.=' -isystem'.g:libs
let g:include_dirs.=' -isystem'.g:libs.'/glfw-3.2.1/include'
let g:include_dirs.=' -isystem'.g:libs.'/glfw-3.2.1/deps'

let g:syntastic_cpp_compiler_options="--std=c++17 -Werror -Wall -Wextra
 \ -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor
 \ -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code
 \ -Weffc++ -Wold-style-cast " . g:include_dirs

let g:syntastic_cpp_compiler="c++"

if match($OS, "Windows_NT") > -1
  let g:syntastic_cpp_compiler_options.=" -DMINGW64"
  set path=.\**
endif

