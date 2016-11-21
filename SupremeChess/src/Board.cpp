#include "Board.h"

Board::Board(Vec2D dimensions) {
	_dimensions = dimensions;

	_boardTiles = new BoardTile**[_dimensions.x];

	for (int i = 0; i < _dimensions.x; i++) {
		_boardTiles[i] = new BoardTile*[_dimensions.y];

		for (int j = 0; j < _dimensions.y; j++) {
			_boardTiles[i][j] = nullptr;
		}
	}
}

Board::~Board() {
	for (int i = 0; i < _dimensions.x; i++) {
		for (int j = 0; j < _dimensions.y; j++) {
			delete _boardTiles[i][j];
		}
		delete[] _boardTiles[i];
	}
	delete[] _boardTiles;
}

MoveList Board::getLegalMoves(Vec2D position) const {

	// Convert position to tile ID
	TileId id = convertPositionToTileId(position);

	auto it = _legalMoves.find(id);

	if (it == _legalMoves.end()) {
		return MoveList();
	}

	MoveList list = it->second;
	return list;
}

void Board::setLegalMoves(Vec2D position, MoveList moves) {
	// Convert position to tile ID
	TileId id = convertPositionToTileId(position);

	_legalMoves[id] = moves;
}

bool Board::tileIsOnBoard(Vec2D tilePosition) const {
	return tilePosition >= Vec2D(0, 0) && tilePosition < _dimensions;
}