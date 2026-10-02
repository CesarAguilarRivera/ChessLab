#include <chesslab/position.hpp>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace chesslab {

namespace {

Piece pieceFromFENCharacter(char character) {
    Color color = std::isupper(static_cast<unsigned char>(character))
        ? Color::White
        : Color::Black;

    char pieceCharacter = static_cast<char>(
        std::tolower(static_cast<unsigned char>(character)));

    switch (pieceCharacter) {
        case 'p': return {PieceType::Pawn, color};
        case 'n': return {PieceType::Knight, color};
        case 'b': return {PieceType::Bishop, color};
        case 'r': return {PieceType::Rook, color};
        case 'q': return {PieceType::Queen, color};
        case 'k': return {PieceType::King, color};
        default: throw std::invalid_argument("Invalid FEN piece character");
    }
}

} // namespace

Position::Position() : sideToMove_(Color::White) {
    // Board starts empty for now.
}

std::optional<Piece> Position::pieceAt(Square square) const {
    // Convert the Square enum to an index in the board array
    return board[static_cast<std::size_t>(square)];
}

Color Position::sideToMove() const {
    return sideToMove_;
}

Position Position::fromFEN(const std::string& fen) {
    std::istringstream fenStream(fen);
    std::string boardField;
    std::string activeColorField;
    std::string extraField;

    if (!(fenStream >> boardField >> activeColorField) || fenStream >> extraField) {
        throw std::invalid_argument("FEN must contain exactly two fields");
    }

    Position position;
    int rank = 7;
    int file = 0;

    for (char character : boardField) {
        if (character == '/') {
            if (file != 8 || rank == 0) {
                throw std::invalid_argument("Invalid FEN rank");
            }

            --rank;
            file = 0;
        } else if (character >= '1' && character <= '8') {
            file += character - '0';
            if (file > 8) {
                throw std::invalid_argument("FEN rank is too wide");
            }
        } else {
            if (file >= 8) {
                throw std::invalid_argument("FEN rank is too wide");
            }

            Piece piece = pieceFromFENCharacter(character);
            Square square = static_cast<Square>(rank * 8 + file);
            position.setPiece(square, piece);
            ++file;
        }
    }

    if (rank != 0 || file != 8) {
        throw std::invalid_argument("FEN must contain exactly eight complete ranks");
    }

    if (activeColorField == "w") {
        position.sideToMove_ = Color::White;
    } else if (activeColorField == "b") {
        position.sideToMove_ = Color::Black;
    } else {
        throw std::invalid_argument("Invalid FEN active color");
    }

    return position;
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
} // namespace chesslab
