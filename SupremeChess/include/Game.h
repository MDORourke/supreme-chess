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
	PlayerType _winner = PlayerType::NONE;

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

	const char* SPRITE_WHITE_PLAYER_TURN = "white_player_turn";
	const char* SPRITE_BLACK_PLAYER_TURN = "black_player_turn";
	const char* SPRITE_WHITE_PLAYER_WON = "white_player_won";
	const char* SPRITE_BLACK_PLAYER_WON = "black_player_won";

	const ChessPieceType CHESS_PIECE_QUEEN = ChessPieceType(Direction::ALL, true);
	const ChessPieceType CHESS_PIECE_KING = ChessPieceType(Direction::ALL, false, ChessPieceType::SpecialModifiers::KING);
	const ChessPieceType CHESS_PIECE_BISHOP = ChessPieceType(Direction::NORTHEAST | Direction::SOUTHEAST | Direction::SOUTHWEST | Direction::NORTHWEST, true);
	const ChessPieceType CHESS_PIECE_KNIGHT = ChessPieceType(Direction::NONE, false, ChessPieceType::SpecialModifiers::KNIGHT);
	const ChessPieceType CHESS_PIECE_ROOK = ChessPieceType(Direction::EAST | Direction::WEST | Direction::NORTH | Direction::SOUTH, true);
	const ChessPieceType CHESS_PIECE_PAWN = ChessPieceType(Direction::NORTH, false, ChessPieceType::SpecialModifiers::PAWN);

	const int TILE_SIZE = 50;
	const int BOARD_OFFSET = 50;
	const Vec2D TILE_DIMENSIONS = { TILE_SIZE, TILE_SIZE };

public:

	Game() {}
	virtual ~Game();

	void setup();
	void runMainLoop();

	GraphicsSystem::SpriteProperty createSpriteProperty(const char* name, Vec2D position, Vec2D dimensions);
	GraphicsSystem::SpriteProperties createChessPieceProperties();

	void refreshLegalMoves();
	void checkWin();

	void endTurn();

};

#endif