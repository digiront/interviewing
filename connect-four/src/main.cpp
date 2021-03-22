#include "Game.h"
#include "Board.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"

int main() {
    HumanPlayer p1({.token='S', .id="SIRAN"});
    HumanPlayer p2({.token='P', .id="PAVLOS"});
    Game game(&p1, &p2);
    do {
        game.DisplayState(std::cout);
    } while(game.ExecuteRound() == State::ONGOING);
    return 0;
}