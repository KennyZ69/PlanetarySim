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

	// draw horizontal lines
	// for (int i = 0; i < GRID_SIZE; i++) {
	// 	for (int j = 0; j < GRID_SIZE - 1; j++) {
	// 		Vec3D a = grid->vertices[i][j];
	// 		Vec3D b = grid->vertices[i][j + 1];
	// 		glVertex3f(a.x, a.y, a.z);
	// 		glVertex3f(b.x, b.y, b.z);
	//
	// 		a = grid->vertices[j][i];
	// 		b = grid->vertices[j + 1][i];
	// 		glVertex3f(a.x, a.y, a.z);
	// 		glVertex3f(b.x, b.y, b.z);
	//
	// 	}
	// }
	
	for (float i = -GRID_SIZE; i<=GRID_SIZE; i+=GRID_SPACING) {
		// horizontal lines
		glVertex3f(-GRID_SIZE, 0, i);
		glVertex3f(GRID_SIZE, 0, i);

		// vertical lines
		glVertex3f(i, 0, -GRID_SIZE);
		glVertex3f(i, 0, GRID_SIZE);
	}

	glEnd();
	glPopMatrix();
}
