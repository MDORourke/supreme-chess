#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "ChessPieceType.h"
#include "PlayerType.h"

class ChessPiece {

private:
	const char *_spriteKey;
	ChessPieceType _chessPieceType;
	PlayerType _owner;
	bool _hasMoved;
	bool _isDead;

public:
	ChessPiece(const char* spriteKey, ChessPieceType type, PlayerType owner)
		: _spriteKey(spriteKey),
		_chessPieceType(type),
		_owner(owner),
		_hasMoved(false),
		_isDead(false) {}

	const char* getSpriteKey() const { return _spriteKey; }
	ChessPieceType getChessPieceType() const { return _chessPieceType; }
	PlayerType getOwner() const { return _owner; }
	bool hasMoved() const { return _hasMoved; }
	bool isDead() const { return _isDead; }

	void setSpriteKey(const char* spriteKey) { _spriteKey = spriteKey; }
	void setChessPieceType(ChessPieceType chessPieceType) { _chessPieceType = chessPieceType; }
	void setOwner(PlayerType owner) { _owner = owner; }
	
	void tickHasMovedFlag() { _hasMoved = true; }
	void tickIsDeadFlag() { _isDead = true; }

	inline bool canTake(ChessPiece* piece) { return _owner != piece->getOwner(); }

};

#endif
