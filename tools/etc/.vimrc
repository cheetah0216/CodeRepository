"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Vundle
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nocompatible              " be iMproved, required
filetype off                  " required
"set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/vundle/
 call vundle#rc()
" alternatively, pass a path where Vundle should install plugins
"let path = '~/some/path/here'
"call vundle#rc(path)
"Plugin 'lsdr/monokai'
Plugin 'gmarik/vundle'
Plugin 'octol/vim-cpp-enhanced-highlight'

"youdao 翻译
Plugin 'ianva/vim-youdao-translater'
vnoremap <silent> <C-T> <Esc>:Ydv<CR> 
nnoremap <silent> <C-T> <Esc>:Ydc<CR> 
noremap <leader>t :Yde<CR>

"缩进对齐线
Plugin 'Yggdroot/indentLine'
"map <leader>il :IndentLinesToggle<CR>
nnoremap <silent> <F8> :IndentLinesToggle<CR>

"增强状态栏
Plugin 'Lokaltog/vim-powerline'
set laststatus=2
let g:Powerline_symbols='unicode'

"括号自动补全（delimitMate,ijiangmiao/auto-pairs）
"Plugin 'Raimondi/delimitMate'
Plugin 'jiangmiao/auto-pairs'

"tarbar:列出了当前文件中的所有宏, 全局变量, 函数名等，类似source
"Insight左边的Symbol窗口.
Plugin 'majutsushi/tagbar'
nnoremap <silent> <F10> :TagbarToggle<CR>
let g:tagbar_width = 35

"netrw:文件浏览器,通过这个浏览器来浏览工程中的源文件.
let g:netrw_hide = 1
let g:netrw_list_hide = '.*\.pyc,\.DS_Store,.swp,.out'
let g:netrw_liststyle = 3
let g:netrw_browse_split=4
let g:netrw_preview=1
let g:netrw_winsize=25
set autochdir
nnoremap <silent> <F9> :Sexplore!<CR>
"disable netrw to generate history file
au VimLeave * if filereadable("[path here]/.netrwhist")|call delete("[path here]/.netrwhist")|endif

"MiniBufExplorer:在一个Vim窗口打开多个标签.
"Plugin 'techlivezheng/vim-plugin-minibufexpl'
Plugin 'vim-scripts/minibufexplorerpp'
let g:miniBufExplMapCTabSwitchBufs = 1
let g:miniBufExplMapWindowNavVim = 1
let g:miniBufExplMapWindowNavArrows = 1
"map <Leader>t :TMiniBufExplorer<cr>

"grep:指定关键词全工程的grep.
Plugin 'yegappan/grep'
nnoremap <silent> <F3> :Grep<CR>
nnoremap <silent> <F4> :Rgrep<CR>
let Grep_Default_Filelist = '*.c *.cpp *.h *.C *.CPP *.proc *.java *.html *.md *.js *.xml *.py'

"VisualMark:书签高亮功能.
Plugin 'vim-scripts/Visual-Mark'

"Lookupfile:输入部分的文件名，找到符合条件的工程中的文件.
""依赖genutils
Plugin 'vim-scripts/genutils'
Plugin 'vim-scripts/lookupfile'
"bug vim第一次先要执行一次查询
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
if filereadable("./filenametags")
    let g:LookupFile_TagExpr = '"./filenametags"'
endif
"nnoremap <silent> <F5> :LookupFile<CR>
nnoremap <silent> <F6> :LUBufs<CR>

"snipMate:提供快速生成代码段的功能.
Plugin 'vim-scripts/snipMate'

filetype plugin indent on     " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList          - list configured plugins
" :PluginInstall(!)    - install (update) plugins
" :PluginSearch(!) foo - search (or refresh cache first) for foo
" :PluginClean(!)      - confirm (or auto-approve) removal of unused plugins
"
" see :h vundle for more details or wiki for FAQ
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => General
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"filetype plugin indent on "Enable filetype plugins
syntax enable
syntax on
set encoding=utf-8
set fenc=utf-8
set fileencodings=ucs-bom,utf-8,cp936
set nobomb
"set background=dark
"colorscheme Tomorrow
"colorscheme solarized
colorscheme Tomorrow-Night-Eighties
"colorscheme Tomorrow-Night
"colorscheme desert
"set autoread           "Autoread when a file is changed from the outside
set history=1000          "How many lines of history VIM has to remember
set showmatch             "代码匹配
set nu                    "显示行号
set ru                    "打开状态栏标尺
set hls                   "高亮查找文本
"set cin                   "打开 C/C++ 风格的自动缩进。
"set autoindent            "自动缩进
set smartindent
set expandtab             "以下三个配置配合使用，设置tab和缩进空格数
set sw=4                  "自动缩进的时候,缩进尺寸为2个空格。
set ts=4                  "Tab 宽度为 2 个字符。
set et                    "编辑时将所有Tab替换为空格。 
set sm                    "显示括号配对情况。
set cursorline            "为光标所在行加下划线
"set mousemodel=popup      "当右键单击窗口的时候， 弹出快捷菜单。
set bs=2                  "在insert模式下用退格键删除
set whichwrap=h,b,s,<,>,l "自动折向下一行
set foldmethod=syntax     "代码折叠
set foldlevel=100         "启动 vim 时不要自动折叠代码
set ic                    "检索时忽略大小写"
"nnoremap <silent> <F10> :set ic<CR>
set fileencodings=uft-8,gbk "使用utf-8或gbk打开文件
set helplang=cn           "帮助系统设置为中文
"set nowrap               "指定不折行。
"set guioptions+=b        "添加水平滚动条
"if (has("gui_running"))
"    set nowrap
"    set guioptions+=b
"    colo torte
"else
"    set wrap
"    colo ron
"endif
if (has("gui_running"))
  set go=aAce             "去掉难看的工具栏和滑动条
  "set transparency=30     "透明背景
  set guifont=Monaco:h13   "设置默认字体为monaco
  set columns=100          "设置宽
  set lines=40             "设置长
endif


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => edit .vimrc
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:mapleader = ","
" Fast saving
nmap <leader>w :w!<cr>
"Fast reloading of the .vimrc
map <silent> <leader>ss :source ~/.vimrc<cr>
"Fast editing of .vimrc
map <silent> <leader>ee :e ~/.vimrc<cr>
"When .vimrc is edited, reload it
autocmd! bufwritepost .vimrc source ~/.vimrc

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Workspace
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Save workspace info
"function! SaveWorkSpace()
  "TMiniBufExplorer
"  set sessionoptions-=curdir
"  set sessionoptions+=sesdir
"  set sessionoptions+=resize
"  mksession! session.vim
"  wviminfo! session.viminfo
"endfunction
"Fast save workspace info
"map <silent> <leader>sw :call SaveWorkSpace()<cr>

" execute project related configuration in current directory
if filereadable("workspace.vim")
    source workspace.vim
endif
":let g:vimim_map='c-bslash'	" Ctrl-\ 开关输入法

".c-->.h a.vim
nnoremap <silent> <F12> :A<CR>


"自动补全窗口
filetype plugin indent on
set completeopt=longest,menu

"settab
let g:SuperTabRetainCompletionType=2
let g:SuperTabDefaultCompletionType="<C-X><C-O>"

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
autocmd BufEnter,BufRead,BufNewFile *.{md,mdown,mkd,mkdn,markdown,mdwn}   set filetype=markdown
