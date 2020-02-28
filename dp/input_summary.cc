#include <iostream>
#include <string>

// 1. 处理字符串
int main(int argc, char *argv[]) {
    std::string name;
    std::cout << "What is your name? ";
    getline (std::cin, name);

    return 0;
}