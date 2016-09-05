#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {

protected:
	Entity* _parent;

public:
	Component(Entity* parent) : _parent(parent) {}

	virtual ~Component() {};

	Entity* getParent() { return _parent; }

};

#endif