
setlocal ff=unix
set omnifunc=omni#cpp#complete#Main

" OmniCppComplete
let OmniCpp_NamespaceSearch = 1
let OmniCpp_GlobalScopeSearch = 1
let OmniCpp_ShowAccess = 1
let OmniCpp_ShowPrototypeInAbbr = 1 " show function parameters
let OmniCpp_MayCompleteDot = 1 " autocomplete after .
let OmniCpp_MayCompleteArrow = 1 " autocomplete after ->
let OmniCpp_MayCompleteScope = 1 " autocomplete after ::
let OmniCpp_DefaultNamespaces = ["std", "_GLIBCXX_STD"]
"
" automatically open and close the popup menu / preview window
au CursorMovedI,InsertLeave * if pumvisible() == 0|silent! pclose|endif
set completeopt=menuone,menu,longest
" "set completeopt=preview " добавляет вверху окно с информацией

let g:syntastic_cpp_compiler_options="-std=c++14 -Werror -Wall -Wextra
	\ -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor
	\ -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code
	\ -Weffc++ -Iinclude -Ideps"

"-Wold-style-cast 

if match($OS, "Windows_NT") > -1
	let g:syntastic_cpp_compiler="c++.exe"
	let g:syntastic_cpp_compiler_options.=" -DMINGW64"
	set path=.\**
endif

