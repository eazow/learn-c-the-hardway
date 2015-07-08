#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"

int Monster_attack(void *self, int damage)
{
	Monster *monster = self;

	printf("You attack %s!\n", monster->proto.description);

	monster->hit_points -= damage;

	if(monster->hit_points > 0) {
		printf("It is still alive.\n");
		return 0;
	}
	else {
		printf("It is dead!\n");
		return 1;
	}
}

int Monster_init(void *self)
{
	Monster *monster = self;
	monster->hit_points = 10;
	return 1;
}

Object MonsterProto = {
	.init = Monster_init,
	.attack = Monster_attack
};

void *Room_move(void *self, Direction direction)
{
	Room *room = self;
	Room *next = NULL;

	if(direction==NORTH && room->north) {
		printf("You go north, into:\n");
		next = room->north;
	}
	else if(direction==SOUTH && room->south) {
		printf("You go south, into:\n");
		next = room->south;
	}
	else if(direction==EAST && room->east) {
		printf("You go east, into:\n");
		next = room->east;
	}
	else if(direction==WEST && room->west) {
		printf("You go west, into:\n");
		next = room->west;
	}
	else {
		printf("You cant't go that direction.");
		next = NULL;
	}

	if(next) {
		next->proto.describe(next);
	}

	return next;
}

int Room_attack(void *self, int damage)
{
	Room *room = self;
	Monster *monster = room->bad_guy;

	if(monster) {
		monster->proto.attack(monster, damage);
		return 1;
	}
	else {
		printf("You flail in the air at nothing. Idiot.\n");
		return 0;
	}
}

Object RoomProto = {
	.move = Room_move,
	.attack = Room_attack
};

void *Map_move(void *self, Direction direction)
{
	Map *map = self;
	Room *location = map->location;
	Room *next = NULL;

	next = location->proto.move(location, direction);

	if(next) {
		map->location = next;
	}

	return next;
}

int Map_attack(void *self, int damage) 
{
	Map *map = self;
	Room *location = map->location;

	return location->proto.attack(location, damage);
}

int Map_init(void *self) 
{
	Map *map = self;

	Room *hall = Object_new(sizeof(Room), RoomProto, "The great Hall");
	Room *throne = Object_new(sizeof(Room), RoomProto, "The throne room");
	Room *arena = Object_new(sizeof(Room), RoomProto, "The arena, with the minotaur");
	Room *kitchen = Object_new(sizeof(Room), RoomProto, "Kitchen, you have the knife now");

	arena->bad_guy = Object_new(sizeof(Monster), MonsterProto, "The evil minotaur");

	hall->north = throne;

	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;

	arena->east = throne;
	kitchen->west = throne;

	map->start = hall;
	map->location = hall;

	return 1;
}

Object MapProto = {
	.init = Map_init,
	.move = Map_move,
	.attack = Map_attack
};

int process_input(Map *map)
{
	printf("\n> ");
	
	char ch = getchar();
	getchar();

	int damage = rand()%4;

	switch(ch) {
		case -1:
			printf("Giving up? You suck.\n");
			return 0;
			break;

		case 'n':
			map->proto.move(map, NORTH);
			break;

		case 's':
			map->proto.move(map, SOUTH);
			break;

		case 'e':
			map->proto.move(map, EAST);
			break;

		case 'w':
			map->proto.move(map, WEST);
			break;

		case 'a':
			map->proto.attack(map, damage);
			break;

		case 'l':
			printf("You can go:\n");
			if(map->location->north)
				printf("NORTH\n");
			if(map->location->south)
				printf("SOUTH\n");
			if(map->location->east)
				printf("EAST\n");
			if(map->location->west)
				printf("WEST\n");
			break;

		default:
			printf("What?: %d\n", ch);

	}

	return 1;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	Map *map = Object_new(sizeof(Map), MapProto, "The Hall of the Minotaur.");

	printf("You enter the ");
	
	map->location->proto.describe(map->location);

	while(process_input(map)) {}

	return 0;
}



















