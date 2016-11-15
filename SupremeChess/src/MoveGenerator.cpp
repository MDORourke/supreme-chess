#include "MoveGenerator.h"

MoveList MoveGenerator::generateLegalMoves(Vec2D boardPosition) {
	MoveList moves;
	BoardTile *tile = _board->getBoardTile(boardPosition);
	if (tile != nullptr && tile->getChessPiece() != nullptr) {
		ChessPiece* piece = tile->getChessPiece();
		ChessPieceType type = piece->getChessPieceType();
		int playerDirection = piece->getOwner();
		
		// Check for special rules
		switch (type.getSpecialModifiers()) {
		case ChessPieceType::NO_MODIFIER:
			moves = getStandardMoves(boardPosition, piece);
			break;
		case ChessPieceType::PAWN:
			moves = getPawnMovement(boardPosition);
			break;
		case ChessPieceType::KNIGHT:
			moves = getKnightMovement(boardPosition);
			break;
		}
	}
	return moves;
}

MoveList MoveGenerator::getStandardMoves(Vec2D boardPosition, ChessPiece* origin) {
	Vec2D velocity;
	MoveList moves;
	ChessPieceType type = origin->getChessPieceType();
	int playerDirection = origin->getOwner();

	Direction::DirectionMask direction = type.getAllowedDirections();
	if ((direction & Direction::NORTH)) {
		velocity = Vec2D(0, playerDirection);
		checkStep(moves, boardPosition + velocity, velocity, origin);
	}
	if (direction & Direction::NORTHEAST) {
		velocity = Vec2D(playerDirection, playerDirection);
		checkStep(moves, boardPosition + velocity, velocity, origin);
	}
	if (direction & Direction::EAST) {
		velocity = Vec2D(playerDirection, 0);
		checkStep(moves, boardPosition + velocity, velocity, origin);
	}
	if (direction & Direction::SOUTHEAST) {
		velocity = Vec2D(playerDirection, -playerDirection);
		checkStep(moves, boardPosition + velocity, velocity, origin);
	}
	if (direction & Direction::SOUTH) {
		velocity = Vec2D(0, -playerDirection);
		checkStep(moves, boardPosition + velocity, velocity, origin);
	}
	if (direction & Direction::SOUTHWEST) {
		velocity = Vec2D(-playerDirection, -playerDirection);
		checkStep(moves, boardPosition + velocity, velocity, origin);
	}
	if (direction & Direction::WEST) {
		velocity = Vec2D(-playerDirection, 0);
		checkStep(moves, boardPosition + velocity, velocity, origin);
	}
	if (direction & Direction::NORTHWEST) {
		velocity = Vec2D(-playerDirection, playerDirection);
		checkStep(moves, boardPosition + velocity, velocity, origin);
	}

	return moves;
}

void MoveGenerator::checkStep(MoveList& moveList, Vec2D boardPosition, Vec2D velocity, ChessPiece* origin) {
	// Check that there are no chess pieces on the position to check
	BoardTile *tile = _board->getBoardTile(boardPosition);
	if (tile != nullptr) {
		if (tile->getChessPiece() == nullptr) {
			moveList.push_back(Move(boardPosition, Move::MOVE));
			// If this piece can slide, keep checking
			if (origin->getChessPieceType().isSliding()) {
				checkStep(moveList, boardPosition + velocity, velocity, origin);
			}
		} else {
			if (origin->canTake(tile->getChessPiece())) {
				moveList.push_back(Move(boardPosition, Move::TAKE));
			}
		}
	}
}

MoveList MoveGenerator::getPawnMovement(Vec2D originPosition) {
	MoveList moves;

	BoardTile *tile = _board->getBoardTile(originPosition);
	if (tile != nullptr && tile->getChessPiece() != nullptr) {
		// Check standard move
		int playerDirection = tile->getChessPiece()->getOwner();
		Vec2D standardMove = originPosition + Vec2D(0, playerDirection);
		BoardTile *standardTile = _board->getBoardTile(standardMove);

		if (standardTile != nullptr && standardTile->getChessPiece() == nullptr) {
			moves.push_back(Move(standardMove, Move::MOVE));

			// Check double move
			if (!tile->getChessPiece()->hasMoved()) {
				Vec2D doubleMove = standardMove + Vec2D(0, playerDirection);
				BoardTile *doubleTile = _board->getBoardTile(doubleMove);

				if (doubleTile != nullptr && doubleTile->getChessPiece() == nullptr) {
					moves.push_back(Move(doubleMove, Move::MOVE));
				}

			}
		}

		// Check for takes
		Vec2D take = originPosition + Vec2D(-1, playerDirection);
		BoardTile *takeTile = _board->getBoardTile(take);

		if (takeTile != nullptr && takeTile->getChessPiece() != nullptr && takeTile->getChessPiece()->canTake(tile->getChessPiece())) {
			moves.push_back(Move(take, Move::TAKE));
		}

		take = originPosition + Vec2D(1, playerDirection);
		takeTile = _board->getBoardTile(take);

		if (takeTile != nullptr && takeTile->getChessPiece() != nullptr && takeTile->getChessPiece()->canTake(tile->getChessPiece())) {
			moves.push_back(Move(take, Move::TAKE));
		}
	}

	return moves;
}

MoveList MoveGenerator::getKnightMovement(Vec2D originPosition) {
	MoveList moves;
	Vec2D deltas[] = { Vec2D(1, 2), Vec2D(2, 1), Vec2D(2, -1), Vec2D(1, -2), Vec2D(-1, -2), Vec2D(-2, -1), Vec2D(-2, 1), Vec2D(-1, 2) };

	BoardTile *origin = _board->getBoardTile(originPosition);

	if (origin != nullptr && origin->getChessPiece() != nullptr) {
		for (int i = 0; i < 8; i++) {
			// Check each of the 8 possible moves
			Vec2D movePos = originPosition + deltas[i];
			BoardTile *moveTile = _board->getBoardTile(movePos);

			if (moveTile != nullptr) {
				// Check for other pieces
				if (moveTile->getChessPiece() == nullptr) {
					moves.push_back(Move(movePos, Move::MOVE));
				}
				else if (moveTile->getChessPiece() != nullptr && origin->getChessPiece()->canTake(moveTile->getChessPiece())) {
					moves.push_back(Move(movePos, Move::TAKE));
				}
			}
		}

	}
	return moves;
}