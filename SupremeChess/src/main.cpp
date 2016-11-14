#include <stdlib.h>

#include "GraphicsSystem.h"
#include "GraphicsComponent.h"
#include "Grid.h"
#include "GridComponent.h"
#include "PieceComponent.h"
#include "Entity.h"

#include "Game.h"

using namespace std;

const char* CHESSBOARD = "chessboard";
const char* CHESSBOARD_WHITE = "chessboard_white";
const char* CHESSBOARD_BLACK = "chessboard_black";

const char* WHITE_QUEEN = "white_queen";
const char* WHITE_KING = "white_king";
const char* WHITE_BISHOP = "white_bishop";
const char* WHITE_KNIGHT = "white_knight";
const char* WHITE_ROOK = "white_rook";
const char* WHITE_PAWN = "white_pawn";

const char* BLACK_QUEEN = "black_queen";
const char* BLACK_KING = "black_king";
const char* BLACK_BISHOP = "black_bishop";
const char* BLACK_KNIGHT = "black_knight";
const char* BLACK_ROOK = "black_rook";
const char* BLACK_PAWN = "black_pawn";

const char* BORDER = "border";

std::vector<Entity*> _entities;

GraphicsSystem::SpriteProperty createSprite(const char* name, int x, int y, int width, int height) {
    GraphicsSystem::SpriteProperty spriteProperty;
    spriteProperty.name = name;
    spriteProperty.x = x;
    spriteProperty.y = y;
    spriteProperty.width = width;
    spriteProperty.height = height;
    return spriteProperty;
}

GraphicsSystem::SpriteProperties loadSprites() {
    GraphicsSystem::SpriteProperties props;
    props.push_back(createSprite(WHITE_QUEEN, 0, 0, 50, 50));
    props.push_back(createSprite(WHITE_KING, 50, 0, 50, 50));
    props.push_back(createSprite(WHITE_BISHOP, 100, 0, 50, 50));
    props.push_back(createSprite(WHITE_KNIGHT, 150, 0, 50, 50));
    props.push_back(createSprite(WHITE_ROOK, 200, 0, 50, 50));
    props.push_back(createSprite(WHITE_PAWN, 250, 0, 50, 50));

    props.push_back(createSprite(BLACK_QUEEN, 0, 50, 50, 50));
    props.push_back(createSprite(BLACK_KING, 50, 50, 50, 50));
    props.push_back(createSprite(BLACK_BISHOP, 100, 50, 50, 50));
    props.push_back(createSprite(BLACK_KNIGHT, 150, 50, 50, 50));
    props.push_back(createSprite(BLACK_ROOK, 200, 50, 50, 50));
    props.push_back(createSprite(BLACK_PAWN, 250, 50, 50, 50));

    return props;
}

Entity* createEntity(const char* name, int x, int y) {
	Entity* entity = new Entity(x, y);
	entity->addComponent<GraphicsComponent>(new GraphicsComponent(entity, name));
	return entity;
}

Entity* createEntityOnGrid(const char* name, Grid* grid, Vec2D index, PieceComponent::PieceType pieceType, PieceComponent::PlayerType playerType) {
	Entity* entity = new Entity();
	entity->addComponent<GraphicsComponent>(new GraphicsComponent(entity, name));
	entity->addComponent<GridComponent>(new GridComponent(entity, index));
	entity->addComponent<PieceComponent>(new PieceComponent(entity, pieceType, playerType));
	grid->addChessPiece(entity, index);
	return entity;
}

/*
 * 
 */
int main(int argc, char** argv) {

 //   GraphicsSystem* _graphics = new GraphicsSystem("Supreme Chess", 400, 400);

 //   _graphics->showWindow();

 //   _graphics->loadSprite(CHESSBOARD, "res/chessboard.png");
	//_graphics->loadSprite(CHESSBOARD_WHITE, "res/chessboard_white.png");
	//_graphics->loadSprite(CHESSBOARD_BLACK, "res/chessboard_black.png");

 //   GraphicsSystem::SpriteProperties spriteProps;
 //   spriteProps = loadSprites();
 //   _graphics->loadSpritesheet(spriteProps, "res/chess_pieces_small.png");
	//_graphics->loadSprite(BORDER, "res/border.png");

	//Grid grid(8, 8);

	//_entities.push_back(createEntityOnGrid(BLACK_ROOK, &grid, Vec2D(0, 0), PieceComponent::PieceType::ROOK, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_KNIGHT, &grid, Vec2D(1, 0), PieceComponent::PieceType::KNIGHT, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_BISHOP, &grid, Vec2D(2, 0), PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_KING, &grid, Vec2D(3, 0), PieceComponent::PieceType::KING, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_QUEEN, &grid, Vec2D(4, 0), PieceComponent::PieceType::QUEEN, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_BISHOP, &grid, Vec2D(5, 0), PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_KNIGHT, &grid, Vec2D(6, 0), PieceComponent::PieceType::KNIGHT, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_ROOK, &grid, Vec2D(7, 0), PieceComponent::PieceType::ROOK, PieceComponent::PlayerType::BLACK));

	//_entities.push_back(createEntityOnGrid(BLACK_PAWN, &grid, Vec2D(0, 1), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_PAWN, &grid, Vec2D(1, 1), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_PAWN, &grid, Vec2D(2, 1), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_PAWN, &grid, Vec2D(3, 1), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_PAWN, &grid, Vec2D(4, 1), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_PAWN, &grid, Vec2D(5, 1), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_PAWN, &grid, Vec2D(6, 1), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK));
	//_entities.push_back(createEntityOnGrid(BLACK_PAWN, &grid, Vec2D(7, 1), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::BLACK));

	//_entities.push_back(createEntityOnGrid(WHITE_ROOK, &grid, Vec2D(0, 7), PieceComponent::PieceType::ROOK, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_KNIGHT, &grid, Vec2D(1, 7), PieceComponent::PieceType::KNIGHT, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_BISHOP, &grid, Vec2D(2, 7), PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_KING, &grid, Vec2D(3, 7), PieceComponent::PieceType::KING, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_QUEEN, &grid, Vec2D(4, 7), PieceComponent::PieceType::QUEEN, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_BISHOP, &grid, Vec2D(5, 7), PieceComponent::PieceType::BISHOP, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_KNIGHT, &grid, Vec2D(6, 7), PieceComponent::PieceType::KNIGHT, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_ROOK, &grid, Vec2D(7, 7), PieceComponent::PieceType::ROOK, PieceComponent::PlayerType::WHITE));

	//_entities.push_back(createEntityOnGrid(WHITE_PAWN, &grid, Vec2D(0, 6), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_PAWN, &grid, Vec2D(1, 6), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_PAWN, &grid, Vec2D(2, 6), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_PAWN, &grid, Vec2D(3, 6), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_PAWN, &grid, Vec2D(4, 6), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_PAWN, &grid, Vec2D(5, 6), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_PAWN, &grid, Vec2D(6, 6), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE));
	//_entities.push_back(createEntityOnGrid(WHITE_PAWN, &grid, Vec2D(7, 6), PieceComponent::PieceType::PAWN, PieceComponent::PlayerType::WHITE));

	//grid.resolvePositions();

	//Entity border;
	//border.addComponent<GraphicsComponent>(new GraphicsComponent(&border, BORDER));

	//int quit = 0;
	//SDL_Event event;

	//while (!quit) {

	//	while (SDL_PollEvent(&event)) {
	//		if (event.type == SDL_QUIT) {
	//			quit = 1;
	//		}

	//		if (event.type == SDL_MOUSEBUTTONDOWN) {
	//			if (event.button.button == SDL_BUTTON_LEFT) {
	//				grid.selectGrid(Vec2D(event.button.x, event.button.y));
	//			}
	//		}
	//	}

	//	// Make sure positions are updated from grid
	//	grid.resolvePositions();

	//	// Clean up any dead entities
	//	for (auto it = _entities.begin(); it != _entities.end(); it++) {
	//		if (!(*it)->isAlive()) {
	//			delete *it;
	//			it = _entities.erase(it);
	//		}
	//	}

	//	_graphics->clearRenderer();

	//	for (int i = 0; i < grid.getNumRows(); i++) {
	//		for (int j = 0; j < grid.getNumCols(); j++) {
	//			Vec2D squareLoc(i, j);
	//			Entity* gridSquare = grid.getGridSquare(squareLoc);
	//			if (gridSquare != nullptr) {
	//				_graphics->drawSprite(gridSquare->getComponent<GraphicsComponent>()->getName(), gridSquare->getPosition().x, gridSquare->getPosition().y);
	//			}
	//		}
	//	}

	//	if (grid.getSelectedSquare() != nullptr) {
	//		Vec2D position = grid.getSelectedSquare()->getPosition();
	//		_graphics->drawSprite(BORDER, position.x, position.y);
	//	}

	//	for (auto it = _entities.begin(); it != _entities.end(); it++) {
	//		Entity* entity = (*it);
	//		if (entity->getComponent<GraphicsComponent>() != nullptr) {
	//			_graphics->drawSprite(entity->getComponent<GraphicsComponent>()->getName(), entity->getPosition().x, entity->getPosition().y);
	//		}
	//	}

	//	_graphics->render();

	//}

 //   _graphics->closeWindow();

 //   delete _graphics;

	//for (auto it = _entities.begin(); it != _entities.end(); it++) {
	//	delete *it;
	//}

	//_entities.clear();

	Game game;

	game.setup();

	game.runMainLoop();

    return 0;
}

