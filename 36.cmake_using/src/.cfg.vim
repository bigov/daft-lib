"
" VIM syntax check tuning
"
" Проверка синтаксиса при помощи плагина syntastic
"

"let g:syntastic_cpp_compiler_options="-std=c++11 -Werror -Wall -Wextra
"	\ -Wpedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy
"	\ -Wnon-virtual-dtor -Wconversion -Wsign-conversion
"	\ -Winit-self -Wunreachable-code -I../libs/"

" -Wold-style-cast

" Если gVIM запущен под MS-Windows
if match($OS, "Windows") > -1
	let MinGW="F:/cDev/MinGW/i686-6.2.0-release-posix-sjlj-rt_v5-rev0/mingw32/bin"
	let $PATH.=";".MinGW.";F:/cDev/cmake/bin"
	let g:syntastic_cpp_compiler=MinGW."/c++.exe"
	let LibsDir="f:/cDev/cLibs/ -D__MS_WIN__"
endif

let g:syntastic_cpp_compiler_options="-std=c++14 -Werror -Wall -Wextra
	\ -Wpedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy
	\ -Wnon-virtual-dtor -Wconversion -Wsign-conversion
	\ -Winit-self -Wunreachable-code -I".LibsDir


" вызов помощи Cmake
nmap ,hc :call OpenCmakeHelp()<CR>

function! OpenCmakeHelp()
    let s = getline( '.' )
    let i = col( '.' ) - 1
    while i > 0 && strpart( s, i, 1 ) =~ '[A-Za-z0-9_]'
        let i = i - 1
    endwhile
    while i < col('$') && strpart( s, i, 1 ) !~ '[A-Za-z0-9_]'
        let i = i + 1
    endwhile
    let start = match( s, '[A-Za-z0-9_]\+', i )
    let end = matchend( s, '[A-Za-z0-9_]\+', i )
    let ident = strpart( s, start, end - start )
    execute "split new"
    execute "%!cmake --help-command ".ident
    set nomodified
    set readonly
endfunction

autocmd BufRead,BufNewFile *.cmake,CMakeLists.txt,*.cmake.in nmap <F1> :call OpenCmakeHelp()<CR>

