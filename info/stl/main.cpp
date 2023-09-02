#include <iostream>
#include <vector>

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<int> v;
    std::cout << "nb:" << std::endl;
    int i;
    std::cin >> i;
    v.push_back(i);

    for(int j : v){
        std::cout << j << std::endl;
    }
    return 0;
}

