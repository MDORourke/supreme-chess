#ifndef DIRECTION_H
#define DIRECTION_H

class Direction {
public:
	typedef unsigned short DirectionMask;

	static const DirectionMask NONE = 0x00;
	static const DirectionMask NORTH = 0x01;
	static const DirectionMask NORTHEAST = 0x02;
	static const DirectionMask EAST = 0x04;
	static const DirectionMask SOUTHEAST = 0x08;
	static const DirectionMask SOUTH = 0x10;
	static const DirectionMask SOUTHWEST = 0x20;
	static const DirectionMask WEST = 0x40;
	static const DirectionMask NORTHWEST = 0x80;
	static const DirectionMask ALL = 0xFF;

};

#endif