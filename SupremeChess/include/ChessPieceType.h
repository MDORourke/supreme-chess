#ifndef CHESSPIECETYPE_H
#define CHESSPIECETYPE_H

class ChessPieceType {

public:
	enum Directions {
		NO_DIRECTION = 0,
		NORTH = 1,
		NORTHEAST = 2,
		EAST = 4,
		SOUTHEAST = 8,
		SOUTH = 16,
		SOUTHWEST = 32,
		WEST = 64,
		NORTHWEST = 128,
		ALL = 255
	};

	enum SpecialModifiers {
		NO_MODIFIER,
		PAWN,
		KNIGHT
	};

private:
	int _allowedDirections;
	bool _isSliding;
	SpecialModifiers _specialRuleModifiers;

public:
	ChessPieceType(int allowedDirections, bool isSliding, SpecialModifiers modifiers = SpecialModifiers::NO_MODIFIER)
		: _allowedDirections(allowedDirections),
		_isSliding(isSliding),
		_specialRuleModifiers(modifiers) {}

	int getAllowedDirections() const { return _allowedDirections; }
	bool isSliding() const { return _isSliding; }
	SpecialModifiers getSpecialModifiers() const { return _specialRuleModifiers; }

};

#endif
