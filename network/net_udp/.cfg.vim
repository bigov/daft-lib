"
" VIM syntax check tuning
"
" Проверка синтаксиса при помощи плагина syntastic
"
let g:syntastic_cpp_compiler_options="-std=c++11 -Werror -Wall -Wextra
	\ -Wpedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy
	\ -Wnon-virtual-dtor -Wconversion -Wsign-conversion
	\ -Winit-self -Wunreachable-code"
" -Wold-style-cast

" Если gVIM запущен под MS-Windows
if match($OS, "Windows") > -1

let g:syntastic_cpp_compiler_options="-std=c++11 -Werror -Wall -Wextra
	\ -Wpedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy
	\ -Wnon-virtual-dtor -Wconversion -Wsign-conversion
	\ -Winit-self -Wunreachable-code -D_WIN32"

endif

