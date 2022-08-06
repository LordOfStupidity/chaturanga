#ifndef CHATURANGA_PIECE_HPP
#define CHATURANGA_PIECE_HPP 1

class chaturangaPiece {
    // Lifecycle Management
public:
    /**
     * @brief Construct a new chaturanga Piece object
     * 
     * @param[in] pd
     *      The definition of the chaturangaPiece
     * @param[in] c
     *      the color of the chaturangaPiece(black, white)
     *      true: white
     *      false: black
     */
    chaturangaPiece(int pd, bool c);
    
    /**
     * @brief Construct a new chaturanga Piece object
     */
    chaturangaPiece();

    /**
     * @brief Set the Empty piece Definition object
     * 
     */
    void setEmpty();

    /**
     * @brief Define the behavior of '=' operator for chaturangaPiece class
     * 
     * @param[in] c 
     *      any chaturangapiece object
     */
    void operator=(chaturangaPiece c);

    /**
     * @brief Get the Piece Def of object
     * 
     * @return int 
     */
    int getPieceDef();

    /**
     * @brief Get the Color of object
     * 
     * @return true 
     * @return false 
     */
    bool getColor();

private:
    int pieceDef;
    bool color;
};

#endif // !CHATURANGA_PIECE_HPP