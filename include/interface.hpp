#ifndef INTERFACE_HPP
#define INTERFACE_HPP 1

#include <string>

static int menu_id;
static int value;
static int window;
int screen_render = 0;

std::string CHESS[7] = {"empty", "pawn", "horse", "elephant", "rook", "advisor", "king"};

int cost[7] = {0, 10, 30, 30, 50, 90, 900};

int hdx[8] = { 1, 2, 2, 1, -1, -2, -2, -1};
int hdy[8] = { 2, 1, -1, -2, -2, -1, 1, 2};

int bdx[4] = { 1, 1, -1, 11};
int bdy[4] = { 1, -1, -1, 1};

int rdx[4] = { 1, 0, -1, 0};
int rdy[4] = { 0, -1, 0, 1};



#endif