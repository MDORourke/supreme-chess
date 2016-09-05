#ifndef MOCKCOMPONENT_H
#define MOCKCOMPONENT_H

#include <Component.h>
#include <gmock\gmock.h>

class MockComponent : public Component {

public:
	MockComponent(Entity* parent) : Component(parent) {}

};

class MockComponentTwo : public Component {

public:
	MockComponentTwo(Entity* parent) : Component(parent) {}

};

#endif