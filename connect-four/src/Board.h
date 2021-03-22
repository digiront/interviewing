#include <iostream>
#include <vector>

#ifndef CPP_SAMPLES_BOARD_H
#define CPP_SAMPLES_BOARD_H


class Board {
    static constexpr char EMPTY_CELL = '_';
public:
    Board(int num_ros, int num_cols) : num_rows_(num_ros), num_cols_(num_cols),
                                       grid_(num_ros, std::vector<char>(num_cols, EMPTY_CELL)) {}

    std::ostream &Display(std::ostream &out_stream) const;

    bool AreFourConnected(char token) const;

    bool IsValid(size_t column) const;

    void SetCellUnsafe(size_t column, char token);

private:
    const int num_rows_;
    const int num_cols_;
    std::vector<std::vector<char>> grid_;
};

#endif //CPP_SAMPLES_BOARD_H
