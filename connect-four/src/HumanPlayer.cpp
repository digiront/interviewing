#include "HumanPlayer.h"
#include "Constants.h"
#include <iostream>

size_t GetNumber(const std::string_view type) {
    size_t num;
    while (true) {
        std::cout << "Pick a " << type << " from 1 up to " << NUM_COLS << ": ";
        std::cin >> num;
        if (std::cin.fail()) {
            std::cin.clear(); std::cin.ignore();
            std::cout << "Re-enter a valid value!" << std::endl;
        } else break;
    }
    return num;
}
size_t HumanPlayer::ChooseColumn() {
    return GetNumber("column") - 1;
}