#ifndef CHATURANGA_SQUARE_HPP
#define CHATURANGA_SQUARE_HPP 1

#include "chaturangaPiece.hpp"

class chaturangaSquare {
public:
    chaturangaSquare();
    
    void drawPiece();
    void setSquare(chaturangaPiece cp);
    void setAsLegal();
    void setNormal();
    void setClear();

private:
    int x, y;
    chaturangaPiece curr;
    bool color;
    bool legal;
};

#endif // !chaturanga_SQUARE_HPP