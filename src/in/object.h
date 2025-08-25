/* object.h */

#pragma once

#include "util.h"

#define MAX_OBJECTS 16

typedef struct {
	Vec3D pos, vel;
	float mass;
	float radius;
} Object;

void init_objects();
