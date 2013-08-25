"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Plugins
" => Vundle:Vim plugin manager
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nocompatible               " be iMproved
filetype off                   " required!

set rtp+=~/.vim/bundle/vundle/
call vundle#rc()

" let Vundle manage Vundle
" required! 
Bundle 'gmarik/vundle'

"""""""My plugins
"""""""vim-scripts repos
"taglist:列出了当前文件中的所有宏, 全局变量, 函数名等，类似source Insight左边的Symbol窗口.
Bundle 'vim-scripts/taglist.vim'

"WinManger:文件浏览器,通过这个浏览器来浏览工程中的源文件.
Bundle 'vim-scripts/winmanager'

"MiniBufExplorer:在一个Vim窗口打开多个标签.
Bundle 'vim-scripts/minibufexplorerpp'

"a.vim:.h/.c文件相互切换.
Bundle 'vim-scripts/a.vim'

"grep:指定关键词全工程的grep.
Bundle 'vim-scripts/grep.vim'

"VisualMark:书签高亮功能.
Bundle 'vim-scripts/Visual-Mark'

"SuperTab:快速自动补全代码功能，需要开启 new-omni-completion.
Bundle 'vim-scripts/SuperTab'

"echofunc:在插入模式下,输入函数名字后在输入一个(,显示函数原型.
Bundle 'vim-scripts/echofunc.vim'

"Lookupfile:输入部分的文件名，找到符合条件的工程中的文件.
"依赖genutils
Bundle 'vim-scripts/genutils'
Bundle 'vim-scripts/lookupfile'

"snipMate:提供快速生成代码段的功能.
Bundle 'vim-scripts/snipMate'

"markdown:MarkDown语法高亮.
Bundle 'vim-scripts/Markdown'

"NERD_commenter:提供快速注释/反注释代码块的功能.
Bundle 'vim-scripts/The-NERD-Commenter'

"SingleCompile:单个文件编译执行,支持多种类型(c,c++,python,bash..)
Bundle 'vim-scripts/SingleCompile'


" Save workspace info
function! SaveWorkSpace()
  WMToggle
  TMiniBufExplorer
  mksession! session.vim
  wviminfo! session.viminfo
endfunction
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => General
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Sets how many lines of history VIM has to remember
set history=1000


" Enable filetype plugins
filetype plugin indent on

" Set to auto read when a file is changed from the outside
"set autoread

" With a map leader it's possible to do extra key combinations
" like <leader>w saves the current file
let mapleader = ","
let g:mapleader = ","

" Fast saving
nmap <leader>w :w!<cr>


"Fast reloading of the .vimrc
map <silent> <leader>ss :source ~/.vimrc<cr>
"Fast editing of .vimrc
map <silent> <leader>ee :e ~/.vimrc<cr>
"When .vimrc is edited, reload it
autocmd! bufwritepost .vimrc source ~/.vimrc
"Fast save workspace info
map <silent> <leader>sw :call SaveWorkSpace()<cr>

set sessionoptions-=curdir
set sessionoptions+=sesdir
set sessionoptions+=resize
" execute project related configuration in current directory
if filereadable("workspace.vim")
    source workspace.vim
endif


syntax enable
syntax on
colorscheme desert
set nu    "显示行号
set ru    "打开状态栏标尺
set hls   "高亮查找文本
set sw=2  "自动缩进的时候,缩进尺寸为 4 个空格。
set ts=4  "Tab 宽度为 4 个字符。
set et    "编辑时将所有Tab替换为空格。 
set sm    "显示括号配对情况。
set cin   "打开 C/C++ 风格的自动缩进。
set mousemodel=popup "当右键单击窗口的时候， 弹出快捷菜单。
set whichwrap=h,b,s,<,>,l "自动折向下一行
"set nowrap           "指定不折行。
"set guioptions+=b    "添加水平滚动条
"if (has("gui_running"))
"    set nowrap
"    set guioptions+=b
"    colo torte
"else
"    set wrap
"    colo ron
"endif

"set fileencodings=utf-8,gb2312,gbk,gb18030
"set termencoding=utf-8
"set encoding=prc
"source $VIMRUNTIME/delmenu.vim
"source $VIMRUNTIME/menu.vim

"忽略大小写
set ic
nnoremap <silent> <F10> :set ic<CR>

:let g:vimim_map='c-bslash'	" Ctrl-\ 开关输入法

"代码折叠
set foldmethod=syntax
set foldlevel=100 " 启动 vim 时不要自动折叠代码
let javaScript_fold=1         " JavaScript
let perl_fold=1               " Perl
let php_folding=1             " PHP
let r_syntax_folding=1        " R
let ruby_fold=1               " Ruby
let sh_fold_enabled=1         " sh
let vimsyn_folding='af'       " Vim script
let xml_syntax_folding=1      " XML

"Tags
if filereadable("tags")
  set tags=tags
endif

"TagList
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1

"winmanger + netrw
let g:winManagerWindowLayout='FileExplorer|TagList'
nmap wm :WMToggle<cr>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" cscope setting
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
if has("cscope")
  set csprg=/usr/bin/cscope
  set csto=1
  set cst
  set nocsverb
  " add any database in current directory
  if filereadable("cscope.out")
      cs add cscope.out
  endif
  set csverb
endif

:set cscopequickfix=s-,c-,d-,i-,t-,e-
nmap <C-_>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-_>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap <C-_>d :cs find d <C-R>=expand("<cword>")<CR><CR>

"MiniBufExplorer
let g:miniBufExplMapCTabSwitchBufs = 1
let g:miniBufExplMapWindowNavVim = 1
let g:miniBufExplMapWindowNavArrows = 1
map <Leader>t :TMiniBufExplorer<cr>
".c-->.h a.vim
nnoremap <silent> <F12> :A<CR>

"grep.vim
nnoremap <silent> <F3> :Grep<CR>
nnoremap <silent> <F4> :Rgrep<CR>
let Grep_Default_Filelist = '*.c *.cpp *.h *.C *.CPP *.proc *.java *.html *.md *.js *.xml'

"自动补全窗口
filetype plugin indent on
set completeopt=longest,menu

"settab
let g:SuperTabRetainCompletionType=2
let g:SuperTabDefaultCompletionType="<C-X><C-O>"

""""""""""""""""""""""""""""""
" lookupfile setting
""""""""""""""""""""""""""""""
" lookup file with ignore case
function! LookupFile_IgnoreCaseFunc(pattern)
    let _tags = &tags
    try
        let &tags = eval(g:LookupFile_TagExpr)
        let newpattern = '\c' . a:pattern
        let tags = taglist(newpattern)
    catch
        echohl ErrorMsg | echo "Exception: " . v:exception | echohl NONE
        return ""
    finally
        let &tags = _tags
    endtry

    " Show the matches for what is typed so far.
    let files = map(tags, 'v:val["filename"]')
    return files
endfunction
let g:LookupFile_LookupFunc = 'LookupFile_IgnoreCaseFunc' 

let g:LookupFile_MinPatLength = 2               "最少输入2个字符才开始查找
let g:LookupFile_PreserveLastPattern = 0        "不保存上次查找的字符串
let g:LookupFile_PreservePatternHistory = 1     "保存查找历史
let g:LookupFile_AlwaysAcceptFirst = 1          "回车打开第一个匹配项目
let g:LookupFile_AllowNewFiles = 0              "不允许创建不存在的文件
"映射LookupFile为,lk
nmap <silent> <leader>lk :LUTags<cr>
"映射LUBufs为,ll
nmap <silent> <leader>lb :LUBufs<cr>
"映射LUWalk为,lw
nmap <silent> <leader>lw :LUWalk<cr>

""""""""""""""""""""""""""""""
" mark setting
""""""""""""""""""""""""""""""
nmap <silent> <leader>hl <Plug>MarkSet
vmap <silent> <leader>hl <Plug>MarkSet
nmap <silent> <leader>hh <Plug>MarkClear
vmap <silent> <leader>hh <Plug>MarkClear
nmap <silent> <leader>hr <Plug>MarkRegex
vmap <silent> <leader>hr <Plug>MarkRegex

""""filetype
autocmd BufEnter,BufRead,BufNewFile *.{pc,proc,plsql,sql} set filetype=esqlc
autocmd BufEnter,BufRead,BufNewFile *.{pc,proc,plsql,sql} set foldmethod=indent
autocmd BufEnter,BufRead,BufNewFile *.{cc,CC,cpp,CPP} set filetype=cpp
au BufEnter,BufRead,BufNewFile *.{md,mdown,mkd,mkdn,markdown,mdwn}   set filetype=markdown

""""""""""""""""""""""""""""""
"snipmate
""""""""""""""""""""""""""""""
"let g:snips_trigger_key='<F6>'

nmap <F9> :SCCompile<cr>
nmap <F10> :SCCompileRun<cr>

"disable netrw to generate history file
au VimLeave * if filereadable("[path here]/.netrwhist")|call delete("[path here]/.netrwhist")|endif
