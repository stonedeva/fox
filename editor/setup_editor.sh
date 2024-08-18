#!/bin/bash
mkdir -p ~/.nvim/ftdetect
cp fox.vim ~/.nvim/ftdetect/fox.vim
echo "autocmd BufRead,BufNewFile *.fox set filetype=fox" >> ~/.vimrc

