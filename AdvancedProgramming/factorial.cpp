/*
    MADE BY: AARON ZAJAC
    GITHUB: AARZAJ
    MAT: A01023376
*/
#include <iostream>

using namespace std;

int factorial(){
    int num;
    std::cout << "Ingrese el numero factorial " << '\n';
    std::cin >> num;
    for (int i = num-1; i > 0; i--) {
        num = num * i;
    }
    std::cout << "Tu factorial es: "<<num<< '\n';
    return num;
}

int main() {
    factorial();
    return 0;
}
