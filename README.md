# Fox Compiler
A stack based concatenative programming language inspired by porth
written in C

## Installation Guide
### Dependencies
- GCC / CC / CLANG
- NASM
- CMake

```console
git clone https://github.com/stonedeva/fox.git
mkdir -p build
chmod +x build.sh && ./build.sh
```

## TODO
- [x] Stack based
- [x] Native
- [x] Basic operations
- [x] String literals
- [x] Variables
- [x] Conditions
- [x] Functions
- [x] Loops
- [ ] Arrays
- [ ] Structures
- [ ] Including files
- [ ] Else-conditions
- [ ] Comments
- [ ] Self hosted
- [ ] Static types

## Bugs
Referencing a variable (i.E: %count) begins with the character
of a modulo operation which causes problems!

## Getting Started
### Hello World!
```code
func main
    "Hello, World!" print
    0 return
end
```
Output:
```code
Hello World
```

### Variables
```code
func main
    95 var count
    105 25 + #count
    0 return
end
```

### If-Conditions
```code
func main
    250 var a
    250 var b
    %a %b = if
	"A and B are equals" print
    end
    0 return
end
```

### Loops
```code
func main
    while 1 do
	"Forever!" print
    end
    0 return
end
```
