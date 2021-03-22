#include "Board.h"
#include "Player.h"

#ifndef CPP_SAMPLES_GAME_H
#define CPP_SAMPLES_GAME_H

enum class State {
    UNKNOWN = 0,
    ONGOING = 1,
    DONE = 2,
    ERROR = 3
};

class Game {
public:
    Game(Player *p1, Player *p2);

    State ExecuteRound();

    std::ostream &DisplayState(std::ostream &out_stream);

private:
    const std::vector<Player *> players_;
    Board board_;
    State state_;
    size_t player_index_ = 0;
    int num_rounds_ = 0;
    std::string winner_ = "unknown";
};

#endif //CPP_SAMPLES_GAME_H
