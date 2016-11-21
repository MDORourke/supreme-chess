#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>

#include "BoardTile.h"
#include "Vec2D.h"
#include "Move.h"

class Board {

public:
	typedef unsigned int TileId;
	typedef std::map<TileId, MoveList> MoveMap;

private:

	BoardTile ***_boardTiles;

	MoveMap _legalMoves;
	Vec2D _dimensions;

	inline TileId convertPositionToTileId(Vec2D tilePos) const { return tilePos.x + (tilePos.y * _dimensions.y); }

public:
	Board(Vec2D dimensions);
	virtual ~Board();

	Vec2D getDimensions() const { return _dimensions; }
	MoveList getLegalMoves(Vec2D position) const;
	BoardTile* getBoardTile(Vec2D position) const { return tileIsOnBoard(position) ? _boardTiles[position.x][position.y] : nullptr; }

	void setLegalMoves(Vec2D position, MoveList moves);
	void setBoardTile(Vec2D position, BoardTile* tile) { _boardTiles[position.x][position.y] = tile; }

	bool tileIsOnBoard(Vec2D tilePosition) const;

};

#endif
