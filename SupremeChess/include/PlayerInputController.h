#ifndef PLAYERINPUTCONTROLLER_H
#define PLAYERINPUTCONTROLLER_H

#include "PlayerType.h"
#include "BoardController.h"

class Game;

class PlayerInputController {

private:
	PlayerType _player;
	BoardController *_boardController;
	Game *_game;

public:
	PlayerInputController(PlayerType player, BoardController *boardController, Game* game) : _player(player), _boardController(boardController), _game(game) {}

	void handleClick(Vec2D boardPosition);

};

#endif