#include "BoardController.h"

void BoardController::addChessPieceToBoard(ChessPiece* piece, Vec2D position) {

	// Get the board tile
	BoardTile *tile = _board->getBoardTile(position);
	
	// Set the piece on the tile
	tile->setChessPiece(piece);

}

// Returns true if the move was successful
bool BoardController::moveChessPiece(Vec2D from, Vec2D to) {

	// Make sure both vectors lie within the dimensions of the board
	if (_board->tileIsOnBoard(from) && _board->tileIsOnBoard(to)) {
		// Make sure there is a chess piece on the from tile
		BoardTile *fromTile = _board->getBoardTile(from);

		if (fromTile->getChessPiece() == nullptr) {
			return false;
		}

		// Make sure there is not a chess piece on the to tile
		BoardTile *toTile = _board->getBoardTile(to);
		
		if (toTile->getChessPiece() != nullptr) {
			return false;
		}

		// Move the piece over
		toTile->setChessPiece(fromTile->getChessPiece());
		fromTile->setChessPiece(nullptr);

		return true;
	}

	return false;

}

void BoardController::cleanUpDeadChessPieces() {

	for (int i = 0; i < _board->getDimensions().x; i++) {
		for (int j = 0; j < _board->getDimensions().y; j++) {
			ChessPiece* piece = _board->getBoardTile(Vec2D(i, j))->getChessPiece();

			if (piece != nullptr && piece->isDead()) {
				_board->getBoardTile(Vec2D(i, j))->setChessPiece(nullptr);
				delete piece;
			}
		}
	}

}

void BoardController::selectBoardTile(Vec2D boardPosition) {
	// Deselect currently selected board tile
	if (_selectedTile != nullptr) {
		clearSelectedTile();
	}

	if (_board->tileIsOnBoard(boardPosition)) {
		_selectedTilePosition = boardPosition;
		_selectedTile = _board->getBoardTile(boardPosition);
		_selectedTile->setBorderSpriteKey(_selectedTileBorderSpriteKey);
	}

	// Highlight legal takes/moves
	highlightLegalTakes(boardPosition);
	highlightLegalMoves(boardPosition);
}

void BoardController::clearSelectedTile() {
	_selectedTile->setBorderSpriteKey(nullptr);
	_selectedTile = nullptr;

	clearHighlightedLegalTakes();
	clearHighlightedLegalMoves();
}

void BoardController::highlightLegalTakes(Vec2D boardPosition) {
	Board::MoveList takes = _board->getLegalTakes(boardPosition);
	for (auto it = takes.begin(); it != takes.end(); it++) {
		BoardTile* tile = _board->getBoardTile(*it);
		tile->setBorderSpriteKey(_legalTakeBorderSpriteKey);
		_highlightedLegalTakes.push_back(tile);
	}

}

void BoardController::clearHighlightedLegalTakes() {
	for (auto it = _highlightedLegalTakes.begin(); it != _highlightedLegalTakes.end(); it++) {
		(*it)->setBorderSpriteKey(nullptr);
	}
	_highlightedLegalTakes.clear();
}

void BoardController::highlightLegalMoves(Vec2D boardPosition) {
	Board::MoveList moves = _board->getLegalMoves(boardPosition);
	for (auto it = moves.begin(); it != moves.end(); it++) {
		BoardTile* tile = _board->getBoardTile(*it);
		tile->setBorderSpriteKey(_legalMoveBorderSpriteKey);
		_highlightedLegalTakes.push_back(tile);
	}
}

void BoardController::clearHighlightedLegalMoves() {
	for (auto it = _highlightedLegalMoves.begin(); it != _highlightedLegalMoves.end(); it++) {
		(*it)->setBorderSpriteKey(nullptr);
	}
	_highlightedLegalMoves.clear();
}