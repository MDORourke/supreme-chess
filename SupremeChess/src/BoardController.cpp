#include "BoardController.h"

void BoardController::addChessPieceToBoard(ChessPiece* piece, Vec2D position) {

	// Get the board tile
	BoardTile *tile = _board->getBoardTile(position);
	
	// Set the piece on the tile
	tile->setChessPiece(piece);

}

// Returns true if the move was successful
bool BoardController::tryMoveChessPiece(Vec2D from, Vec2D to) {

	MoveList moves = _board->getLegalMoves(from);

	BoardTile *fromTile = _board->getBoardTile(from);

	for (auto it = moves.begin(); it != moves.end(); ++it) {
		if (it->destination == to) {
			BoardTile *toTile = _board->getBoardTile(to);
			if (it->moveType == Move::TAKE) {
				toTile->getChessPiece()->tickIsDeadFlag();
			}
			toTile->setChessPiece(fromTile->getChessPiece());
			fromTile->setChessPiece(nullptr);
			toTile->getChessPiece()->tickHasMovedFlag();

			return true;
		}
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
	highlightLegalMoves(boardPosition);
}

void BoardController::clearSelectedTile() {
	_selectedTile->setBorderSpriteKey(nullptr);
	_selectedTile = nullptr;

	clearHighlightedLegalMoves();
}

void BoardController::highlightLegalMoves(Vec2D boardPosition) {
	MoveList moves = _board->getLegalMoves(boardPosition);
	for (auto it = moves.begin(); it != moves.end(); it++) {
		BoardTile* tile = _board->getBoardTile(it->destination);
		switch (it->moveType) {
		case Move::MOVE:
			tile->setBorderSpriteKey(_legalMoveBorderSpriteKey);
			break;
		case Move::TAKE:
			tile->setBorderSpriteKey(_legalTakeBorderSpriteKey);
			break;
		}
		_highlightedLegalMoves.push_back(tile);
	}
}

void BoardController::clearHighlightedLegalMoves() {
	for (auto it = _highlightedLegalMoves.begin(); it != _highlightedLegalMoves.end(); it++) {
		(*it)->setBorderSpriteKey(nullptr);
	}
	_highlightedLegalMoves.clear();
}