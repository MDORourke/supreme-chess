#ifndef GRID_H
#define GRID_H

#include "Entity.h"
#include "GraphicsComponent.h"
#include "GridComponent.h"
#include "PieceComponent.h"
#include "GridSelectionState.h"
#include "Vec2D.h"

class Grid {

private:

	const int SQUARE_SIZE = 50;

	int _numRows, _numCols;
	PieceComponent::PlayerType _currentPlayer = PieceComponent::PlayerType::WHITE;

	Entity*** _gridSquares;
	Entity*** _pieces;
	Entity* _selectedGridSquare;
	Entity* _targetGridSquare;

	GridSelectionState* _selectionState;

	void initialiseGrid();
	Entity* createGridSquare(Vec2D gridSquareIndex);

public:

	Grid(int numRows, int numCols);
	~Grid();

	Vec2D getGridSquareFromPosition(Vec2D position) const;
	Vec2D getPositionFromGridSquare(Vec2D gridSquare) const;
	Vec2D getPositionClampedToGridSquare(Vec2D position) const;

	int getNumRows() const { return _numRows; }
	int getNumCols() const { return _numCols; }
	PieceComponent::PlayerType getCurrentPlayer() const { return _currentPlayer; }
	Entity* getGridSquare(Vec2D index) const;
	Entity* getChessPiece(Vec2D index) const;
	Entity* getSelectedSquare() const { return _selectedGridSquare; }
	Entity* getTargetSquare() const { return _targetGridSquare; }

	void setSelectedSquare(Entity* entity) { _selectedGridSquare = entity; }
	void setTargetSquare(Entity* entity) { _targetGridSquare = entity; }

	void addChessPiece(Entity* piece, Vec2D index);
	void moveChessPiece(Vec2D from, Vec2D to);
	void takeChessPiece(Vec2D pieceToTake);

	inline bool indexIsInBounds(Vec2D index) const { return index.x <= _numRows && index.y <= _numCols; }
	bool isLegalMove(Vec2D from, Vec2D to);
	bool isLegalMove(Vec2D from, Vec2D to, PieceComponent component);
	bool isLegalTake(Vec2D from, Vec2D to);
	bool isLegalTake(Vec2D from, Vec2D to, PieceComponent component);

	void selectGrid(Vec2D position);
	void resolvePositions();
	void endTurn();

};

#endif // GRID_H
