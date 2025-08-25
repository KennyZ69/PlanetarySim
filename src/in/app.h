/* app.h */

#pragma once

#include "object.h"
#include "camera.h"

bool init();

void cleanup();

void run();

// initialize OpenGL state
void gl_setup();

// resize OpenGL viewport and projection matrix when resizing window
void gl_resize(int w, int h);

// update all the objects and physics in the scene
void update_scene();

// render the updated scene from the cam's perspective
void render_scene(Camera* cam);
