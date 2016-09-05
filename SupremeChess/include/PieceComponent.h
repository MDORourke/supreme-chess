#ifndef PIECECOMPONENT_H
#define PIECECOMPONENT_H

#include "Component.h"

class PieceComponent : public Component {

public:
	enum PieceType {
		QUEEN,
		KING,
		BISHOP,
		KNIGHT,
		ROOK,
		PAWN
	};

	enum PlayerType {
		BLACK,
		WHITE
	};

private:
	PieceType _pieceType;
	PlayerType _playerType;
	bool _hasMoved = false;

public:

	PieceComponent(Entity* parent, PieceType pieceType, PlayerType playerType) : Component(parent), _pieceType(pieceType), _playerType(playerType) {}

	inline PieceType getPieceType() const { return _pieceType; }
	inline PlayerType getPlayerType() const { return _playerType; }
	inline bool hasMoved() const { return _hasMoved; }

	inline void setPieceType(PieceType pieceType) { _pieceType = pieceType; }
	inline void setPlayerType(PlayerType playerType) { _playerType = playerType; }
	inline void setHasMoved(bool hasMoved) { _hasMoved = hasMoved; }

};

#endif