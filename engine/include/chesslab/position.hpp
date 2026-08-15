/**
 * Represents a chess position, including the arrangement of pieces on the board and the side to move.
 * 
 */


# ifndef CHESSLAB_POSITION_HPP
# define CHESSLAB_POSITION_HPP

#include <array> 
#include <optional>

#include <chesslab/piece.hpp>
#include <chesslab/square.hpp>

namespace chesslab {

class Position {
    public:
        /// @brief - Constructs a new Position object with an empty board and sets the side to move to White.
        Position(); 

        /// @brief - Gets the piece at the specified square, if it exists.
        /// @param square - The square to check.
        /// @return - The piece at the square, or std::nullopt if the square is empty.
        std::optional<Piece> pieceAt(Square square) const;

        /// @brief  - Sets the piece at the specified square.
        /// @param square - The square where the piece will be placed.
        /// @param piece - The piece to place on the square.
        void setPiece(Square square, Piece piece);

        /// @brief - Removes the piece from the specified square.
        /// @param square - The square from which to remove the piece.
        void removePiece(Square square);

        /// @brief - Prints the current state of the chessboard to the console.
        void printBoard() const; 

    private:
        /// @brief - The chessboard represented as a 1D array of optional pieces.
        std::array<std::optional<Piece>, 64> board;
        /// @brief - The color of the side to move.
        Color sideToMove;
};


} // namespace chesslab

#endif // CHESSLAB_POSITION_HPP