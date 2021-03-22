#include "Game.h"
#include "Constants.h"
#include <cassert>
#include <thread>
#include <chrono>

Game::Game(Player *p1, Player *p2) : players_({p1, p2}), board_(NUM_ROWS, NUM_COLS), state_(State::ONGOING) {
    for (const Player *p : players_) {
        assert(p != nullptr);
    }
}

State Game::ExecuteRound() {
    if (state_ != State::ONGOING) return state_;
    num_rounds_++;

    size_t attempts = 0;
    Player *current_player = players_[player_index_];
    while (attempts < MAX_RETRIES) { // repeat until player made a valid move
        size_t chosen_col = current_player->ChooseColumn();
        if (board_.IsValid(chosen_col)) {
            std::cout << "Player " << current_player->Id() << " chose column: " << chosen_col + 1 << std::endl;
            board_.SetCellUnsafe(chosen_col, current_player->Token());
            if (board_.AreFourConnected(current_player->Token())) {
                state_ = State::DONE;
                winner_ = current_player->Id();
            }
            break;
        } else {
            std::cout << "Please choose a valid cell." << std::endl;
        }
        attempts++;
    }
    if (attempts == MAX_RETRIES) {
        return State::ERROR;
    }
    player_index_ = (player_index_ + 1) % players_.size();
    return State::ONGOING;
}

std::ostream &Game::DisplayState(std::ostream &out_stream) {
    switch (state_) {
        case State::ONGOING: {
            out_stream << "Round " << num_rounds_ << "\n";
            board_.Display(out_stream);
        }
            break;
        case State::DONE: {
            board_.Display(out_stream);
            out_stream << "And the winner is...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            out_stream << winner_ << "\nCongratulations!";
        }
            break;
        case State::ERROR: {
            out_stream << "No winners, only losers here.";
        }
            break;
        default: {
            out_stream << "what is life?";
        }
            break;
    }
    out_stream << std::endl;
    return out_stream;
}