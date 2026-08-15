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
        std::optional<Piece> pieceAt(Square square) const; 

    private:

        std::array<std::optional<Piece>, 64> board; // 8x8 chessboard represented as a 1D array
        Color sideToMove; // Color of the player to move
};


} // namespace chesslab

#endif // CHESSLAB_POSITION_HPP