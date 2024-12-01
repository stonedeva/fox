# Fox Compiler
A stack based concatenative programming language inspired by porth
written in C

## Installation Guide
### Dependencies
- C Compiler
- FASM

```console
git clone https://github.com/stonedeva/fox.git
mkdir -p build
cc -o cbuild cbuild.c
./cbuild
```

## TODO
- [x] Stack based
- [x] Native
- [x] Turing-Complete
- [ ] Static types
- [ ] Self hosted
- [ ] Compile to Native Code

## Intrinsic
| Intrinsic     | Function                                   | Showcase  |
|---------------|--------------------------------------------|-----------|
| ```dup```     | Duplicate top of the stack                 | ```a -> a a```  |
| ```swap```     | Swap top two elements of the stack        |  ```a b -> b a``` |
| ```over```     | Duplicate element beneath top of the stack        |  ```a b -> a b a``` |
| ```drop```     | Drop the element on top of the stack      |	```a b -> a```	|
| ```print```	| Print the element on top of the stack	     |	```Maintained``` |
| ```set```     | Set the value of address on top of the stack      |	```Maintained```	|
| ```get```	| Get the value of address on top of the stack	     |	```a (pointer) -> a (pointer) a (value)``` |

## Getting Started
### Hello World!
```code
import "std.fox"

func main in
    "Hello, World!\n" @puts
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
    if a b == do
	"A and B are equals\n" @puts
    else
	"A and B are not equals\n" @puts
    end
    0 return
end
```

### Loops
```code
import "std.fox"

func main in
    while 1 do
	"Forever!" @puts
    end
    0 return
end
```

### Pointers
```code
func main in
    var x 550 end
    &x 8 + 99 set
    &x get print
    &x 8 + get print

    0 return
end
