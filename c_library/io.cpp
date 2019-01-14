#pragma once

#include <iostream>

#include "error.cpp"
#include "function.cpp"


class Print : public Function {
public:
    template<typename A>
    auto call(A a) {
        std::cout << a.get_data();
        return a;
    }
};


class Println : public Function {
public:
    template<typename A>
    auto call(A a) {
        std::cout << a.get_data() << std::endl;
        return a;
    }
};



class Info : public Function {
public:
    template<typename A>
    auto call(A a) {
        info(a.get_data());
        return a;
    }
};


class Debug : public Function {
public:
    template<typename A>
    auto call(A a) {
        debug(a.get_data());
        return a;
    }
};


class Warning : public Function {
public:
    template<typename A>
    auto call(A a) {
        warning(a.get_data());
        return a;
    }
};


class Error : public Function {
public:
    template<typename A>
    auto call(A a) {
        error(a.get_data());
        return a;
    }
};
