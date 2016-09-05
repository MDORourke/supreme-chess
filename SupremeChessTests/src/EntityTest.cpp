#include "stdafx.h"
#include <gtest\gtest.h>

#include "Entity.h"
#include "MockComponent.h"

TEST(EntityTest, CanAddComponent) {

	Entity entity;
	MockComponent *component = new MockComponent(&entity);

	entity.addComponent<MockComponent>(component);
	
	MockComponent* actualComponent = entity.getComponent<MockComponent>();

	EXPECT_EQ(actualComponent, component);

}

TEST(EntityTest, ReturnNULLIfNoComponent) {
	Entity entity;

	MockComponent* actualComponent = entity.getComponent<MockComponent>();

	EXPECT_EQ(actualComponent, nullptr);
}

TEST(EntityTest, ReturnCorrectComponent) {
	Entity entity;

	MockComponent* expected = new MockComponent(&entity);
	MockComponentTwo* alt = new MockComponentTwo(&entity);

	entity.addComponent<MockComponent>(expected);
	entity.addComponent<MockComponentTwo>(alt);

	MockComponent* actual = entity.getComponent<MockComponent>();

	EXPECT_EQ(actual, expected);

}