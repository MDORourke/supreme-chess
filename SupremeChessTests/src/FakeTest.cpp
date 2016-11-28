#include <gtest\gtest.h>

#include "Vec2D.h"

TEST(FakeTest, Fakey) {
	Vec2D vec;
	ASSERT_EQ(vec.x, 0);
	ASSERT_EQ(vec.y, 0);
}