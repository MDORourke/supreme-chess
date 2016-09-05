#ifndef VEC2D_H
#define VEC2D_H

struct Vec2D {
	int x, y;

	Vec2D() : x(0), y(0) {}
	Vec2D(int in_x, int in_y) : x(in_x), y(in_y) {}

};

inline bool operator==(Vec2D a, Vec2D b) {
	return a.x == b.x && a.y == b.y;
}

#endif