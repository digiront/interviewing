#include "RandomPlayer.h"
#include <random>
#include "Constants.h"

namespace {
    size_t GetRandomWithinRange(int max_num) {
        static std::random_device rd; // obtain a random number from hardware
        static std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, max_num); // define the range
        return distr(gen);
    }
}

size_t RandomPlayer::ChooseColumn() {
    return GetRandomWithinRange(NUM_COLS) - 1;
}
