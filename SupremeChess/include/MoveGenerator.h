#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "Board.h"

class MoveGenerator {

private:
	Board *_board;

public:
	void attachToBoard(Board* board) { _board = board; }

	Board::MoveList generateLegalTakes(Vec2D boardPosition);
	Board::MoveList generateLegalMoves(Vec2D boardPosition, Board::MoveList legalTakes);

};

#endif
