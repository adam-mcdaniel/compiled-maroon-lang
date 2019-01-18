
#include <iostream>
#include "../include/std/function.cpp"
#include "../include/std/io.cpp"
#include "../include/std/error.cpp"
#include "../include/std/data.cpp"
#include "../include/std/logic.cpp"
using namespace std;



#include "../include/compose.cpp"


class Double : public Function {
public:
	template<typename __A__>
	auto call(__A__ n) {
		return Mul().call(Number(2), n);
	}
};


class Triple : public Function {
public:
	template<typename __A__>
	auto call(__A__ n) {
		return Mul().call(Number(3), n);
	}
};


class Quadruple : public Function {
public:
	template<typename __A__>
	auto call(__A__ n) {
		return Mul().call(Number(4), n);
	}
};


class Main : public Function {
public:
	template<typename __A__>
	auto call(__A__ args) {
		return compose::Compose().call(Println(), Double(), Triple()).call(Number(5));
	}
};


int main(int argc, char** argv) {
    Pair args;
    if (argc > 1) {
        args = Pair().call(String(argv[argc-1]), None());
        for (int i = argc-2; i > 0; i--) {
            args = Pair().call(String(argv[i]), args);
        }
    } else {
        args = Pair().call(None(), None());
    }

    Main().call(args);
    return 0;
}