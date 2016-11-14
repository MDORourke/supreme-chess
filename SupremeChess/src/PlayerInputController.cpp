#include "PlayerInputController.h"
#include "Game.h"

void PlayerInputController::handleClick(Vec2D boardPosition) {
	// Check selected tile
	BoardTile *tile = _boardController->getSelectedTile();

	if (tile != nullptr) {
		// If this is the same tile, toggle
		if (_boardController->getSelectedTilePosition() == boardPosition) {
			_boardController->clearSelectedTile();
		}
		else {
			// Get the chess piece of the currently selected tile
			ChessPiece *piece = tile->getChessPiece();

			// If there is a piece and it belongs to this player
			if (piece != nullptr && piece->getOwner() == _player) {
				if (_boardController->moveChessPiece(_boardController->getSelectedTilePosition(), boardPosition)) {
					_boardController->clearSelectedTile();
					_game->endTurn();
				}
			}
			else {
				// Select the tile
				_boardController->selectBoardTile(boardPosition);
			}
		}
	}
	else {
		_boardController->selectBoardTile(boardPosition);
	}
}