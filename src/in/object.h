/* object.h */

#pragma once

#include "util.h"

#define MAX_OBJECTS 16

typedef struct {
	Vec3D pos, vel;
	float mass;
	float radius;
} Object;

void init_objects(Object objects[], int *obj_count);

void clear_objects(Object objects[], int *obj_count);

void add_object(const char *name, Vec3D pos, Vec3D vel, double mass, float radius, Color color);
