#include "Player.h"

#ifndef CONNECT_FOUR_HUMANPLAYER_H
#define CONNECT_FOUR_HUMANPLAYER_H

class HumanPlayer : public Player {
public:
    explicit HumanPlayer(const Options &options) : Player(options) {}

    size_t ChooseColumn() override;
};


#endif //CONNECT_FOUR_HUMANPLAYER_H
