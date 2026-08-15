/**
 * Represents a chess piece with its type and color.
 * 
 */
# ifndef CHESSLAB_PIECE_HPP
# define CHESSLAB_PIECE_HPP

#include <chesslab/color.hpp>

namespace chesslab {
    
/// @brief - Represents the type of a chess piece.
enum class PieceType {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

/// @brief - Represents a chess piece with its type and color.
struct Piece {
    /// @brief - The type of the piece.
    PieceType type;
    /// @brief - The color of the piece.    
    Color color;    
};

}

#endif
