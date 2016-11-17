#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "ChessPiece.h"
#include "Board.h"

class BoardController {

private:
	Board *_board;
	BoardTile *_selectedTile = nullptr;
	Vec2D _selectedTilePosition;

	std::vector<BoardTile*> _highlightedLegalMoves;

	const char* _selectedTileBorderSpriteKey;
	const char* _legalTakeBorderSpriteKey;
	const char* _legalMoveBorderSpriteKey;

public:
	BoardController(const char* selectedTileBorderSpriteKey, const char* legalTakeBorderSpriteKey, const char* legalMoveBorderSpriteKey) : _selectedTileBorderSpriteKey(selectedTileBorderSpriteKey), _legalTakeBorderSpriteKey(legalTakeBorderSpriteKey), _legalMoveBorderSpriteKey(legalMoveBorderSpriteKey) {}

	BoardTile* getSelectedTile() const { return _selectedTile; }
	Vec2D getSelectedTilePosition() const { return _selectedTilePosition; }

	void attachToBoard(Board *board) { _board = board; }

	void addChessPieceToBoard(ChessPiece* piece, Vec2D position);
	bool tryMoveChessPiece(Vec2D from, Vec2D to);

	void cleanUpDeadChessPieces();

	void selectBoardTile(Vec2D boardPosition);
	void clearSelectedTile();

	void highlightLegalMoves(Vec2D boardPosition);
	void clearHighlightedLegalMoves();

};

#endif