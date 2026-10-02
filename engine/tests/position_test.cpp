#include <chesslab/position.hpp>

#include <gtest/gtest.h>

#include <array>
#include <optional>
#include <stdexcept>
#include <string>

namespace chesslab {
namespace {

TEST(PositionTest, NewPositionStartsWithWhiteToMove) {
    Position position;

    EXPECT_EQ(position.sideToMove(), Color::White);
}

TEST(PositionTest, NewBoardStartsEmpty) {
    Position position;

    for (int square = 0; square < 64; ++square) {
        EXPECT_FALSE(position.pieceAt(static_cast<Square>(square)).has_value());
    }
}

TEST(PositionTest, SetPiecePlacesPieceOnSquare) {
    Position position;
    Piece whitePawn{PieceType::Pawn, Color::White};

    position.setPiece(Square::A2, whitePawn);

    EXPECT_TRUE(position.pieceAt(Square::A2).has_value());
}

TEST(PositionTest, PieceAtReturnsCorrectPiece) {
    Position position;
    Piece blackQueen{PieceType::Queen, Color::Black};

    position.setPiece(Square::D5, blackQueen);

    std::optional<Piece> piece = position.pieceAt(Square::D5);
    ASSERT_TRUE(piece.has_value());
    EXPECT_EQ(piece->type, PieceType::Queen);
    EXPECT_EQ(piece->color, Color::Black);
}

TEST(PositionTest, RemovePieceClearsSquare) {
    Position position;
    position.setPiece(Square::E4, {PieceType::Knight, Color::White});

    position.removePiece(Square::E4);

    EXPECT_FALSE(position.pieceAt(Square::E4).has_value());
}

TEST(PositionTest, LowAndHighSquaresMapCorrectly) {
    Position position;
    position.setPiece(Square::A1, {PieceType::Rook, Color::White});
    position.setPiece(Square::H8, {PieceType::King, Color::Black});

    ASSERT_TRUE(position.pieceAt(Square::A1).has_value());
    EXPECT_EQ(position.pieceAt(Square::A1)->type, PieceType::Rook);
    EXPECT_EQ(position.pieceAt(Square::A1)->color, Color::White);

    ASSERT_TRUE(position.pieceAt(Square::H8).has_value());
    EXPECT_EQ(position.pieceAt(Square::H8)->type, PieceType::King);
    EXPECT_EQ(position.pieceAt(Square::H8)->color, Color::Black);
}

TEST(PositionFENTest, ParsesStandardStartingBoard) {
    Position position = Position::fromFEN(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    const std::array<PieceType, 8> backRank{
        PieceType::Rook,
        PieceType::Knight,
        PieceType::Bishop,
        PieceType::Queen,
        PieceType::King,
        PieceType::Bishop,
        PieceType::Knight,
        PieceType::Rook
    };

    for (int file = 0; file < 8; ++file) {
        auto whiteBackRankPiece = position.pieceAt(static_cast<Square>(file));
        ASSERT_TRUE(whiteBackRankPiece.has_value());
        EXPECT_EQ(whiteBackRankPiece->type, backRank[file]);
        EXPECT_EQ(whiteBackRankPiece->color, Color::White);

        auto whitePawn = position.pieceAt(static_cast<Square>(8 + file));
        ASSERT_TRUE(whitePawn.has_value());
        EXPECT_EQ(whitePawn->type, PieceType::Pawn);
        EXPECT_EQ(whitePawn->color, Color::White);

        auto blackPawn = position.pieceAt(static_cast<Square>(48 + file));
        ASSERT_TRUE(blackPawn.has_value());
        EXPECT_EQ(blackPawn->type, PieceType::Pawn);
        EXPECT_EQ(blackPawn->color, Color::Black);

        auto blackBackRankPiece = position.pieceAt(static_cast<Square>(56 + file));
        ASSERT_TRUE(blackBackRankPiece.has_value());
        EXPECT_EQ(blackBackRankPiece->type, backRank[file]);
        EXPECT_EQ(blackBackRankPiece->color, Color::Black);
    }

    for (int square = 16; square < 48; ++square) {
        EXPECT_FALSE(position.pieceAt(static_cast<Square>(square)).has_value());
    }
}

TEST(PositionFENTest, ParsesEmptyBoard) {
    Position position = Position::fromFEN("8/8/8/8/8/8/8/8");

    for (int square = 0; square < 64; ++square) {
        EXPECT_FALSE(position.pieceAt(static_cast<Square>(square)).has_value());
    }
}

TEST(PositionFENTest, ParsesSimplePosition) {
    Position position = Position::fromFEN("8/8/8/8/8/8/P7/8");

    std::optional<Piece> pawn = position.pieceAt(Square::A2);
    ASSERT_TRUE(pawn.has_value());
    EXPECT_EQ(pawn->type, PieceType::Pawn);
    EXPECT_EQ(pawn->color, Color::White);
    EXPECT_FALSE(position.pieceAt(Square::A1).has_value());
}

TEST(PositionFENTest, RejectsInvalidPieceCharacter) {
    EXPECT_THROW(Position::fromFEN("8/8/8/8/8/8/8/7X"), std::invalid_argument);
}

TEST(PositionFENTest, RejectsMalformedRankWidth) {
    EXPECT_THROW(Position::fromFEN("8/8/8/8/8/8/8/9"), std::invalid_argument);
    EXPECT_THROW(Position::fromFEN("8/8/8/8/8/8/8/7"), std::invalid_argument);
}

} // namespace
} // namespace chesslab
