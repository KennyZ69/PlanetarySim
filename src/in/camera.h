/* camera.h */

#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "util.h"

typedef struct {
	float vertical, horizontal; // angles in radians
	float dist;
	float zoom, rot, pan; // sensitivity
	bool rotating, panning;
	int last_x, last_y;
	Vec3D target; // the point the cam is looking at
} Camera;

void cam_init(Camera* cam);

// handle given event with camera
void handle_cam_event(Camera* cam, SDL_Event* ev, int winW, int winH);

void apply_cam_view(Camera *cam);
