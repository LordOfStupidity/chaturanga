#ifndef INTERFACE_HPP
#define INTERFACE_HPP 1

#include <vector>

std::vector<int> legalMoves(int pos, bool lastColor);
void compMove(int depth, bool lastColor);


#endif