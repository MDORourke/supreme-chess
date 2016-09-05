#include "GridSelectionState.h"
#include "Grid.h"

void GridSelectionState::checkState() {

	switch (_currentState) {
	case State::NONE:
		{
			Entity* target = _grid->getTargetSquare();
			if (target != nullptr) {
				enterState(State::SELECTED);
			}
		}
		break;
	case State::SELECTED:
		{
			Entity* target = _grid->getTargetSquare();
			if (target == nullptr) {
				return;
			}
			// Selecting currently selected square?
			Entity* selectedSquare = _grid->getSelectedSquare();
			if (target == selectedSquare) {
				enterState(State::NONE);
				return;
			}
			// Is there a piece on the selected square?
			Entity* selectedPiece = _grid->getChessPiece(selectedSquare->getComponent<GridComponent>()->getGridIndex());
			if (selectedPiece == nullptr) {
				enterState(State::SELECTED);
				return;
			}
			// Does the selected piece belong to the current player?
			PieceComponent::PlayerType player = selectedPiece->getComponent<PieceComponent>()->getPlayerType();
			if (player != _grid->getCurrentPlayer()) {
				enterState(State::SELECTED);
				return;
			}
			// Is there a piece at the target location?
			Entity* targetPiece = _grid->getChessPiece(target->getComponent<GridComponent>()->getGridIndex());
			if (targetPiece == nullptr) {
				// Is it a legal move?
				if (_grid->isLegalMove(selectedSquare->getComponent<GridComponent>()->getGridIndex(), target->getComponent<GridComponent>()->getGridIndex())) {
					enterState(State::PIECE_MOVED);
				}
				return;
			}
			// Does the piece belong to the other player?
			if (targetPiece->getComponent<PieceComponent>()->getPlayerType() != _grid->getCurrentPlayer()) {
				// Is it a legal take?
				if (_grid->isLegalTake(selectedSquare->getComponent<GridComponent>()->getGridIndex(), target->getComponent<GridComponent>()->getGridIndex())) {
					enterState(State::PIECE_TAKEN);
				}
				return;
			}
			enterState(State::SELECTED);
		}
		break;
	case State::PIECE_TAKEN:
		enterState(State::TURN_ENDED);
		break;
	case State::PIECE_MOVED:
		enterState(State::TURN_ENDED);
		break;
	case State::TURN_ENDED:
		enterState(State::NONE);
		break;
	}

}

void GridSelectionState::enterState(State state) {
	switch (state) {
	case State::NONE:
		_grid->setSelectedSquare(nullptr);
		_grid->setTargetSquare(nullptr);
		break;
	case State::SELECTED:
		_grid->setSelectedSquare(_grid->getTargetSquare());
		_grid->setTargetSquare(nullptr);
		break;
	case State::PIECE_TAKEN:
		_grid->takeChessPiece(_grid->getTargetSquare()->getComponent<GridComponent>()->getGridIndex());
		_grid->moveChessPiece(_grid->getSelectedSquare()->getComponent<GridComponent>()->getGridIndex(), _grid->getTargetSquare()->getComponent<GridComponent>()->getGridIndex());
		break;
	case State::PIECE_MOVED:
		_grid->moveChessPiece(_grid->getSelectedSquare()->getComponent<GridComponent>()->getGridIndex(), _grid->getTargetSquare()->getComponent<GridComponent>()->getGridIndex());
		break;
	case State::TURN_ENDED:
		_grid->endTurn();
		break;
	}

	_currentState = state;
	checkState();
}