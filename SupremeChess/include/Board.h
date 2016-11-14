#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>

#include "BoardTile.h"
#include "Vec2D.h"

class Board {

public:
	typedef std::vector<Vec2D> MoveList;
	typedef unsigned int TileId;
	typedef std::map<TileId, MoveList> MoveMap;

private:

	BoardTile ***_boardTiles;

	MoveMap _legalTakes;
	MoveMap _legalMoves;
	Vec2D _dimensions;

	inline TileId convertPositionToTileId(Vec2D tilePos) const { return tilePos.x + (tilePos.y * _dimensions.y); }

public:
	Board(Vec2D dimensions);
	virtual ~Board();

	Vec2D getDimensions() const { return _dimensions; }
	MoveList getLegalTakes(Vec2D position) const;
	MoveList getLegalMoves(Vec2D position) const;
	BoardTile* getBoardTile(Vec2D position) const { return _boardTiles[position.x][position.y]; }

	void setLegalTakes(Vec2D position, MoveList takes);
	void setLegalMoves(Vec2D position, MoveList moves);
	void setBoardTile(Vec2D position, BoardTile* tile) { _boardTiles[position.x][position.y] = tile; }

	bool tileIsOnBoard(Vec2D tilePosition);

};

#endif
