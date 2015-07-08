#ifndef _ex19_h
#define _ex19_h

#include "object.h"

struct Monster {
	Object proto;
	int hit_points;
};

typedef struct Monster Monster;

int monster_attack(void *self, int damage);
int monster_init(void *self);

struct Room {
	Object proto;

	Monster *bad_guy;

	struct Room *north;
	struct Room *south;
	struct Room *east;
	struct Room *west;
};

typedef struct Room Room;

void *Room_move(void *self, Direction direction);

struct Map {
	Object proto;
	Room *start;
	Room *location;
};

typedef struct Map Map;

void *Map_move(void *self, Direction direction);

#endif
