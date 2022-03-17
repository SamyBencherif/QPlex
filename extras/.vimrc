
set number
set ruler
set hlsearch
set expandtab
set tabstop=2
set shiftwidth=2
set autoindent
set mouse=a
syntax on

noremap [ :w<CR>:prev<CR>
noremap ] :w<CR>:next<CR>

" l to create a blank line
noremap l o<ESC>
" shift+l to create a blank line above
noremap L O<ESC>

vnoremap > >gv
vnoremap < <gv

noremap h :nohl<CR>

noremap <BACKSPACE> "_dd

noremap M :set nolist wrap linebreak breakat&vim<CR>:set nonumber<CR>
noremap \ :w<CR>

set nowrap
