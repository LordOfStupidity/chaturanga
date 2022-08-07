#include <vector>
#include <algorithm>

#include "evaluate.hpp"
#include "chaturangaBoard.hpp"
#include "moves.hpp"
#include "interface.hpp"

float evalBoardState() {
    float val = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            bool pieceColor = cb.board[i][j].curr.getColor();
            float colorFactor = pieceColor ? 1.0 : -1.0;
            float piecePos = 0;

            switch (cb.board[i][j].curr.getPieceDef()) {
            case 0:
                break;
            case 1:
                piecePos += cost[1] + (pieceColor ? pawnEvalWhite[i][j] : pawnEvalBlack[i][j]);
                break;
            case 2:
                piecePos += cost[2] + horseEval[i][j];
                break;
            case 3:
                piecePos += cost[3] + (pieceColor ? elephantEvalWhite[i][j] : elephantEvalBlack[i][j]);
                break;
            case 4:
                piecePos += cost[4] + (pieceColor ? rookEvalWhite[i][j] : rookEvalBlack[i][j]);
                break;
            case 5:
                piecePos += cost[5] + evalAdvisor[i][j];
                break;
            case 6:
                piecePos += cost[6] + (pieceColor ? kingEvalWhite[i][j] : kingEvalBlack[i][j]);
                break;
            }

            piecePos *= colorFactor;
            val += piecePos;
        }
    }
}

int minimax(int depth, int alpha, int beta, bool lastColor) {
    if (depth == 0) {
        return evalBoardState();
    }

    std::vector<std::pair<int, int>> allMoves;
    std::vector<int> curr;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (cb.board[i][j].curr.getPieceDef() != 0 && cb.board[i][j].curr.getColor() != lastColor) {
                curr = legalMoves(i * 8 + j, lastColor);

                for (auto x : curr) {
                    allMoves.push_back({i * 8 + j, x});
                }
            }
        }
    }

    if ((!lastColor)) {
        int bestMove = INT_MIN;
        for (int i = 0; i < allMoves.size(); i++) {
            int from = allMoves[i].first;
            int to = allMoves[i].second;

            cb.move(to / 8, to % 8, from / 8, from % 8);
            
            bestMove = std::max(bestMove, minimax(depth - 1, alpha, beta, !lastColor));
            
            cb.undo();
            alpha = std::min(beta, bestMove);

            if (beta <= alpha) {
                return bestMove;
            }
        }
    } else {
        int bestMove = INT_MAX;
        for (int i = 0; i < allMoves.size(); i++) {
            int from = allMoves[i].first;
            int to = allMoves[i].second;

            cb.move(to / 8, to % 8, from / 8, from % 8);

            bestMove = std::min(bestMove, minimax(depth - 1, alpha, beta, !lastColor));
            
            cb.undo();

            beta = std::min(beta, bestMove);

            if (beta <= alpha) {
                return bestMove;
            }
        }

        return bestMove;
    }
}