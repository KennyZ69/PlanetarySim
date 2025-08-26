/* grid.c */

#include "in/grid.h"
#include <GL/gl.h>

void init_grid(Grid *grid) {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			grid->vertices[i][j] = (Vec3D){
				.x = (i - GRID_SIZE / 2.0f) * GRID_SPACING,
				.y = (j - GRID_SIZE / 2.0f) * GRID_SPACING,
				.z = 0.0f
			};
		}
	}
}

void render_grid(Grid *grid) {
	glColor3f(0.3f, 0.3f, 0.5f);
	glBegin(GL_LINES);

	for (float i = -GRID_SIZE; i<=GRID_SIZE; i+=GRID_SPACING) {
		// horizontal lines
		glVertex3f(-GRID_SIZE, 0, i);
		glVertex3f(GRID_SIZE, 0, i);

		// vertical lines
		glVertex3f(i, 0, -GRID_SIZE);
		glVertex3f(i, 0, GRID_SIZE);
	}

	glEnd();
}

// void update_grid(Grid *grid, Object *objects, int obj_count) {
//
// }
