#ifndef MOCKGRID_H
#define MOCKGRID_H

#include <gmock\gmock.h>

#include "Grid.h"

class MockGrid : public Grid {
public:
	MockGrid() : Grid(2, 2) {
		_targetSquare = new Entity();
		_selectedSquare = new Entity();
	}

	virtual ~MockGrid() {
		delete _targetSquare;
		delete _selectedSquare;
	}

	Entity *_targetSquare;
	Entity *_selectedSquare;

	/*virtual void setTargetSquare(Entity *targetSquare) {
		_targetSquare = targetSquare;
	}

	virtual void setSelectedSquare(Entity *selectedSquare) {
		_selectedSquare = selectedSquare;
	}*/

	MOCK_CONST_METHOD0(getSelectedSquare, Entity*());
	MOCK_CONST_METHOD0(getTargetSquare, Entity*());

	MOCK_METHOD1(setSelectedSquare, void(Entity* entity));
	MOCK_METHOD1(setTargetSquare, void(Entity* entity));

	MOCK_METHOD2(moveChessPiece, void(Vec2D from, Vec2D to));
	MOCK_METHOD2(takeChessPiece, void(Vec2D from, Vec2D to));

	MOCK_METHOD0(resolvePositions, void());

	void delegateGetters() {
		ON_CALL(*this, getSelectedSquare()).WillByDefault(::testing::Return(_selectedSquare));
		ON_CALL(*this, getTargetSquare()).WillByDefault(::testing::Return(_targetSquare));
	}

};

#endif