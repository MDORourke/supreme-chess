#include "stdafx.h"
#include <gtest\gtest.h>

#include "Grid.h"
#include "GridSelectionState.h"

class GridTest : public ::testing::Test {

protected:

	GridTest() {
		_grid = new Grid(4, 4);
	}

	~GridTest() {
		delete _grid;
	}

	void addPieceWithComponents(Entity* piece, Vec2D index, PieceComponent::PieceType pieceType, PieceComponent::PlayerType playerType) {
		GridComponent* gridComponent = new GridComponent(piece, index);
		PieceComponent* pieceComponent = new PieceComponent(piece, pieceType, playerType);
		piece->addComponent<GridComponent>(gridComponent);
		piece->addComponent<PieceComponent>(pieceComponent);

		_grid->addChessPiece(piece, index);
	}

	void addPieceWithComponents(Entity* piece, Vec2D index) {
		addPieceWithComponents(piece, index, PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::BLACK);
	}

	//Grid _grid(4, 4);
	Grid *_grid;

};

TEST_F(GridTest, constructor_Basic_GridInitialised) {
	// Expected Values
	int expectedRows = 4, expectedCols = 4;

	// Actual Values
	int actualRows = _grid->getNumRows();
	int actualCols = _grid->getNumCols();

	ASSERT_EQ(actualRows, expectedRows);
	ASSERT_EQ(actualCols, expectedCols);

	// Check the squares are initialised properly
	for (int i = 0; i < actualRows; i++) {
		for (int j = 0; j < actualCols; j++) {
			ASSERT_FALSE(_grid->getGridSquare(Vec2D(i, j)) == nullptr);
			ASSERT_TRUE(_grid->getChessPiece(Vec2D(i, j)) == nullptr);
		}
	}

}

TEST_F(GridTest, getGridSquareFromPosition_PositionSupplied_ReturnGridSquareIndex) {
	// Expected values
	Vec2D expectedSquare = Vec2D(2, 2);
	
	// Actual values
	Vec2D actualSquare = _grid->getGridSquareFromPosition(Vec2D(100, 100));

	ASSERT_EQ(expectedSquare, actualSquare);
}

TEST_F(GridTest, getPositionFromGridSquare_GridSquareSupplied_ReturnPosition) {
	// Expected values
	Vec2D expectedPosition = Vec2D(100, 100);

	Vec2D actualPosition = _grid->getPositionFromGridSquare(Vec2D(2, 2));
	
	ASSERT_EQ(expectedPosition, actualPosition);
}

TEST_F(GridTest, getPositionClampedToGridSquare_PositionSupplied_ReturnPositionToNearestSquare) {
	Vec2D expectedPosition = Vec2D(100, 100);

	Vec2D actualPosition = _grid->getPositionClampedToGridSquare(Vec2D(125, 125));

	ASSERT_EQ(expectedPosition, actualPosition);
}

TEST_F(GridTest, getGridSquare_InBounds_ReturnGridSquare) {
	Entity* actualGridSquare = _grid->getGridSquare(Vec2D(2, 2));
	
	ASSERT_FALSE(actualGridSquare == nullptr);
}

TEST_F(GridTest, getGridSquare_OutOfBounds_ReturnNull) {
	Entity* actualGridSquare = _grid->getGridSquare(Vec2D(10, 10));

	ASSERT_TRUE(actualGridSquare == nullptr);
}

TEST_F(GridTest, addChessPiece_HasAllComponentsIsInBounds_AddPiece) {
	Entity expectedPiece;
	addPieceWithComponents(&expectedPiece, Vec2D(2, 2));

	Entity* actualPiece = _grid->getChessPiece(Vec2D(2, 2));

	ASSERT_EQ(&expectedPiece, actualPiece);
}

TEST_F(GridTest, addChessPiece_HasGridComponentIsInBounds_ReturnNull) {
	Entity piece;
	GridComponent* gridComponent = new GridComponent(&piece, Vec2D(2, 2));
	piece.addComponent<GridComponent>(gridComponent);

	_grid->addChessPiece(&piece, Vec2D(2, 2));

	ASSERT_TRUE(_grid->getChessPiece(Vec2D(2, 2)) == nullptr);
}

TEST_F(GridTest, addChessPiece_HasPieceComponentIsInBounds_ReturnNull) {
	Entity piece;
	PieceComponent* pieceComponent = new PieceComponent(&piece, PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::BLACK);
	piece.addComponent<PieceComponent>(pieceComponent);

	_grid->addChessPiece(&piece, Vec2D(2, 2));

	ASSERT_TRUE(_grid->getChessPiece(Vec2D(2, 2)) == nullptr);
}

TEST_F(GridTest, addChessPiece_HasAllComponentsIsOutOfBounds_ReturnNull) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(10, 10));

	ASSERT_TRUE(_grid->getChessPiece(Vec2D(10, 10)) == nullptr);
}

TEST_F(GridTest, moveChessPiece_PieceExistsFromInBoundsToInBounds_MovePiece) {
	Entity expectedPiece;
	
	addPieceWithComponents(&expectedPiece, Vec2D(2, 2));

	_grid->moveChessPiece(Vec2D(2, 2), Vec2D(3, 3));

	Entity* actualPiece = _grid->getChessPiece(Vec2D(3, 3));

	ASSERT_EQ(&expectedPiece, actualPiece);
}

TEST_F(GridTest, moveChessPiece_PieceDoesNotExist_DoNothing) {
	_grid->moveChessPiece(Vec2D(2, 2), Vec2D(3, 3));

	ASSERT_TRUE(_grid->getChessPiece(Vec2D(2, 2)) == nullptr);
	ASSERT_TRUE(_grid->getChessPiece(Vec2D(3, 3)) == nullptr);
}

TEST_F(GridTest, moveChessPiece_PieceExistsFromOutOfBoundsToInBounds_DoNothing) {
	Entity piece;
	
	addPieceWithComponents(&piece, Vec2D(10, 10));

	_grid->moveChessPiece(Vec2D(10, 10), Vec2D(3, 3));

	Entity* actualPiece = _grid->getChessPiece(Vec2D(3, 3));

	ASSERT_TRUE(actualPiece == nullptr);
}

TEST_F(GridTest, moveChessPiece_PieceExistsFromInBoundsToOutOfBounds_DoNothing) {
	Entity piece;
	
	addPieceWithComponents(&piece, Vec2D(2, 2));

	_grid->moveChessPiece(Vec2D(2, 2), Vec2D(10, 10));

	ASSERT_TRUE(_grid->getChessPiece(Vec2D(10, 10)) == nullptr);
	ASSERT_EQ(_grid->getChessPiece(Vec2D(2, 2)), &piece);
}

TEST_F(GridTest, takeChessPiece_PieceExists_KillPiece) {
	Entity piece;
	
	addPieceWithComponents(&piece, Vec2D(2, 2));

	_grid->takeChessPiece(Vec2D(2, 2));

	ASSERT_TRUE(_grid->getChessPiece(Vec2D(2, 2)) == nullptr);
	ASSERT_EQ(piece.isAlive(), false);
}

TEST_F(GridTest, takeChessPiece_PieceDoesNotExist_DoNothing) {
	Entity piece;

	_grid->takeChessPiece(Vec2D(2, 2));

	ASSERT_TRUE(_grid->getChessPiece(Vec2D(2, 2)) == nullptr);
}

TEST_F(GridTest, isLegalMove_PieceIsBishopMoveIsDiagonal_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsBishopMoveIsHorizontal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalMove_PieceIsBishopMoveIsVertical_ReturnFalse) {
	Entity piece;
	
	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsKingMoveIsDiagonal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KING, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsKingMoveIsHorizontal_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KING, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalMove_PieceIsKingMoveIsDoubleHorizontal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KING, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(4, 2)));
}

TEST_F(GridTest, isLegalMove_PieceIsKingMoveIsVertical_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KING, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsKingMoveIsDoubleVertical_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KING, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 4)));
}

TEST_F(GridTest, isLegalMove_PieceIsKnightMoveIsDiagonal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KNIGHT, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsKnightMoveIsHorizontal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KNIGHT, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalMove_PieceIsKnightMoveIsVertical_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KNIGHT, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsKnightMoveIsKnightMove_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::KNIGHT, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 4)));
	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(4, 3)));
	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(4, 1)));
	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 0)));
	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(1, 0)));
	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(0, 1)));
	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(0, 3)));
	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(1, 4)));
}

TEST_F(GridTest, isLegalMove_PieceIsBlackPawnMoveIsUpBoard_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsBlackPawnMoveIsDownBoard_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 1)));
}

TEST_F(GridTest, isLegalMove_PieceIsBlackPawnMoveIsDoubleUpBoardFirstTurn_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 4)));
}

TEST_F(GridTest, isLegalMove_PieceIsBlackPawnMoveIsDoubleUpBoardNotFirstTurn_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	piece.getComponent<PieceComponent>()->setHasMoved(true);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 4)));
}

TEST_F(GridTest, isLegalMove_PieceIsBlackPawnMoveIsDiagonal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsBlackPawnMoveIsHorizontal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalMove_PieceIsWhitePawnMoveIsUpBoard_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsWhitePawnMoveIsDownBoard_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 1)));
}

TEST_F(GridTest, isLegalMove_PieceIsWhitePawnMoveIsDoubleDownBoardFirstTurn_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 0)));
}

TEST_F(GridTest, isLegalMove_PieceIsWhitePawnMoveIsDoubleDownBoardNotFirstTurn_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE);

	piece.getComponent<PieceComponent>()->setHasMoved(true);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 0)));
}

TEST_F(GridTest, isLegalMove_PieceIsWhitePawnMoveIsDiagonal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsWhitePawnMoveIsHorizontal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalMove_PieceIsQueenMoveIsDiagonal_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::QUEEN, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsQueenMoveIsHorizontal_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::QUEEN, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsQueenMoveIsVertical_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::QUEEN, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalMove_PieceIsRookMoveIsDiagonal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::ROOK, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalMove_PieceIsRookMoveIsHorizontal_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::ROOK, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalMove_PieceIsRookMoveIsVertical_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::ROOK, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, isLegalMove_NoPiece_ReturnFalse) {
	Entity piece;

	ASSERT_FALSE(_grid->isLegalMove(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalTake_PieceIsBlackPawnTakeIsDiagonalUpBoard_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_TRUE(_grid->isLegalTake(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalTake_PieceIsBlackPawnTakeIsDiagonalDownBoard_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalTake(Vec2D(2, 2), Vec2D(1, 1)));
}

TEST_F(GridTest, isLegalTake_PieceIsBlackPawnTakeIsHorizontal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalTake(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalTake_PieceIsBlackPawnTakeIsVertical_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK);

	ASSERT_FALSE(_grid->isLegalTake(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, isLegalTake_PieceIsWhitePawnTakeIsDiagonalUpBoard_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE);

	ASSERT_FALSE(_grid->isLegalTake(Vec2D(2, 2), Vec2D(3, 3)));
}

TEST_F(GridTest, isLegalTake_PieceIsWhitePawnTakeIsDiagonalDownBoard_ReturnTrue) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE);

	ASSERT_TRUE(_grid->isLegalTake(Vec2D(2, 2), Vec2D(1, 1)));
}

TEST_F(GridTest, isLegalTake_PieceIsWhitePawnTakeIsHorizontal_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE);

	ASSERT_FALSE(_grid->isLegalTake(Vec2D(2, 2), Vec2D(3, 2)));
}

TEST_F(GridTest, isLegalTake_PieceIsWhitePawnTakeIsVertical_ReturnFalse) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE);

	ASSERT_FALSE(_grid->isLegalTake(Vec2D(2, 2), Vec2D(2, 3)));
}

TEST_F(GridTest, resolvePositions_PiecesExist_UpdatePositions) {
	Entity piece;

	addPieceWithComponents(&piece, Vec2D(2, 2));

	piece.setPosition(Vec2D(100, 100));

	_grid->resolvePositions();

	ASSERT_EQ(piece.getPosition(), _grid->getPositionFromGridSquare(Vec2D(2, 2)));
}

TEST_F(GridTest, endTurn_WhitePlayerTurn_SetCurrentPlayerBlack) {
	ASSERT_EQ(_grid->getCurrentPlayer(), PieceComponent::PlayerType::WHITE);

	_grid->endTurn();

	ASSERT_EQ(_grid->getCurrentPlayer(), PieceComponent::PlayerType::BLACK);
}

TEST_F(GridTest, endTurn_BlackPlayerTurn_SetCurrentPlayerWhite) {
	_grid->endTurn();

	ASSERT_EQ(_grid->getCurrentPlayer(), PieceComponent::PlayerType::BLACK);

	_grid->endTurn();

	ASSERT_EQ(_grid->getCurrentPlayer(), PieceComponent::PlayerType::WHITE);
}