#include "Game.h"

Game::~Game() {
	for (std::map<PlayerType, PlayerInputController*>::iterator it = _inputControllers.begin(); it != _inputControllers.end(); ++it) {
		delete it->second;
	}

	delete _boardBuilder;
	delete _boardController;
	delete _moveGenerator;
	delete _board;

	delete _graphics;
}

void Game::setup() {

	// Create the board
	_boardBuilder = new BoardBuilder();
	_boardController = new BoardController(SPRITE_BORDER, SPRITE_BORDER_TAKE, SPRITE_BORDER_MOVE);
	_moveGenerator = new MoveGenerator();
	_inputControllers[PlayerType::WHITE] = new PlayerInputController(PlayerType::WHITE, _boardController, this);
	_inputControllers[PlayerType::BLACK] = new PlayerInputController(PlayerType::BLACK, _boardController, this);

	_board = _boardBuilder->setNumBoardFiles(8)->setNumBoardRanks(8)->build();

	// Setup the window
	_graphics = new GraphicsSystem("Supreme Chess", 500, 500);
	_graphics->showWindow();
	
	// Load the sprites
	_graphics->loadSprite(SPRITE_CHESSBOARD_WHITE, "res/chessboard_white.png");
	_graphics->loadSprite(SPRITE_CHESSBOARD_BLACK, "res/chessboard_black.png");
	_graphics->loadSprite(SPRITE_BORDER, "res/border.png");
	_graphics->loadSprite(SPRITE_BORDER_MOVE, "res/border_move.png");
	_graphics->loadSprite(SPRITE_BORDER_TAKE, "res/border_take.png");

	GraphicsSystem::SpriteProperties pieceProps = createChessPieceProperties();
	_graphics->loadSpritesheet(pieceProps, "res/chess_pieces_small.png");

	// Load the text
	GraphicsSystem::SpriteProperties textProps;
	textProps.push_back(GraphicsSystem::SpriteProperty(SPRITE_WHITE_PLAYER_TURN, 0, 0, 200, 50));
	textProps.push_back(GraphicsSystem::SpriteProperty(SPRITE_BLACK_PLAYER_TURN, 200, 0, 200, 50));
	textProps.push_back(GraphicsSystem::SpriteProperty(SPRITE_WHITE_PLAYER_WON, 0, 50, 200, 50));
	textProps.push_back(GraphicsSystem::SpriteProperty(SPRITE_BLACK_PLAYER_WON, 200, 50, 200, 50));
	_graphics->loadSpritesheet(textProps, "res/text.png");

	// Attach the controller and the generator to the board
	_boardController->attachToBoard(_board);
	_moveGenerator->attachToBoard(_board);

	// Add the pieces to the board
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_ROOK, CHESS_PIECE_ROOK, PlayerType::BLACK), Vec2D(0, 0));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_KNIGHT, CHESS_PIECE_KNIGHT, PlayerType::BLACK), Vec2D(1, 0));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_BISHOP, CHESS_PIECE_BISHOP, PlayerType::BLACK), Vec2D(2, 0));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_KING, CHESS_PIECE_KING, PlayerType::BLACK), Vec2D(3, 0));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_QUEEN, CHESS_PIECE_QUEEN, PlayerType::BLACK), Vec2D(4, 0));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_BISHOP, CHESS_PIECE_BISHOP, PlayerType::BLACK), Vec2D(5, 0));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_KNIGHT, CHESS_PIECE_KNIGHT, PlayerType::BLACK), Vec2D(6, 0));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_ROOK, CHESS_PIECE_ROOK, PlayerType::BLACK), Vec2D(7, 0));

	for (int i = 0; i < 8; i++) {
		_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_BLACK_PAWN, CHESS_PIECE_PAWN, PlayerType::BLACK), Vec2D(i, 1));
	}

	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_ROOK, CHESS_PIECE_ROOK, PlayerType::WHITE), Vec2D(0, 7));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_KNIGHT, CHESS_PIECE_KNIGHT, PlayerType::WHITE), Vec2D(1, 7));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_BISHOP, CHESS_PIECE_BISHOP, PlayerType::WHITE), Vec2D(2, 7));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_KING, CHESS_PIECE_KING, PlayerType::WHITE), Vec2D(3, 7));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_QUEEN, CHESS_PIECE_QUEEN, PlayerType::WHITE), Vec2D(4, 7));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_BISHOP, CHESS_PIECE_BISHOP, PlayerType::WHITE), Vec2D(5, 7));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_KNIGHT, CHESS_PIECE_KNIGHT, PlayerType::WHITE), Vec2D(6, 7));
	_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_ROOK, CHESS_PIECE_ROOK, PlayerType::WHITE), Vec2D(7, 7));

	for (int i = 0; i < 8; i++) {
		_boardController->addChessPieceToBoard(new ChessPiece(SPRITE_WHITE_PAWN, CHESS_PIECE_PAWN, PlayerType::WHITE), Vec2D(i, 6));
	}

	// Refresh the legal takes/moves
	refreshLegalMoves();

}

void Game::runMainLoop() {

	SDL_Event event;

	while (!_shouldQuit) {
		
		// Check input
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				_shouldQuit = true;
			}

			// Only allow clicks if the game has not finished
			if (event.type == SDL_MOUSEBUTTONDOWN && _winner == PlayerType::NONE) {
				// Translate click to board co-ordinates
				Vec2D boardPosition = Vec2D(event.button.x, event.button.y) - BOARD_OFFSET;
				if (boardPosition > 0) {
					boardPosition.x = std::floor(boardPosition.x / TILE_SIZE);
					boardPosition.y = std::floor(boardPosition.y / TILE_SIZE);
					if (_board->tileIsOnBoard(boardPosition)) {
						_inputControllers[_currentPlayer]->handleClick(boardPosition);
					}
				}
			}
		}

		// Clear up dead chess pieces
		_boardController->cleanUpDeadChessPieces();

		// Draw sprites
		GraphicsSystem::Color playerColor = _currentPlayer == PlayerType::WHITE ? GraphicsSystem::WHITE : GraphicsSystem::BLACK;
		_graphics->clearRenderer(playerColor);

		for (int i = 0; i < _board->getDimensions().x; i++) {
			for (int j = 0; j < _board->getDimensions().y; j++) {
				Vec2D position(BOARD_OFFSET + TILE_SIZE * i, BOARD_OFFSET + TILE_SIZE * j);
				BoardTile* tile = _board->getBoardTile(Vec2D(i, j));
				if (tile != nullptr) {
					_graphics->drawSprite(tile->getSpriteKey(), position.x, position.y);

					// Draw tile border if it has one
					if (tile->getBorderSpriteKey() != nullptr) {
						_graphics->drawSprite(tile->getBorderSpriteKey(), position.x, position.y);
					}

					// Draw chess piece if it has one
					if (tile->getChessPiece() != nullptr) {
						_graphics->drawSprite(tile->getChessPiece()->getSpriteKey(), position.x, position.y);
					}
				}
			}
		}

		// Draw text
		switch (_winner) {
		case PlayerType::NONE:
			switch (_currentPlayer) {
			case PlayerType::WHITE:
				_graphics->drawSprite(SPRITE_WHITE_PLAYER_TURN, 0, 0);
				break;
			case PlayerType::BLACK:
				_graphics->drawSprite(SPRITE_BLACK_PLAYER_TURN, 300, 450);
				break;
			}
			break;
		case PlayerType::WHITE:
			_graphics->drawSprite(SPRITE_WHITE_PLAYER_WON, 0, 0);
			break;
		case PlayerType::BLACK:
			_graphics->drawSprite(SPRITE_BLACK_PLAYER_WON, 300, 450);
			break;
		}

		_graphics->render();

	}

	_graphics->closeWindow();

}

GraphicsSystem::SpriteProperty Game::createSpriteProperty(const char* name, Vec2D position, Vec2D dimensions) {
	GraphicsSystem::SpriteProperty spriteProperty;
	spriteProperty.name = name;
	spriteProperty.x = position.x;
	spriteProperty.y = position.y;
	spriteProperty.width = dimensions.x;
	spriteProperty.height = dimensions.y;
	return spriteProperty;
}

GraphicsSystem::SpriteProperties Game::createChessPieceProperties() {
	GraphicsSystem::SpriteProperties properties;
	properties.push_back(createSpriteProperty(SPRITE_WHITE_QUEEN, Vec2D(0, 0), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_WHITE_KING, Vec2D(50, 0), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_WHITE_BISHOP, Vec2D(100, 0), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_WHITE_KNIGHT, Vec2D(150, 0), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_WHITE_ROOK, Vec2D(200, 0), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_WHITE_PAWN, Vec2D(250, 0), TILE_DIMENSIONS));

	properties.push_back(createSpriteProperty(SPRITE_BLACK_QUEEN, Vec2D(0, 50), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_BLACK_KING, Vec2D(50, 50), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_BLACK_BISHOP, Vec2D(100, 50), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_BLACK_KNIGHT, Vec2D(150, 50), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_BLACK_ROOK, Vec2D(200, 50), TILE_DIMENSIONS));
	properties.push_back(createSpriteProperty(SPRITE_BLACK_PAWN, Vec2D(250, 50), TILE_DIMENSIONS));

	return properties;
}

void Game::refreshLegalMoves() {
	for (int i = 0; i < _board->getDimensions().x; i++) {
		for (int j = 0; j < _board->getDimensions().y; j++) {
			Vec2D tilePos(i, j);
			_board->setLegalMoves(tilePos, _moveGenerator->generateLegalMoves(tilePos));
		}
	}
}

void Game::checkWin() {
	ChessPiece* kings[2];
	int kingsFound = 0;

	for (int i = 0; i < _board->getDimensions().x; i++) {
		for (int j = 0; j < _board->getDimensions().y; j++) {
			Vec2D tilePos(i, j);
			BoardTile* tile = _board->getBoardTile(tilePos);
			if (tile != nullptr) {
				ChessPiece* piece = tile->getChessPiece();
				if (piece != nullptr
					&& piece->getChessPieceType().getSpecialModifiers() == ChessPieceType::KING) {
					// Might not be cleaned up yet
					if (!piece->isDead()) {
						kings[kingsFound++] = piece;
					}
				}
			}
		}
	}

	// If there's only one king left, that player wins
	if (kingsFound == 1) {
		_winner = kings[0]->getOwner();
	}
}

void Game::endTurn() {
	// Check the win conditions
	checkWin();

	if (_winner == PlayerType::NONE) {

		switch (_currentPlayer) {
		case PlayerType::WHITE:
			_currentPlayer = PlayerType::BLACK;
			break;
		case PlayerType::BLACK:
			_currentPlayer = PlayerType::WHITE;
			break;
		}

		// Refresh the legal takes/moves
		refreshLegalMoves();

	}
}