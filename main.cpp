#include <iostream>
#include <lazyContainer.h>

void print(const int& i){
    std::cout << i << ' ';
}
int multiply(const int& i){
    return i * 3;
}
bool filter(const int& i){
    return i != 3;
}

int main() {
    auto test = funk::lazy<int>{};
    test << 1 << 2 << multiply << 3 << 4 << filter;
    test << print;
    test();
}
