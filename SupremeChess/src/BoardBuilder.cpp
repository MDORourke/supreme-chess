#include "BoardBuilder.h"

BoardBuilder* BoardBuilder::setNumBoardRanks(int numBoardRanks) {
	_boardRanksAndFiles.x = numBoardRanks;
	return this;
}

BoardBuilder* BoardBuilder::setNumBoardFiles(int numBoardFiles) {
	_boardRanksAndFiles.y = numBoardFiles;
	return this;
}

Board* BoardBuilder::build() {
	Board* board = new Board(_boardRanksAndFiles);

	for (int i = 0; i < _boardRanksAndFiles.x; i++) {
		for (int j = 0; j < _boardRanksAndFiles.y; j++) {
			const char* spriteKey;
			if ((i + j) % 2 == 1) {
				spriteKey = SPRITE_WHITE_TILE;
			} else {
				spriteKey = SPRITE_BLACK_TILE;
			}
			BoardTile* tile = new BoardTile(spriteKey);
			board->setBoardTile(Vec2D(i, j), tile);
		}
	}

	return board;
}