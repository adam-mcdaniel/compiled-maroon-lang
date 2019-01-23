# pink-lang

(named after pink-floyd lol)

A (kind of) functional programming language that compiles to native

## What is pink-lang?

pink-lang is a (kind of) functional programming language with incredible performance.

Here's how you can use it.

## Syntax
---

### Function Calls

Functions are applied using the `[]` operator, like this.

```clojure
Println["Hello world!"]
```

Multiple arguments can be supplied by separating them with commas.

```clojure
Print["Hello ", "world!", "\n"]
```

You must supply the required number of arguments when you call a function, no more and no less.

### Function Definitions

Functions are defined with the `=` operator, like this.

```clojure
double = n.(
	Mul[n, 2]
)
```

The `n.` signifies that the function takes an argument named `n`. You can also signify multiple arguments like this.

```clojure
sum = a.b.c.(
	Add[a, Add[b, c]]
)
```

The function `sum` takes 3 arguments, `a`, `b`, and `c`.

The most important function is the `main` function. This function takes no arguments, or one argument. If you choose to let `main` take an argument, the argument will be a linked list of the arguments supplied to your program from the command line.

```clojure
main = args.(
	Println[args] ; this will print out the arguments supplied to your program
)
```

There are no lambda functions yet, but I plan to add them.

### Object Orientation??

While it's not truly object oriented, pink-lang has some tools to make code more object oriented like.

The `~` operator is like the `.` operator in traditional programming languages. All it does is make whatever is on the left of the `~` the first argument to the function call to the right of the `~`.

So `1~Add[2]` is the same as `Add[1, 2]`.

This makes it easier to write long chains of function calls. Here's an example.

```clojure
; the sum function rewritten
sum = a.b.c.(
	a~Add[b]~Add[c]
)
```

Here's another.

```clojure
main = (
	"Hello "~Print["world!", "\n"]
)
```

### Standard Library

The standard library isn't well documented as of yet. If you want to see what functions you have available to you, you can look in `logic.cpp`, `io.cpp`, and `data.cpp` in your project's `include/std/` to find the functions you can use.

## Type inference

pink-lang infers your types and automatically uses generics for each function, so you can call a function with a String, a Number, or a Function, anything really.

## Foreign Function Interface

Because of the format of code generated by pink-lang, it's very interoperable with C++. For example, if I wanted to create a pink-lang function in C++ that printed out a value, and returned the value, it would look like this.

```c++
// the name of the function is `Put`
class Put : public Function {
public:
    template<typename A>
    auto call(A a) {
	Println().call(a) // call pink-lang's print
        return a;
    }
};
```

If you wanted to avoid using any of pink-lang's tools, you can do it yourself.

```c++
// the name of the function is `Put`
class Put : public Function {
public:
    template<typename A>
    auto call(A a) {
	cout << a.get_string() << endl; // get data from a and print it
        return a;
    }
};
```

Here's a function that allows for composing any number of functions together!
```c++
#include <iostream>
#include "std/function.cpp"
#include "std/io.cpp"
#include "std/error.cpp"
#include "std/data.cpp"
#include "std/logic.cpp"
using namespace std;

namespace compose {
    class Compose : public Function {
    public:
        template<typename A>
        auto call(A a) {
            return a;
        }

        template<typename A, typename... Args>
        auto call(A a, Args... args) {
            return Pipe().call(a, this->call(args...));
        }
    };
}
```


See how easy that was?

All you have to do to use that in pink-lang is to include your c++ file with the `Include["name_of_file.cpp"]` statement!

## Simplicity and Speed

pink-lang is blazingly fast, and it's very simple too. There are only 4 datatypes: `String`, `Number`, `Pair`, and `None`.

To get command-line arguments, all one has to do is give their main function a parameter to receive them as a linked list.

```clojure
main = your_parameter_name_here.(
	Println[your_parameter_name_here]
)
```

Super easy!

And function definitions are straight forward: just a name, an equals sign, the arguments separated by dots, and the function body. The last statement is returned at the end of the function.

## Program manager

pink-lang's program manager is incredibly easy to use. To create a new project, use `make project path="path/to/new/project"`. This command will generate this structure at the specified path.

```
.
├── include
│   └── std
│       ├── data.cpp
│       ├── error.cpp
│       ├── function.cpp
│       ├── io.cpp
│       └── logic.cpp
├── pf
├── run
├── src
│   └── main.pf
└── target
```

`pf` is the pink-lang compiler and run is a bash script that compiles and runs your program. Your pink-lang code is stored in the `src` directory. Any C++ file that you want to use in your program goes into the `include` directory, but not under `include/std`!

There is no unified system installation of pink-lang, so each project contains all the depencies it will ever need. This makes it very easy to give to someone else to compile, they won't have to install anything extra to compile your program.

If your project's `std` is out of date, you can `git pull`, and `make update path="path/to/project"`.


# Running pink-lang

To run pink-lang, you'll need a python3 installation to freeze the compiler with pyinstaller. Once, you build the compiler for your platform, however, everything else depends on stuff that should come ready with *nix machines: `make` and `g++` with `std=c++14`.

To install pink-lang on a *nix machine _(excluding the python3 installation)_, run this.

```bash
cd ~/Desktop
git clone https://github.com/adam-mcdaniel/pink-lang # Download pink-lang
cd pink-lang

make project path="../new_project" # Make new pink-lang project in ~/Desktop/new_project
make update path="../new_project"  # Update that project's version of std
cd ../new_project # Go to the project

./run # Compile and run the project!
```
