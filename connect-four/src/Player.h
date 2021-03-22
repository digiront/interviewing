#include <string>
#include <utility>

#ifndef CPP_SAMPLES_PLAYER_H
#define CPP_SAMPLES_PLAYER_H

struct Options {
    char token;
    std::string id;
};

class Player {
public:
    explicit Player(Options options) : options_(std::move(options)) {}

    virtual ~Player() = default;

    virtual char Token() { return options_.token; }

    virtual std::string Id() { return options_.id; }

    virtual size_t ChooseColumn() = 0;

private:
    const Options options_;
};

#endif //CPP_SAMPLES_PLAYER_H
