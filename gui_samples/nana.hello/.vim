setlocal ff=unix

let g:syntastic_cpp_compiler_options='--std=c++17 -Werror -Wall -Wextra
 \ -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor
 \ -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code
 \ -Weffc++ -Wold-style-cast'

let g:syntastic_cpp_compiler='c++'

if match($OS, "Windows_NT") > -1
  let g:syntastic_cpp_compiler_options.=' -DMINGW64'
  set path=.\**
endif

if !exists("g:include_dirs")
  let g:include_dirs=''
endif

" Путь к файлу (vim~) с настройкой локального пути к внешним библиотекам.
" В нем должна быть строка вида:  let g:tp_libs='D:/dev/WORKSPACE/LIBS'
let s:tp_file_name='../../deps/tplibs.vim'
if filereadable(s:tp_file_name)
  exec('source '.s:tp_file_name)
  let g:include_dirs.=' -isystem '.g:tp_libs.'/SRC/nana-1.6.2/include'
endif

let g:syntastic_cpp_compiler_options.=g:include_dirs

