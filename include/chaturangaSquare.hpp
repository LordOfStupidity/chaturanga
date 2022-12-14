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

public:
    chaturangaPiece curr;
private:
    int x, y;
    bool color;
    bool legal;

friend class chaturangaBoard;
};

#endif // !chaturanga_SQUARE_HPP