#include "Entity.h"

Entity::~Entity() {
	for (auto& c : _components) {
		delete c.second;
	}
}