#include "Grid.h"

Grid::Grid(int numRows, int numCols) {
	_numRows = numRows;
	_numCols = numCols;

	_selectionState = new GridSelectionState(this);

	initialiseGrid();
}

Grid::~Grid() {
	for (int i = 0; i < _numRows; i++) {
		for (int j = 0; j < _numCols; j++) {
			delete _gridSquares[i][j];
		}
		delete[] _gridSquares[i];
	}
	delete[] _gridSquares;

	delete _selectionState;
}

void Grid::initialiseGrid() {

	_gridSquares = new Entity**[_numRows];
	_pieces = new Entity**[_numRows];

	for (int i = 0; i < _numRows; i++) {

		_gridSquares[i] = new Entity*[_numCols];
		_pieces[i] = new Entity*[_numCols];

		for (int j = 0; j < _numCols; j++) {

			Vec2D gridSquareIndex;
			gridSquareIndex.x = i;
			gridSquareIndex.y = j;
			_gridSquares[i][j] = createGridSquare(gridSquareIndex);
			_pieces[i][j] = nullptr;

		}
	}
}

Entity* Grid::createGridSquare(Vec2D gridSquareIndex) {
	Vec2D position = getPositionFromGridSquare(gridSquareIndex);

	Entity* gridSquare = new Entity(position);

	if ((gridSquareIndex.x + gridSquareIndex.y) % 2 == 1) {
		gridSquare->addComponent<GraphicsComponent>(new GraphicsComponent(gridSquare, "chessboard_white"));
	}
	else {
		gridSquare->addComponent<GraphicsComponent>(new GraphicsComponent(gridSquare, "chessboard_black"));
	}

	gridSquare->addComponent<GridComponent>(new GridComponent(gridSquare, gridSquareIndex));

	return gridSquare;
}

Vec2D Grid::getGridSquareFromPosition(Vec2D position) const {
	Vec2D gridSquare;
	gridSquare.x = std::floor(position.x / SQUARE_SIZE);
	gridSquare.y = std::floor(position.y / SQUARE_SIZE);
	return gridSquare;
}

Vec2D Grid::getPositionFromGridSquare(Vec2D gridSquare) const {
	Vec2D position;
	position.x = gridSquare.x * SQUARE_SIZE;
	position.y = gridSquare.y * SQUARE_SIZE;
	return position;
}

Vec2D Grid::getPositionClampedToGridSquare(Vec2D position) const {
	return getPositionFromGridSquare(getGridSquareFromPosition(position));
}

Entity* Grid::getGridSquare(Vec2D index) const {
	if (indexIsInBounds(index)) {
		return _gridSquares[index.x][index.y];
	}
	return nullptr;
}

Entity* Grid::getChessPiece(Vec2D index) const {
	if (indexIsInBounds(index)) {

		return _pieces[index.x][index.y];

	}
	return nullptr;
}

void Grid::addChessPiece(Entity* piece, Vec2D index) {
	// Make sure entity has the correct components
	if (!(piece->hasComponent<GridComponent>() && piece->hasComponent<PieceComponent>())) {
		std::cout << "Piece could not be added at " << index.x << ", " << index.y << std::endl;
		return;
	}

	if (indexIsInBounds(index)) {
		_pieces[index.x][index.y] = piece;
	}

}

void Grid::moveChessPiece(Vec2D from, Vec2D to) {
	if (indexIsInBounds(from) && indexIsInBounds(to)) {

		// Does a piece exist at the old location?
		if (_pieces[from.x][from.y] == nullptr) {
			return;
		}

		// Move to new position
		_pieces[from.x][from.y]->getComponent<GridComponent>()->setGridIndex(to);
		_pieces[from.x][from.y]->getComponent<PieceComponent>()->setHasMoved(true);

		// Swap position
		_pieces[to.x][to.y] = _pieces[from.x][from.y];
		_pieces[from.x][from.y] = nullptr;

	}
}

void Grid::takeChessPiece(Vec2D pieceToTake) {
	// Is there a piece at the required index?
	if (getChessPiece(pieceToTake) != nullptr) {
		// Kill the entity
		getChessPiece(pieceToTake)->kill();

		// Remove the piece from the board
		_pieces[pieceToTake.x][pieceToTake.y] = nullptr;
		std::cout << "Piece taken!" << std::endl;
	}
}

bool Grid::isLegalMove(Vec2D from, Vec2D to) {

	// Get piece at starting point (if exists)
	Entity* piece = getChessPiece(from);
	if (piece == nullptr) {
		return false;
	}

	return isLegalMove(from, to, *piece->getComponent<PieceComponent>());

}

bool Grid::isLegalMove(Vec2D from, Vec2D to, PieceComponent component) {
	// Switch on type of piece
	switch (component.getPieceType()) {
	case PieceComponent::PieceType::BISHOP:
		return to.y - from.y != 0 && std::abs((to.x - from.x) / (to.y - from.y)) == 1;
		break;
	case PieceComponent::PieceType::KING:
		return (std::abs(from.x - to.x) == 1 && std::abs(from.y - to.y) == 0) || (std::abs(from.y - to.y) == 1 & std::abs(from.x - to.x) == 0);
		break;
	case PieceComponent::PieceType::KNIGHT:
		return (std::abs(from.x - to.x) == 2 && std::abs(from.y - to.y) == 1) || (std::abs(from.x - to.x) == 1 && std::abs(from.y - to.y) == 2);
		break;
	case PieceComponent::PieceType::PAWN:
		if (component.hasMoved()) {
			if (component.getPlayerType() == PieceComponent::WHITE) {
				return from.x - to.x == 0 && from.y - to.y == 1;
			}
			else {
				return from.x - to.x == 0 && from.y - to.y == -1;
			}
		}
		else {
			if (component.getPlayerType() == PieceComponent::WHITE) {
				return from.x - to.x == 0 && from.y - to.y <= 2 && from.y - to.y > 0;
			}
			else {
				return from.x - to.x == 0 && from.y - to.y >= -2 && from.y - to.y < 0;
			}
		}
		break;
	case PieceComponent::PieceType::QUEEN:
		// A few cases here
		component.setPieceType(PieceComponent::PieceType::BISHOP);
		if (isLegalMove(from, to, component)) {
			return true;
		}
		component.setPieceType(PieceComponent::PieceType::ROOK);
		if (isLegalMove(from, to, component)) {
			return true;
		}
		return false;
		break;
	case PieceComponent::PieceType::ROOK:
		return from.x - to.x == 0 || from.y - to.y == 0;
		break;
	}

	return false;
}

bool Grid::isLegalTake(Vec2D from, Vec2D to) {

	// Get piece at starting point (if exists)
	Entity* piece = getChessPiece(from);
	if (piece == nullptr) {
		return false;
	}

	return isLegalTake(from, to, *piece->getComponent<PieceComponent>());

}

bool Grid::isLegalTake(Vec2D from, Vec2D to, PieceComponent component) {

	// Switch on type of piece
	switch (component.getPieceType()) {
	case PieceComponent::PieceType::BISHOP:
	case PieceComponent::PieceType::KING:
	case PieceComponent::PieceType::KNIGHT:
	case PieceComponent::PieceType::ROOK:
		return isLegalMove(from, to, component);
		break;
	case PieceComponent::PieceType::PAWN:
	{
		int allowedDiff;
		if (component.getPlayerType() == PieceComponent::WHITE) {
			allowedDiff = 1;
		}
		else {
			allowedDiff = -1;
		}
		return std::abs(from.x - to.x) == 1 && from.y - to.y == allowedDiff;
	}
	break;
	case PieceComponent::PieceType::QUEEN:
		// A few cases here
		component.setPieceType(PieceComponent::PieceType::BISHOP);
		if (isLegalMove(from, to, component)) {
			return true;
		}
		component.setPieceType(PieceComponent::PieceType::ROOK);
		if (isLegalMove(from, to, component)) {
			return true;
		}
		return false;
		break;
	}
}

void Grid::selectGrid(Vec2D position) {
	Vec2D gridIndex = getGridSquareFromPosition(position);

	// Is it valid?
	if (indexIsInBounds(gridIndex)) {

		_targetGridSquare = getGridSquare(gridIndex);

		_selectionState->checkState();

	}
}

void Grid::resolvePositions() {
	for (int i = 0; i < _numRows; i++) {
		for (int j = 0; j < _numCols; j++) {
			if (_pieces[i][j] != nullptr) {
				_pieces[i][j]->setPosition(getPositionFromGridSquare(Vec2D(i, j)));
			}
		}
	}
}

void Grid::endTurn() {
	switch (_currentPlayer) {
	case PieceComponent::PlayerType::WHITE:
		_currentPlayer = PieceComponent::PlayerType::BLACK;
		std::cout << "Black Player's turn" << std::endl;
		break;
	case PieceComponent::PlayerType::BLACK:
		_currentPlayer = PieceComponent::PlayerType::WHITE;
		std::cout << "White Player's turn" << std::endl;
		break;
	}
}

