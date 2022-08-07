#include "moves.hpp"
#include "chaturangaBoard.hpp"
#include "interface.hpp"

bool legalState(bool lastColor) {
    int a, b;
    bool found = false;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (cb.board[i][j].curr.getPieceDef() == 6 && (cb.board[i][j].curr.getColor() == lastColor)) {
                a = i, b = j;
            }
        }
    }

    for (int i = 0; i < 8; i++) {                   // check if the horse is attacking
        int x = a + bdx[i];
        int y = b + bdy[i];

        while (x >= 0 && x < 8 && y >= 0 && y < 8) {
            if (cb.board[x][y].curr.getPieceDef() != 0) {
                if (cb.board[x][y].curr.getColor() == lastColor || cb.board[x][y].curr.getPieceDef() == 2 || cb.board[x][y].curr.getPieceDef() == 4) {
                } else if (cb.board[x][y].curr.getPieceDef() == 1) {    // found opposite color pawn diagonally
                    if((x == a + 1 || x == a - 1) && y == (b + ((lastColor) ? 1 : -1))) {
                        return false;
                    }
                } else if (cb.board[x][y].curr.getPieceDef() == 6) {
                    if ((x == a + 1 || x == a - 1) && (y == b + 1 || y == b - 1)) { // Found opposite color king diagonally
                        return false;
                    }
                } else if (cb.board[x][y].curr.getPieceDef() == 3) {
                    return false;
                } else if (cb.board[x][y].curr.getPieceDef() == 5) {
                    return false;
                }
                
                break;
            } else {
                x += bdx[i];
                y += bdy[i];
            }
        }
    }

    for (int i = 0; i < 4; i++) {               // Cheking diagonal attack on king
        int x = a + rdx[i];
        int y = b + rdy[i];

        while (x >= 0 && y < 8 && y >= 0 && y < 8) {
            if (cb.board[x][y].curr.getPieceDef() != 0) {
                if (cb.board[x][y].curr.getColor() == lastColor || cb.board[x][y].curr.getPieceDef() == 1 || cb.board[x][y].curr.getPieceDef() == 2 || cb.board[x][y].curr.getPieceDef() == 3) {

                } else if (cb.board[x][y].curr.getPieceDef() == 6) {    // found opposite color king HV
                    if (abs(x - a) < 2 && abs(y - b) < 2) {
                        return false;
                    }
                } else if (cb.board[x][y].curr.getPieceDef() == 4) {    // Found opposite color Rook HV
                    return false;
                } else if (cb.board[x][y].curr.getPieceDef() == 5) {
                    return false;
                }
                break;
            } else {
                x += rdx[i];
                y += rdy[i];
            }
        }
    }

    return true;
}

std::vector<int> legalMoves(int pos, bool lastColor) {
    int a = pos / 8;
    int b = pos % 8;
    std::vector<int> moves;

    if (cb.board[a][b].curr.getPieceDef() == 0 || cb.board[a][b].curr.getColor() == lastColor) {
        return moves;
    }

    switch (cb.board[a][b].curr.getPieceDef()) {
    
    // Pawn
    case 1:
        {
            int x = a;
            int y = b + ((cb.board[a][b].curr.getColor()) ? 1 : -1);

            if (x >= 0 && x < 8 && y >= 0 && y < 8 && cb.board[x][y].curr.getPieceDef() == 0) {
                cb.board[a][b].curr.setPieceDef(0);
                cb.board[x][y].curr.setPieceDef(1);
                cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                if (legalState(!lastColor)) {
                    moves.push_back(x * 8 + y);
                }

                cb.board[a][b].curr.setPieceDef(1);
                cb.board[x][y].curr.setPieceDef(0);
            }

            x--;

            if (x >= 0 && x < 8 && y < 8 && cb.board[x][y].curr.getPieceDef() != 0 && cb.board[x][y].curr.getColor() == lastColor) {
                int help = cb.board[x][y].curr.getPieceDef();

                cb.board[a][b].curr.setPieceDef(0);
                cb.board[x][y].curr.setPieceDef(1);
                cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                if (legalState(!lastColor)) {
                    moves.push_back(x * 8 + y);
                }

                cb.board[a][b].curr.setPieceDef(1);
                cb.board[a][b].curr.setPieceDef(help);
                cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
            }

            x += 2;

            if (x >= 0 && x < 8 && y >= 0 && cb.board[x][y].curr.getPieceDef() != 0 && cb.board[x][y].curr.getColor() == lastColor) {
                int help = cb.board[x][y].curr.getPieceDef();

                cb.board[a][b].curr.setPieceDef(0);
                cb.board[x][y].curr.setPieceDef(1);
                cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                if (legalState(!lastColor)) {
                    moves.push_back(x * 8 + y);
                }

                cb.board[a][b].curr.setPieceDef(1);
                cb.board[a][b].curr.setPieceDef(help);
                cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
            }

            x--;
        }
        break;
    
    // Horse
    case 2:
        {
            for (int i = 0; i < 8; i++) {
                int x = a + hdx[i];
                int y = b + hdy[i];

                if (x < 0 || x > 7 || y < 0 || y > 7) {
                    continue;
                }

                if (cb.board[x][y].curr.getPieceDef() == 0 || cb.board[x][y].curr.getColor() == lastColor) {
                    int help = cb.board[x][y].curr.getPieceDef();

                    cb.board[a][b].curr.setPieceDef(0);
                    cb.board[x][y].curr.setPieceDef(2);
                    cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                    if (legalState(!lastColor)) {
                        moves.push_back(x * 8 + y);
                    }

                    cb.board[a][b].curr.setPieceDef(2);
                    cb.board[x][y].curr.setPieceDef(help);
                    cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
                }
            }
        }
        break;

    // Elephant
    case 3:
        {
            for (int i = 0; i < 4; i++) {
                int x = a + bdx[i];
                int y = b + bdy[i];

                while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    if (cb.board[x][y].curr.getPieceDef() != 0) {
                        if (cb.board[x][y].curr.getColor() == lastColor) {
                            int help = cb.board[x][y].curr.getPieceDef();

                            cb.board[a][b].curr.setPieceDef(0);
                            cb.board[x][y].curr.setPieceDef(3);
                            cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                            if (legalState(!lastColor)) {
                                moves.push_back(x * 8 + y);
                            }

                            cb.board[a][b].curr.setPieceDef(3);
                            cb.board[x][y].curr.setPieceDef(help);
                            cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
                        }
                        break;
                    } else {
                        cb.board[a][b].curr.setPieceDef(0);
                        cb.board[x][y].curr.setPieceDef(3);
                        cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());
                        
                        if (legalState(!lastColor)) {
                            moves.push_back(x * 8 + y);
                        }

                        cb.board[a][b].curr.setPieceDef(3);
                        cb.board[x][y].curr.setPieceDef(0);
                        
                        x += rdx[i];
                        y += rdy[i];
                    }
                }
            }
        }
        break;

    // Rook
    case 4:
        {
            for (int i = 0; i < 4; i++) {
                int x = a + rdx[i];
                int y = b + rdy[i];

                while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    if (cb.board[x][y].curr.getPieceDef() != 0) {
                        if (cb.board[x][y].curr.getColor() == lastColor) {
                            int help = cb.board[x][y].curr.getPieceDef();

                            cb.board[a][b].curr.setPieceDef(0);
                            cb.board[x][y].curr.setPieceDef(4);
                            cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                            if (legalState(!lastColor)) {
                                moves.push_back(x * 8 + y);
                            }

                            cb.board[a][b].curr.setPieceDef(4);
                            cb.board[x][y].curr.setPieceDef(help);
                            cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
                        }
                        break;
                    } else {
                        cb.board[a][b].curr.setPieceDef(0);
                        cb.board[x][y].curr.setPieceDef(4);
                        cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());
                        
                        if (legalState(!lastColor)) {
                            moves.push_back(x * 8 + y);
                        }

                        cb.board[a][b].curr.setPieceDef(4);
                        cb.board[x][y].curr.setPieceDef(0);
                        
                        x += rdx[i];
                        y += rdy[i];
                    }
                }
            }
        }
        break;

    // Advisor
    case 5:
        {
            for (int i = 0; i < 4; i++) {
                int x = a + bdx[i];
                int y = b + bdy[i];

                while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    if (cb.board[x][y].curr.getPieceDef() != 0) {
                        if (cb.board[x][y].curr.getColor() == lastColor) {
                            int help = cb.board[x][y].curr.getPieceDef();

                            cb.board[a][b].curr.setPieceDef(0);
                            cb.board[x][y].curr.setPieceDef(5);
                            cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                            if (legalState(!lastColor)) {
                                moves.push_back(x * 8 + y);
                            }

                            cb.board[a][b].curr.setPieceDef(5);
                            cb.board[x][y].curr.setPieceDef(help);
                            cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
                        }
                        break;
                    } else {
                        cb.board[a][b].curr.setPieceDef(0);
                        cb.board[x][y].curr.setPieceDef(5);
                        cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                        if (legalState(!lastColor)) {
                            moves.push_back(x * 8 + y);
                        }

                        cb.board[a][b].curr.setPieceDef(5);
                        cb.board[x][y].curr.setPieceDef(0);
                        x += rdx[i];
                        y += rdy[i];
                    }
                }
            }

            for (int i = 0; i < 4; i++) {
                int x = a + rdx[i];
                int y = b + rdy[i];

                while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    if(cb.board[x][y].curr.getPieceDef() != 0) {
                        if (cb.board[x][y].curr.getColor() == lastColor) {
                            int help = cb.board[x][y].curr.getPieceDef();

                            cb.board[a][b].curr.setPieceDef(0);
                            cb.board[x][y].curr.setPieceDef(5);
                            cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                            if (legalState(!lastColor)) {
                                moves.push_back(x * 8 + y);
                            }

                            cb.board[a][b].curr.setPieceDef(5);
                            cb.board[x][y].curr.setPieceDef(help);
                            cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
                        }
                            break;
                    } else {
                        cb.board[a][b].curr.setPieceDef(0);
                        cb.board[x][y].curr.setPieceDef(5);
                        cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                        if (legalState(!lastColor)) {
                            moves.push_back(x * 8 + y);
                        }

                        cb.board[a][b].curr.setPieceDef(5);
                        cb.board[x][y].curr.setPieceDef(0);
                        
                        x += rdx[i];
                        y += rdy[i];
                    }
                }
            }
        }
        break;

    // king
    case 6:
        {
            // check for horizontal and vertical moves
            for (int i = 0; i < 4; i++) {
                int x = a + bdx[i];
                int y = b + rdy[i];

                if ((x >= 0 && x < 8 && y >= 0 && y < 8) && (cb.board[x][y].curr.getPieceDef() == 0 || cb.board[x][y].curr.getColor() == lastColor)) {
                    int help = cb.board[x][y].curr.getPieceDef();

                    cb.board[a][b].curr.setPieceDef(0);
                    cb.board[x][y].curr.setPieceDef(6);
                    cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                    if (legalState(!lastColor)) {
                        moves.push_back(x * 8 + y);
                    }

                    cb.board[a][b].curr.setPieceDef(6);
                    cb.board[x][y].curr.setPieceDef(help);
                    cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
                }

                x = a + rdx[i];
                y = b + rdy[i];

                if ((x >= 0 && x < 8 && y >= 0 && y < 8) && (cb.board[x][y].curr.getPieceDef() == 0 || cb.board[x][y].curr.getColor() == lastColor)) {
                    int help = cb.board[x][y].curr.getPieceDef();

                    cb.board[a][b].curr.setPieceDef(0);
                    cb.board[x][y].curr.setPieceDef(6);
                    cb.board[x][y].curr.setColor(cb.board[a][b].curr.getColor());

                    if (legalState(!lastColor)) {
                        moves.push_back(x * 8 + y);
                    }

                    cb.board[a][b].curr.setPieceDef(6);
                    cb.board[x][y].curr.setPieceDef(help);
                    cb.board[x][y].curr.setColor(!cb.board[a][b].curr.getColor());
                }
            }
        }
        break;
    }

    return moves;
}