#ifndef GRIDCOMPONENT_H
#define GRIDCOMPONENT_H

#include "Component.h"
#include "Vec2D.h"

class GridComponent : public Component {

private:
	Vec2D _index;

public:
	GridComponent(Entity* parent, Vec2D index) : Component(parent), _index(index) {}

	inline Vec2D getGridIndex() const { return _index; }

	inline void setGridIndex(Vec2D index) { _index = index; }

};

#endif