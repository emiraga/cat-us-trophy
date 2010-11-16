set ai ts=4 sw=4 st=4 noet nu nohls
syntax enable
map <F6> :w<CR>:!g++ % -g && ./a.out < ~/input.txt <CR>
map <F5> :w<CR>:!g++ % -g && ./a.out < ~/input.txt <CR>
filetype plugin indent on
colo pablo
" experimental feature
map <F12> :!gdb ./a.out -c core <CR>
