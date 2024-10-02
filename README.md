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
- [ ] Structures
- [ ] Including files
- [ ] Else-conditions
- [ ] Comments
- [ ] Self hosted
- [ ] Static types

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

