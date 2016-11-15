#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "Vec2D.h"

struct Move {
	enum MoveType {
		MOVE,
		TAKE
	};

	Vec2D destination;
	MoveType moveType;

	Move(Vec2D in_destination, MoveType in_moveType) : destination(in_destination), moveType(in_moveType) {}
};

typedef std::vector<Move> MoveList;

#endif