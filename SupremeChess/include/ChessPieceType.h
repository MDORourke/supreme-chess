#ifndef CHESSPIECETYPE_H
#define CHESSPIECETYPE_H

#include "Direction.h"

class ChessPieceType {

public:

	enum SpecialModifiers {
		NO_MODIFIER,
		PAWN,
		KNIGHT
	};

private:
	Direction::DirectionMask _allowedDirections;
	bool _isSliding;
	SpecialModifiers _specialRuleModifiers;

public:
	ChessPieceType(Direction::DirectionMask allowedDirections, bool isSliding, SpecialModifiers modifiers = SpecialModifiers::NO_MODIFIER)
		: _allowedDirections(allowedDirections),
		_isSliding(isSliding),
		_specialRuleModifiers(modifiers) {}

	Direction::DirectionMask getAllowedDirections() const { return _allowedDirections; }
	bool isSliding() const { return _isSliding; }
	SpecialModifiers getSpecialModifiers() const { return _specialRuleModifiers; }

};

#endif
