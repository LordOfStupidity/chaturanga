#ifndef MOVES_HPP
#define MOVES_HPP 1

#include <vector>

bool legalState(bool lastColor);
std::vector<int> legalMoves(int pos, bool lastColor);
void compMove(int depth, bool lastColor);

#endif // !MOVES_HPP