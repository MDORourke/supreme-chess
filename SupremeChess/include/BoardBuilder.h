#ifndef BOARDBUILDER_H
#define BOARDBUILDER_H

#include "Board.h"
#include "BoardTile.h"
#include "Vec2D.h"

class BoardBuilder {

private:
	Vec2D _boardRanksAndFiles;

	const char* SPRITE_WHITE_TILE = "chessboard_white";
	const char* SPRITE_BLACK_TILE = "chessboard_black";

public:
	BoardBuilder() {}

	BoardBuilder* setNumBoardRanks(int numBoardRanks);
	BoardBuilder* setNumBoardFiles(int numBoardFiles);

	Board* build();

};

#endif
