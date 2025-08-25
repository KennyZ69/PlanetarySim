/* camera.c */

#include "in/camera.h"

void cam_init(Camera *cam) {
	cam->vertical = 0.75f; // slightly above the horizon
	cam->horizontal = 3.14f / 4.0f; // 45 degrees in radians
	cam->dist = 40.0f;
	cam->zoom = 0.5f;
	cam->rot = 0.005f;
	cam->pan = 0.01f;
	cam->rotating = false;
	cam->panning = false;
	cam->last_x = 0;
	cam->last_y = 0;
	cam->target = (Vec3D){0.0f, 0.0f, 0.0f};
}

void apply_cam_view(Camera *cam) {
	float camX = cam->target.x + cam->dist * cosf(cam->vertical) * sinf(cam->horizontal);
	float camY = cam->target.y + cam->dist * sinf(cam->vertical);
	float camZ = cam->target.z + cam->dist * cosf(cam->vertical) * cosf(cam->horizontal);
	gluLookAt(camX, camY, camZ, cam->target.x, cam->target.y, cam->target.z, 0.0f, 1.0f, 0.0f);
}
