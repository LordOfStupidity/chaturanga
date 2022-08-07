#ifndef LEGAL_MOVES_HPP
#define LEGAL_MOVES_HPP 1

#include <vector>

bool legalState(bool lastColor);
std::vector<int> legalMoves(int pos, bool lastColor);
float evalBoardState();
void compMove(int depth, bool lastColor);

#endif // !LEGAL_MOVES_HPP