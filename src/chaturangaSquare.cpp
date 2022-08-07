#include "chaturangaSquare.hpp"
#include "blackPiece.hpp"
#include "whitePiece.hpp"
#include <GL/glut.h>

chaturangaSquare::chaturangaSquare() {
    x = 0;
    y = 0;
    color = true;
    legal = false;
}

void chaturangaSquare::drawPiece() {
    if (curr.getPieceDef() == 0) {
        
        if (color) {
            glColor3f(0.941, 0.941, 0.874);
        } else {
            glColor3f(0.247, 0.345, 0.4);
        }

        glRecti(x + 10, y + 10, x + 90, y + 90);

        return;
    }

    if (curr.getColor()) {
        switch (curr.getPieceDef()) {

        case 1:
            drawwP(x+10, y+10);
            break;

        case 2:
            drawwR(x + 10, y + 10);
            break;

        case 3:
            drawwH(x + 10, y + 10);
            break;

        case 4:
            drawwE(x + 10, y + 10);
            break;

        case 5:
            drawwA(x + 10, y + 10);
            break;

        case 6:
            drawwK(x + 10, y + 10);
            break;
        }
    } else {
        switch (curr.getPieceDef()) {

        case 1:
            drawbP(x+10, y+10);
            break;

        case 2:
            drawbR(x + 10, y + 10);
            break;

        case 3:
            drawbH(x + 10, y + 10);
            break;

        case 4:
            drawbE(x + 10, y + 10);
            break;

        case 5:
            drawbA(x + 10, y + 10);
            break;

        case 6:
            drawbK(x + 10, y + 10);
            break;
        }
    }
}

void chaturangaSquare::setSquare(chaturangaPiece cp) {
    curr.setColor(cp.getColor());
    curr.setPieceDef(cp.getPieceDef());
}

void chaturangaSquare::setAsLegal() {
    glColor3f(0.7421, 0.9196, 0.62109);
    glRecti(x, y, x + 100, y + 100);
    drawPiece();
    legal = true;
}

void chaturangaSquare::setNormal() {
    legal = false;
    setClear();
    drawPiece();
}

void chaturangaSquare::setClear() {
    if (color) {
        glColor3f(0.941, 0.941, 0.874);
    } else {
        glColor3f(0.247, 0.345, 0.4);
    }

    glRecti(x, y, x + 100, y + 100);
}