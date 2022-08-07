#ifndef LOGENTRY_HPP
#define LOGENTRY_HPP 1

#include <bits/stdc++.h>

#include "chaturangaPiece.hpp"

class logEntry {
public:
    logEntry(chaturangaPiece _A, chaturangaPiece _B, int locA, int locB);

public:
    std::pair<int, int> move;
    chaturangaPiece A;
    chaturangaPiece B;
};

#endif // !LOGENTRY_HPP