#ifndef CHATURANGA_BOARD_HPP
#define CHATURANGA_BOARD_HPP 1

#include <stack>

#include "chaturangaSquare.hpp"
#include "logEntry.hpp"

class chaturangaBoard {
public:
    /**
     * @brief Initializes the board
     */
    void initiate();

    /**
     * @brief Set the Pieces object
     */
    void setPieces();

    /**
     * @brief Get the legal moves for the chess piece
     * 
     * @param a
     *      x-coordinate of the piece
     * @param b
     *      y-coordinate of the piece 
     */
    void getLegal(int a, int b);

    /**
     * @brief reset legal moves
     */
    void resetLegal();

    /**
     * @brief Moves the piece to new position
     * 
     * @param a 
     *      x-coordinate of the new position
     * @param b 
     *      y-coordinate of the new position
     */
    void move(int a, int b);

    /**
     * @brief Moves the piece to new position
     * 
     * @param a
     *      x-coordinate of the new position
     * @param b 
     *      y-coordinate of the new position
     * @param lastX 
     *      x-coordinate of the current position
     * @param lasty 
     *      y-coordinate of the current position
     */
    void move(int a, int b, int lastX, int lasty);

    /**
     * @brief Behavior of the application on a mouse click
     * 
     * @param button 
     *      The type of button that is clicked
     * @param state
     *      current state of OpenGL renderer
     * @param x
     *      x-coordinates of the square
     * @param y 
     *      y-coordinates of the square
     */
    void click(int button, int state, int x, int y);

    /**
     * @brief clears the move log
     */
    void emptyMoveLog();

    /**
     * @brief Undo previous move
     */
    void undo();

    /**
     * @brief Check whether if there's any other piece remaining on the board
     * 
     */
    bool remainingPieces(bool lastColor);

public:
    chaturangaSquare board[8][8];
private:
    std::stack<logEntry> move_stack;
    bool lastColor;
    int lastx, lasty;
};

chaturangaBoard cb;

#endif // !CHATURANGA_BOARD_HPP