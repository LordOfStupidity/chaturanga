#include "chaturangaPiece.hpp"

chaturangaPiece::chaturangaPiece(int pd, bool c) {
    pieceDef = pd;
    color = c;
}

chaturangaPiece::chaturangaPiece() {
    pieceDef = 0;
    color = true;
}

void chaturangaPiece::setEmpty() {
    pieceDef = 0;
}

void chaturangaPiece::operator=(chaturangaPiece c) {
    this->pieceDef = c.getPieceDef();
    this->color = c.getColor();
}

int chaturangaPiece::getPieceDef() {
    return pieceDef;
}

bool chaturangaPiece::getColor() {
    return color;
}

void chaturangaPiece::setColor(bool c) {
    color = c;
}

void chaturangaPiece::setPieceDef(int c) {
    pieceDef = c;
}