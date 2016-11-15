#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "Board.h"
#include "Move.h"

class MoveGenerator {

private:
	Board *_board;

	MoveList getStandardMoves(Vec2D boardPosition, ChessPiece* origin);
	void checkStep(MoveList& moveList, Vec2D boardPosition, Vec2D velocity, ChessPiece* origin);
	
	MoveList getPawnMovement(Vec2D originPosition);
	MoveList getKnightMovement(Vec2D originPosition);

public:
	void attachToBoard(Board* board) { _board = board; }

	MoveList generateLegalMoves(Vec2D boardPosition);

};

#endif
