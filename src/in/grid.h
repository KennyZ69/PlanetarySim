/* grid.h */

#pragma once

#include <GL/gl.h>
#include "util.h"
#include "object.h"

#define GRID_SPACING 1.0f
#define GRID_SIZE 50

typedef struct {
	Vec3D vertices[GRID_SIZE][GRID_SIZE];
} Grid;

void init_grid(Grid *grid);

void render_grid(Grid *grid);

void update_grid(Grid *grid, Object objects[], int obj_count);
