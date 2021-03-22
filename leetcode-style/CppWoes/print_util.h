#include <iostream>

#ifndef LEETCODE_STYLE_PRINT_UTIL_H
#define LEETCODE_STYLE_PRINT_UTIL_H

template<typename Container>
Print(const Container& c, const string& title = "Container:") {
    std::cout << title << endl;
    for (const auto& elem : c) {
        std::cout << elem << std::endl;
    }
    std::cout << "." << std::endl;
}
#endif //LEETCODE_STYLE_PRINT_UTIL_H
