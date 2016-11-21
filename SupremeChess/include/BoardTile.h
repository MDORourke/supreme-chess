#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "ChessPiece.h"

class BoardTile {

private:
	const char *_spriteKey;
	const char *_borderSpriteKey;
	ChessPiece *_chessPiece;

public:
	BoardTile(const char* spriteKey) : _spriteKey(spriteKey) {}
	virtual ~BoardTile();

	const char* getSpriteKey() const { return _spriteKey; }
	const char* getBorderSpriteKey() const { return _borderSpriteKey; }
	ChessPiece* getChessPiece() const { return _chessPiece; }

	void setSpriteKey(const char* spriteKey) { _spriteKey = spriteKey; }
	void setBorderSpriteKey(const char* borderSpriteKey) { _borderSpriteKey = borderSpriteKey; }
	void setChessPiece(ChessPiece* chessPiece) { _chessPiece = chessPiece; }

};

#endif
