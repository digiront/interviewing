#include "Player.h"

#ifndef CPP_SAMPLES_RANDOMPLAYER_H
#define CPP_SAMPLES_RANDOMPLAYER_H


class RandomPlayer : public Player {
public:
    explicit RandomPlayer(const Options &options) : Player(options) {}

    size_t ChooseColumn() override;
};


#endif //CPP_SAMPLES_RANDOMPLAYER_H
