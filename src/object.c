/* object.c */

#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>
#include "in/object.h"


void clear_objects(Object objects[], int *obj_count) {
	*obj_count = 0;
	memset(objects, 0, sizeof(Object) * MAX_OBJECTS);
}

void init_objects(Object objects[], int *obj_count) {
	clear_objects(objects, obj_count);

	objects[(*obj_count)++] = (Object){
		.pos = {0.0f, 1.5f, 0.0f},
		.vel = {0.0f, 0.0f, 0.0f},
		.mass = 1.989e30f, // mass of the sun
		.radius = 2.0f,
		.color = {255, 255, 0} // yellow
	};
	objects[(*obj_count)++] = (Object){
		.pos = {15.0f, 1.5f, 0.0f},
		.vel = {0.0f, 0.0f, 0.0f}, // approx orbital velocity of earth
		.mass = 5.972e24f, // mass of the earth
		.radius = 1.0f,
		.color = {0, 0, 255} // blue
	};
}

// int add_object(const char *name, Vec3D pos, Vec3D vel, double mass, float radius, Color color) {
//
// }

void draw_object(const Object *obj) {
	glPushMatrix();
		glColor3ub(obj->color.r, obj->color.g, obj->color.b);
		GLUquadric* quad = gluNewQuadric();
		gluQuadricDrawStyle(quad, GLU_FILL);
		gluQuadricNormals(quad, GLU_SMOOTH);
		glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
		gluSphere(quad, obj->radius, 32, 32);
		gluDeleteQuadric(quad);
	glPopMatrix();
}
