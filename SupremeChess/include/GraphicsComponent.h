#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"

class GraphicsComponent : public Component {

private:
	const char* _name;
	bool _isVisible;

public:
	GraphicsComponent(Entity* parent, const char* name) : Component(parent), _name(name), _isVisible(true) {};

	// Getters
	const char* getName() const {
		return _name;
	}

	bool getVisible() const {
		return _isVisible;
	}

	// Setters
	void setName(const char* name) {
		_name = name;
	}

	void setVisible(bool isVisible) {
		_isVisible = isVisible;
	}
};

#endif