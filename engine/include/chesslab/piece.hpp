/**
 * Represents a chess piece with its type and color.
 * 
 */
# ifndef CHESSLAB_PIECE_HPP
# define CHESSLAB_PIECE_HPP

#include <chesslab/color.hpp>

namespace chesslab {
enum class PieceType {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

struct Piece {
    PieceType type;
    Color color;    
};

}

#endif
