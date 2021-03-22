#include "Board.h"

std::ostream &Board::Display(std::ostream &out_stream) const {
    out_stream << "Board:\n   ";
    for (size_t c = 0; c < num_cols_; ++c) {
        out_stream << c + 1 << " ";
    }
    out_stream << std::endl;

    for (size_t r = 0; r < num_rows_; ++r) {
        out_stream << r + 1 << "  ";
        for (size_t c = 0; c < num_cols_; ++c) {
            out_stream << grid_[r][c] << " ";
        }
        out_stream << std::endl;
    }
    return out_stream;
}

bool Board::AreFourConnected(char token) const {
    if (token == EMPTY_CELL) return false;

    // horizontalCheck 
    for (int j = 0; j < num_rows_ - 3; j++) {
        for (int i = 0; i < num_cols_; i++) {
            if (grid_[i][j] == token && grid_[i][j + 1] == token && grid_[i][j + 2] == token &&
                grid_[i][j + 3] == token) {
                return true;
            }
        }
    }
    // verticalCheck
    for (int i = 0; i < num_cols_ - 3; i++) {
        for (int j = 0; j < num_rows_; j++) {
            if (grid_[i][j] == token && grid_[i + 1][j] == token && grid_[i + 2][j] == token &&
                grid_[i + 3][j] == token) {
                return true;
            }
        }
    }
    // ascendingDiagonalCheck 
    for (int i = 3; i < num_cols_; i++) {
        for (int j = 0; j < num_rows_ - 3; j++) {
            if (grid_[i][j] == token && grid_[i - 1][j + 1] == token && grid_[i - 2][j + 2] == token &&
                grid_[i - 3][j + 3] == token)
                return true;
        }
    }
    // descendingDiagonalCheck
    for (int i = 3; i < num_cols_; i++) {
        for (int j = 3; j < num_rows_; j++) {
            if (grid_[i][j] == token && grid_[i - 1][j - 1] == token && grid_[i - 2][j - 2] == token &&
                grid_[i - 3][j - 3] == token)
                return true;
        }
    }
    return false;
}

bool Board::IsValid(size_t column) const {
    if (column >= num_cols_) return false;
    return grid_[0][column] == EMPTY_CELL;
}

void Board::SetCellUnsafe(size_t column, char token) {
    for (size_t r = num_rows_ - 1; r >= 0; --r) {
        if (grid_[r][column] == EMPTY_CELL) {
            grid_[r][column] = token;
            return;
        }
    }
}