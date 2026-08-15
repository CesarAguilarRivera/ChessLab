#include <chesslab/position.hpp>
#include <iostream>

namespace chesslab {

Position::Position() : sideToMove(Color::White) {
    // Board starts empty for now.
}

std::optional<Piece> Position::pieceAt(Square square) const {
    // Convert the Square enum to an index in the board array
    return board[static_cast<std::size_t>(square)];
}

void Position::setPiece(Square square, Piece piece) {
    // Convert the Square enum to an index in the board array
    board[static_cast<std::size_t>(square)] = piece;
}

void Position::removePiece(Square square) {
    board[static_cast<std::size_t>(square)] = std::nullopt;
}

void Position::printBoard() const {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            Square square = static_cast<Square>(rank * 8 + file);
            auto pieceOpt = pieceAt(square);
            if (pieceOpt) {
                const Piece& piece = pieceOpt.value();
                char pieceChar;
                switch (piece.type) {
                    case PieceType::Pawn:   pieceChar = 'P'; break;
                    case PieceType::Knight: pieceChar = 'N'; break;
                    case PieceType::Bishop: pieceChar = 'B'; break;
                    case PieceType::Rook:   pieceChar = 'R'; break;
                    case PieceType::Queen:  pieceChar = 'Q'; break;
                    case PieceType::King:   pieceChar = 'K'; break;
                }
                if (piece.color == Color::Black) {
                    pieceChar = tolower(pieceChar);
                }
                std::cout << pieceChar << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}
}
