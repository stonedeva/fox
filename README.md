# Fox Compiler
A stack based concatenative programming language inspired by porth
written in C

## Installation Guide
### Dependencies
- GCC / CC / CLANG
- FASM
- CMake

```console
git clone https://github.com/stonedeva/fox.git
mkdir -p build
chmod +x build.sh && ./build.sh
```

## TODO
- [x] Stack based
- [x] Native
- [x] Turing-Complete
- [ ] Self hosted
- [ ] Static types
- [ ] Compile to Native Code

## Getting Started
### Hello World!
```code
import "std.fox"

func main in
    "Hello, World!\n" @print
    0 return
end
```
Output:
```code
Hello World
```

### Variables
```code
func main in
    var count 95 end
    105 25 + #count
    0 return
end
```

### If-Conditions
```code
import "std.fox"

func main in
    var a 250 end
    var b 250 end
    a b = if
	"A and B are equals\n" @print
    else
	"A and B are not equals\n" @print
    end
    0 return
end
```

### Loops
```code
import "std.fox"

func main in
    while 1 do
	"Forever!" @print
    end
    0 return
end
```
