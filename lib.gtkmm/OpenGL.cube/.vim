setlocal ff=unix

"if !exists("g:include_dirs")
"  let g:include_dirs=' '
"endif
" Путь к файлу (vim~) с настройкой локального пути к внешним библиотекам.
" В нем должна быть строка вида:  let g:libs = ' d:/dev/WORKSPACE/LIBS'
"if filereadable("../../deps/vim~")
"  source ../../deps/vim~
"  let g:include_dirs.='-isystem'.g:libs
"endif

let g:syntastic_cpp_compiler_options='--std=c++17 -Werror -Wall -Wextra
 \ -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor
 \ -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code
 \ -Weffc++ -Wold-style-cast'

let g:syntastic_cpp_compiler='c++'

if match($OS, "Windows_NT") > -1
  let g:syntastic_cpp_compiler_options.=' -DMINGW64'
  set path=.\**
endif

let s:inc_dirs = ' ' . system('pkg-config --cflags-only-I gtkmm-3.0')
let g:syntastic_cpp_compiler_options .=
  \ substitute(s:inc_dirs[:-2], ' -I', ' -isystem ', 'g')

