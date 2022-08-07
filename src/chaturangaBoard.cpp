#include <GL/glut.h>
#include "chaturangaBoard.hpp"
#include "interface.hpp"

void chaturangaBoard::initiate() {
    lastColor = false;
    bool color = true;
    int x = 100, y = 100;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].x = y;
            board[i][j].y = x;
            board[i][j].color = !color;

            glRecti(x, y, x + 100, y + 100);

            x += 100;

            if (color) {
                glColor3f(0.941, 0.941, 0.874);
            } else {
                glColor3f(0.247, 0.345, 0.4);
            }

            color = !color;
        }

        if (color) {
            glColor3f(0.941, 0.941, 0.874);
        } else {
            glColor3f(0.247, 0.345, 0.4);
        }

        color = !color;
        x = 100;
        y += 100;
    }
}

void chaturangaBoard::setPieces() {
    int order[8] = {4, 2, 3, 5, 6, 3, 2, 4};

    for (int i = 0; i < 8; i++) {
        board[i][1].curr.setPieceDef(1);
        board[i][1].curr.setColor(true);
        
        board[i][0].curr.setColor(true);
        board[i][0].curr.setPieceDef(order[i]);
        
        board[i][6].curr.setColor(false);
        board[i][6].curr.setPieceDef(1);
        
        board[i][7].curr.setColor(false);
        board[i][7].curr.setPieceDef(order[i]);
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 2; j < 6; j++) {
            board[i][j].curr.setPieceDef(0);
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].drawPiece();
        }
    }
}

void chaturangaBoard::getLegal(int a, int b) {
    resetLegal();

    std::vector<int> moves = legalMoves(a*8 + b, lastColor);
    
    for (int i = 0; i < moves.size(); i++) {
        board[moves[i] / 8][moves[i] % 8].setAsLegal();
    }
    
    glFlush();
}

void chaturangaBoard::resetLegal() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].setNormal();
        }
    }
}

void chaturangaBoard::move(int a, int b) {
    resetLegal();

    if (board[lastx][lasty].curr.getPieceDef() == 6 && abs(a - lastx) == 2) {
        if (a > lastx) {
            logEntry m(board[a + 1][b].curr, board[a - 1][b].curr, (a + 1) * 8 + b, (a - 1) * 8 + b);
            move_stack.push(m);
            
            board[a - 1][b].curr.setPieceDef(4);
            board[a - 1][b].curr.setColor(board[lastx][lasty].curr.getColor());
            
            board[7][b].curr.setPieceDef(0);
            
            board[a - 1][b].drawPiece();
            board[a + 1][b].setClear();
        } else {
            logEntry n(board[a - 2][b].curr, board[a + 1][b].curr, (a - 2) * 8 + b, (a + 1) * 8 + b);
            move_stack.push(n);
            
            board[a + 1][b].curr.setPieceDef(4);
            board[a + 1][b].curr.setColor(board[lastx][lasty].curr.getColor());
            
            board[0][b].curr.setPieceDef(0);
            
            board[a + 1][b].drawPiece();
            board[a - 2][b].setClear();
        }
    }

    logEntry l(board[lastx][lasty].curr, board[a][b].curr, lastx * 8 + lasty, a * 8 + b);
    move_stack.push(l);

    board[a][b].curr.setPieceDef(board[lastx][lasty].curr.getPieceDef());
    board[a][b].curr.setColor(board[lastx][lasty].curr.getColor());
    board[lastx][lasty].curr.setPieceDef(0);

    if ((b == 0 || b == 7) && board[a][b].curr.getPieceDef() == 1) {
        board[a][b].curr.setPieceDef(5);
    }

    board[a][b].setClear();
    board[lastx][lasty].setClear();
    board[a][b].drawPiece();

    lastColor = !lastColor;

    glFlush();

    if (lastColor) {
        compMove(3, lastColor);
        
        bool stalemated = true;
        bool checkmated = true;

        for (int i = 0; i < 8 && stalemated; i++) {
            for (int j = 0; j < 8 && stalemated; j++) {
                if (board[i][j].curr.getPieceDef() != 0 && board[i][j].curr.getColor() != lastColor) {
                    if (remainingPieces(lastColor)) {
                        stalemated = false;
                    }

                    if (legalMoves(i * 8 + j, lastColor).size() > 0) {
                        checkmated = false;
                    }
                }
            }
        }

        if (stalemated) {
            // TODO: Display you lost screen
        }

        if (checkmated) {
            // TODO: Display you lost screen
        }
    }
}

void chaturangaBoard::move(int a, int b, int lastx, int lasty) {
    if (board[lastx][lasty].curr.getPieceDef() == 6 && abs(a - lastx) == 2) {
        if (a > lastx) {
            logEntry m(board[a + 1][b].curr, board[a - 1][b].curr, (a + 1) * 8 + b, (a - 1) * 8 + b);
            move_stack.push(m);

            board[a - 1][b].curr.setPieceDef(4);
            board[a - 1][b].curr.setColor(board[lastx][lasty].curr.getColor());
            board[7][b].curr.setPieceDef(0);
        } else {
            logEntry n(board[a - 2][b].curr, board[a+1][b].curr, (a - 2) * 8 + b, (a + 1) * 8 + b);
            move_stack.push(n);

            board[a + 1][b].curr.setPieceDef(4);
            board[a + 1][b].curr.setColor(board[lastx][lasty].curr.getColor());
            board[0][b].curr.setPieceDef(0);
        }
    }

    logEntry l(board[lastx][lasty].curr, board[a][b].curr, lastx * 8 + lasty, a * 8 + b);
    move_stack.push(l);

    board[a][b].curr.setPieceDef(board[lastx][lasty].curr.getPieceDef());
    board[a][b].curr.setColor(board[lastx][lasty].curr.getColor());
    board[lastx][lasty].curr.setPieceDef(0);

    if ((b == 0 || b == 7) && board[a][b].curr.getPieceDef() == 1) {
        board[a][b].curr.setPieceDef(5);
    }

    lastColor = !lastColor;
}

void chaturangaBoard::click(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int a = x;
        int b = 1000 - y;
        a /= 100;
        b /= 100;
        a--, b--;

        if (a >= 0 && a < 8 && b >= 0 && b < 8) {
            if (board[a][b].legal == true) {
                move(a, b);
            } else {
                char c = 'A' + b;
                getLegal(a, b);
                lastx = a, lasty = b;
            }
        }
    }
}

void chaturangaBoard::emptyMoveLog() {
    while (!move_stack.empty()) {
        move_stack.pop();
    }
}

void chaturangaBoard::undo() {
    if (move_stack.empty()) {
        return;
    }

    logEntry lg = move_stack.top();
    move_stack.pop();

    int last = lg.move.second;
    int prev = lg.move.first;

    chaturangaPiece prevPiece = lg.A;
    chaturangaPiece lastPiece = lg.B;

    lastx /= 8;
    lasty %= 8;

    int a = prev / 8;
    int b = prev % 8;

    board[a][b].curr.setPieceDef(prevPiece.getPieceDef());
    board[a][b].curr.setColor(prevPiece.getColor());

    board[lastx][lasty].curr.setPieceDef(lastPiece.getPieceDef());
    board[lastx][lasty].curr.setColor(lastPiece.getColor());

    board[a][b].setClear();
    board[lastx][lasty].setClear();
    
    board[a][b].drawPiece();
    board[lastx][lasty].drawPiece();

    lastColor = !lastColor;

    if (prevPiece.getPieceDef() == 6 && abs(a - lastx) > 1) {
        undo();
        lastColor = !lastColor;
    }
}

bool chaturangaBoard::remainingPieces(bool lastColor) {
    int x = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].curr.getPieceDef() == lastColor) {
                x++;
            } 
        }
    }

    return (x > 1) ? true : false;
}