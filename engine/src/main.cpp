#include <chesslab/position.hpp>
#include <iostream>

int main() {
    chesslab::Position position;

    // Example usage: Set a white pawn on A2
    chesslab::Piece whitePawn{chesslab::PieceType::Pawn, chesslab::Color::White};
    position.setPiece(chesslab::Square::A2, whitePawn);

    // Check if the piece is set correctly.
    auto piece = position.pieceAt(chesslab::Square::A2);
    if (piece) {
        std::cout << "Piece at A2: Exists\n";
    } else {
        std::cout << "Piece at A2: Does not exist\n";
    }

    position.printBoard();

    return 0;
}
