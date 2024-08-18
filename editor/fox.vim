# Vim editor syntax for Fox Language
if exists("b:current_syntax")
    finish
end

# Language keywords
syntax keyword foxKeywords poke if else while for return import

# Constants
syntax keyword foxConstants true false null 

# Comments (;;)
syntax match foxComment ";;.*"

# Strings
syntax region foxString start=+"+ skip=+\\+ end=+"+

# Numbers
syntax match foxNumbers "\<\d\+\.\d\+\|\d\+\>"

# Highlighting groups
highlight default link foxKeywords Keyword
highlight default link foxConstants Constant
highlight default link foxComment Comment
highlight default link foxString String
highlight default link foxNumbers Number

let b:current_syntax = "fox"
