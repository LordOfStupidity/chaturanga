#ifndef LOGENTRY_HPP
#define LOGENTRY_HPP 1

#include <bits/stdc++.h>

#include "chaturanga_piece.hpp"

struct logEntry {
public:
    std::pair<int, int> move;
    chaturangaPiece A;
    chaturangaPiece B;
    logEntry(chaturangaPiece _A, chaturangaPiece _B, int locA, int locB) {
        move.first = locA;
        move.second = locB;
        A = _A;
        B = _B;
    };
};

#endif // !LOGENTRY_HPP