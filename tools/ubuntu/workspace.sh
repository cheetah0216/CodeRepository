#/bin/bash

ProDir=`pwd`
PathDir="set path+=""$ProDir""/**"
#create tags file
ctags -R --fields=+lS

#create cscope file
find . -name "*.h" -o -name "*.c" -o -name "*.cpp" -o -name "*.java" -o -name "*.proc" -o -name "*.mak" -o -name "*.init" -o -name "*.txt" -o -name "*.yacc"> cscope.files
cscope -bq

# generate tag file for lookupfile plugin
echo -e "!_TAG_FILE_SORTED\t2\t/2=foldcase/" > filenametags
find . -not -regex '.*\.\(png\|gif\)' -type f -printf "%f\t%p\t1\n" | \
    sort -f >> filenametags 

#create workspace.vim
touch workspace.vim
echo "if filereadable(\"./filenametags\")" >> workspace.vim
echo "let g:LookupFile_TagExpr = '\"./filenametags\"'" >> workspace.vim
echo "endif" >> workspace.vim
echo "$PathDir" >> workspace.vim
echo "if filereadable(\"session.vim\")" >> workspace.vim
echo "source session.vim" >> workspace.vim
echo "endif" >> workspace.vim
echo "if filereadable(\"session.viminfo\")" >> workspace.vim
echo "rviminfo session.viminfo" >> workspace.vim
echo "endif" >> workspace.vim

