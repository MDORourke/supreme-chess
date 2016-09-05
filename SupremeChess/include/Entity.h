#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <typeindex>
#include <iostream>

#include "Component.h"
#include "Vec2D.h"

class Entity {

private:
	std::map<std::type_index, Component*> _components;

	Vec2D _position;
	bool _isAlive = true;

public:
	Entity() : _position(0, 0) {}
	Entity(Vec2D position) : _position(position) {}
	Entity(int x, int y) : _position(x, y) {}

	~Entity();

	// Getters
	Vec2D getPosition() const { return _position; }
	bool isAlive() const { return _isAlive; }

	// Setters
	void setPosition(Vec2D position) { _position = position; }
	void kill() { _isAlive = false; }

	template <typename T>
	inline void addComponent(Component* component) {
		_components[std::type_index(typeid(T))] = component;
	}

	template <typename T>
	inline T* getComponent() {
		auto it = _components.find(std::type_index(typeid(T)));
		if (it != _components.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return nullptr;
	}

	template <typename T>
	inline bool hasComponent() {
		auto it = _components.find(std::type_index(typeid(T)));
		return (it != _components.end());
	}

};

#endif