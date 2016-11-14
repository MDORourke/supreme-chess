#ifndef GAME_H
#define GAME_H

#include "GraphicsSystem.h"

#include "BoardBuilder.h"
#include "BoardController.h"
#include "PlayerInputController.h"
#include "MoveGenerator.h"
#include "Board.h"
#include "PlayerType.h"

class Game {

private:
	BoardBuilder *_boardBuilder;
	BoardController *_boardController;
	MoveGenerator *_moveGenerator;
	Board *_board;
	std::map<PlayerType, PlayerInputController*> _inputControllers;

	PlayerType _currentPlayer = PlayerType::WHITE;

	bool _shouldQuit = false;

	GraphicsSystem *_graphics;

	const char* SPRITE_CHESSBOARD_WHITE = "chessboard_white";
	const char* SPRITE_CHESSBOARD_BLACK = "chessboard_black";

	const char* SPRITE_WHITE_QUEEN = "white_queen";
	const char* SPRITE_WHITE_KING = "white_king";
	const char* SPRITE_WHITE_BISHOP = "white_bishop";
	const char* SPRITE_WHITE_KNIGHT = "white_knight";
	const char* SPRITE_WHITE_ROOK = "white_rook";
	const char* SPRITE_WHITE_PAWN = "white_pawn";

	const char* SPRITE_BLACK_QUEEN = "black_queen";
	const char* SPRITE_BLACK_KING = "black_king";
	const char* SPRITE_BLACK_BISHOP = "black_bishop";
	const char* SPRITE_BLACK_KNIGHT = "black_knight";
	const char* SPRITE_BLACK_ROOK = "black_rook";
	const char* SPRITE_BLACK_PAWN = "black_pawn";

	const char* SPRITE_BORDER = "border";
	const char* SPRITE_BORDER_MOVE = "border_move";
	const char* SPRITE_BORDER_TAKE = "border_take";

	const ChessPieceType CHESS_PIECE_QUEEN = ChessPieceType(ChessPieceType::Directions::ALL, true);
	const ChessPieceType CHESS_PIECE_KING = ChessPieceType(ChessPieceType::Directions::ALL, false);
	const ChessPieceType CHESS_PIECE_BISHOP = ChessPieceType(ChessPieceType::Directions::NORTHEAST | ChessPieceType::Directions::SOUTHEAST | ChessPieceType::Directions::SOUTHWEST | ChessPieceType::Directions::NORTHWEST, true);
	const ChessPieceType CHESS_PIECE_KNIGHT = ChessPieceType(ChessPieceType::Directions::NO_DIRECTION, false, ChessPieceType::SpecialModifiers::KNIGHT);
	const ChessPieceType CHESS_PIECE_ROOK = ChessPieceType(ChessPieceType::Directions::EAST | ChessPieceType::Directions::WEST | ChessPieceType::Directions::NORTH | ChessPieceType::SOUTH, true);
	const ChessPieceType CHESS_PIECE_PAWN = ChessPieceType(ChessPieceType::Directions::NORTH, false, ChessPieceType::SpecialModifiers::PAWN);

	const int TILE_SIZE = 50;
	const Vec2D TILE_DIMENSIONS = { TILE_SIZE, TILE_SIZE };

public:

	Game() {}
	virtual ~Game();

	void setup();
	void runMainLoop();

	GraphicsSystem::SpriteProperty createSpriteProperty(const char* name, Vec2D position, Vec2D dimensions);
	GraphicsSystem::SpriteProperties createChessPieceProperties();

	void refreshLegalTakes();
	void refreshLegalMoves();

	void endTurn();

};

#endif