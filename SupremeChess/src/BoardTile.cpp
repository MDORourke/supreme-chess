#include "BoardTile.h"

BoardTile::~BoardTile() {
	delete _chessPiece;
}