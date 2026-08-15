#include <chesslab/position.hpp>

namespace chesslab {

Position::Position() : sideToMove(Color::White) {
    // Board starts empty for now.
}

std::optional<Piece> Position::pieceAt(Square square) const {
    // Convert the Square enum to an index in the board array
    return board[static_cast<std::size_t>(square)];
}

}