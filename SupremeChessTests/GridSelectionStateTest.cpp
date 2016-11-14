#include "stdafx.h"
#include <gtest\gtest.h>
#include <gmock\gmock.h>

#include "MockGrid.h"
#include "GridSelectionState.h"

class GridSelectionStateTest : public ::testing::Test {

protected:
	GridSelectionState *_state;
	MockGrid _grid;

	GridSelectionStateTest() {
		_state = new GridSelectionState(&_grid);
	}

	~GridSelectionStateTest() {
		delete _state;
	}

};

TEST_F(GridSelectionStateTest, enterState_EnterStateNone_SetSelectedAndTargetSquareToNull) {

	EXPECT_CALL(_grid, setSelectedSquare(nullptr)).Times(1);
	EXPECT_CALL(_grid, setTargetSquare(nullptr)).Times(1);

	_state->enterState(GridSelectionState::State::NONE);
}

//TODO: Return to this, test is failing due to lack of knowledge of googletest
//TEST_F(GridSelectionStateTest, enterState_EnterStateSelected_SetSelectedSquareToTargetAndTargetToNull) {
//	// Entity object to return
//	Entity* targetSquare = new Entity();
//
//	_grid._targetSquare = targetSquare;
//	_grid.delegateGetters();
//
//	EXPECT_CALL(_grid, setSelectedSquare(targetSquare)).Times(1);
//	EXPECT_CALL(_grid, setTargetSquare(nullptr)).Times(1);
//
//	_state->enterState(GridSelectionState::State::SELECTED);
//}