set ai ts=4 sw=4 st=4 noet nu nohls
syntax enable
filetype plugin indent on
map <F6> :w<CR>:!g++ % -g && ./a.out < ~/input.txt <CR>
map <F5> <F6>
colo pablo
map <F12> :!gdb ./a.out -c core <CR>
