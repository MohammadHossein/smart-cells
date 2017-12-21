/*
 * In The Name Of God
 * ========================================
 * [] File Name : multiplayer.h
 *
 * [] Creation Date : 19-01-2016
 *
 * [] Created By : Iman Tabrizian (tabrizian@outlook.com)
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani and Iman Tabrizian.
*/
#ifndef GOOD_MULTIPLAYER_H
#define GOOD_MULTIPLAYER_H

enum move_direction {
	NORTH = 1,
	SOUTH,
	NORTHEAST,
	NORTHWEST,
	SOUTHEAST,
	SOUTHWEST,
};

struct cell_move_data {
    int cell_energy;
    enum move_direction move_direction;
};

struct cell_position {
    int x;
    int y;
};

struct cell_position cell_new(struct cell_position your_initial_position);

struct cell_move_data cell_move(struct cell_move_data your_move);

#endif //GOOD_MULTIPLAYER_H
