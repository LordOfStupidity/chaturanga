#include "logEntry.hpp"

logEntry::logEntry(chaturangaPiece _A, chaturangaPiece _B, int locA, int locB) {
    move.first = locA;
    move.second = locB;
    A = _A;
    B = _B;
}