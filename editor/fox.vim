" fox.vim - Syntax highlighting for custom .fox files

" Define keywords
syntax keyword foxKeyword import func print var const for while if else const struct do return end define

" Define constants (numbers)
syntax match foxConstant "\<[0-9]\+\>"

" Define strings
syntax region foxString start=+"+ end=+"+

" Highlight groups
highlight link foxKeyword Keyword
highlight link foxConstant Number
highlight link foxString String
