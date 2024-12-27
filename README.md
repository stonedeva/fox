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
| ```rot```     | Rotate top three elements of the stack        |  ```a b c -> b c a``` |
| ```drop```     | Drop the element on top of the stack      |	```a b -> a```	|
| ```print```	| Print the element on top of the stack	     |	```Maintained``` |
| ```set```     | Set the value of address on top of the stack      |	```b a (pointer) -> b```	|
| ```get```	| Get the value of address on top of the stack	     |	```a (pointer) -> a (value)``` |

## Operators
Operatores apply for the top two stack elements.
They will remove them handle them and push the result back.

#### Mathematical
- ```+```
- ```-```
- ```*```
- ```/```

#### Bitwise
- ```>>```
- ```<<```
- ```|```
- ```&```
- ```^```

#### Logical
- ```<```
- ```>```
- ```!=```
- ```==```

## Data Types
In Fox there are three datatypes: ```int```, ```ptr```, ```bool```

### Integer
```code
205 255 +
```
This code pushes first ```205``` and then ```255``` onto the stack.
The plus operator then takes the top two elements sums them up and pushes
the result back onto the stack.

### Pointer
```code
var x 250 end
&x print
```
This code defines a variable ```x``` with value ```250```.
```&x``` now is a C-style pointer that pushes the address of ```x``` onto the stack.

### Boolean
```code
205 255 > print
```
This code again pushes ```205``` and ```255```onto the stack.
It then compares them using the greater than operator. 
The result will be pushed onto the stack.
```0``` meaning ```false``` and ```1``` meaning ```true```

### Strings
```code
"Hello, World!\n" print print
```
Strings are no seperate datatype in Fox instead they push
the length of the string aswell as the pointer to the beginning
of the string onto the stack.

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

### Constants
```code
const N 100 end

func main in
    N print
end
```

### Memory
```code
const sizeof(int64) 8 end
memory board sizeof(int64) 100 * end

func main in
    board print
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
func main in
    0 while dup 100 > do
	dup print
    end
    drop
    0 return
end
```

### Bindings
```code
func main in
    10 20 30
    take a b c in
	a print
	b print
	c print
    end
end
```

## Examples
### Max element
Find the largest element in an array
```code
const sizeof(int64) 8 end
memory list sizeof(int64) 4 * end

func main in
    list 20 set
    list 8 + 30 set
    list 16 + 95 set
    list 24 + 40 set

    var max 0 end

    0 while dup 4 > do
        list over sizeof(int64) * + get
        take element in
            if max element > do
                element #max
            end
        end
        1 +
    end
    drop

    max print
end
```

### File operations
Write strings to a file
```code
import "std.fox"

func main in
    "test.txt"c @fopen

    bind fd in
	"Hello, World!\n" fd @fputs
	"A new line!\n" fd @fputs
	"Last line!\n" fd @fputs
	fd @fclose
    end
end
```
