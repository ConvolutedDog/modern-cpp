#include <iostream>
#include <vector>

// // Define a template class with a template template parameter
// template<
//     typename T,
//     template<typename = T/*, typename = std::allocator<T>*/>
//     class Container
// >
// class MyContainer {
// public:
//     Container<T> data;

//     void add(const T& value) {
//         data.push_back(value);
//     }

//     void print() {
//         for (auto& elem : data) {
//             std::cout << elem << ' ';
//         }
//         std::cout << '\n';
//     }
// };

// Define a template class with a template template parameter
template<
    typename T,
    template<typename _Tp=T, typename _Alloc = std::allocator<_Tp> > class Container
>
class MyContainer {
public:
    Container<T> data;

    void add(const T& value) {
        data.push_back(value);
    }

    void print() {
        for (auto& elem : data) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
};

int main() {
    // Instantiate MyContainer with std::vector as the container
    MyContainer<int, std::vector> myIntContainer;
    myIntContainer.add(10);
    myIntContainer.add(20);

    myIntContainer.print(); // Output: 10 20

    return 0;
}
