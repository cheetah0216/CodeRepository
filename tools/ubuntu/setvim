#!/bin/bash

VimPlugin="/root/.vim/plugin"
VimDoc="/root/.vim/doc"
VimSyntax="/root/.vim/syntax"
SortVim="/home/liufei/soft/vim"
bp12="/home/liufei/work/bp12"

if [ ! -d "$VimPlugin" ] ; then
     mkdir -p "$VimPlugin"
fi

if [ ! -d $VimDoc ] ; then
     mkdir -p  $VimDoc
fi

if [ ! -d $VimSyntax ] ; then
     mkdir -p $VimSyntax
fi

if [ ! -d $SortVim ] ; then
     mkdir -p $SortVim
fi

#add download ctags source.
#
#

cd $SortVim
tar -xzvf ctags-5.8.tar.gz
cd ctags-5.8
./configure
make
make install

