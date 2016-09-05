#ifndef GRIDSELECTIONSTATE_H
#define GRIDSELECTIONSTATE_H

class Grid;

/*
	Simple (probably badly-designed) FSM to
	handle annoying conditional logic of grid selection
*/
class GridSelectionState {

private:
	enum State {
		NONE,
		SELECTED,
		PIECE_TAKEN,
		PIECE_MOVED,
		TURN_ENDED
	};

	State _currentState;

	Grid* _grid;

public:
	GridSelectionState(Grid* grid) : _grid(grid), _currentState(State::NONE) {}

	void checkState();
	void enterState(State state);

};

#endif
