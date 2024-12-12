#include <iostream>

template<typename T>
struct Container {
    T element;
    Container(T e) : element(e) {}
    void display() const { std::cout << element << '\n'; }
};

// 很像一个 wrapper，把 Container 包装在了 struct Example 里。
template<template<typename> class C, typename T>
struct Example {
    C<T> container;
    Example(T e) : container(e) {}
    void show() { container.display(); }
};

int main() {
    Example<Container, double> example(3.14);
    example.show(); // 输出: 3.14
    return 0;
}
