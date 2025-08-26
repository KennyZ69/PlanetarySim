/* object.h */

#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "util.h"

#define MAX_OBJECTS 16

typedef struct {
	Vec3D pos, vel;
	float mass;
	float radius;
	Color color;
	char name[20];
} Object;

void init_objects(Object objects[], int *obj_count);

void clear_objects(Object objects[], int *obj_count);

int add_object(const char *name, Vec3D pos, Vec3D vel, double mass, float radius, Color color);

void draw_object(const Object *obj);

void leapfrog_step(Object objects[], int obj_count, float dt);

// compute the gravitational forces on each object and return an array of acceleration vectors
// Vec3D *compute_gravity(Object objects[], int obj_count);
void compute_gravity(Object objects[], int obj_count, Vec3D forces[]); // pass in preallocated forces array

void initial_velocity(Object *obj, Object *central);
