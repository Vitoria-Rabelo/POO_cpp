#include <iostream>

//a = 7, b = 4 e c =11
int main() {
    int a = 5;
    int b = a;
    a += 1;  
    b -= 1;
    a += 1;
    int c = a + b;  
    std::cout << a << " " << b << " " << c << '\n';
}