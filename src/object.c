/* object.c */

#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "in/object.h"
#include "in/util.h"


void clear_objects(Object objects[], int *obj_count) {
	*obj_count = 0;
	memset(objects, 0, sizeof(Object) * MAX_OBJECTS);
}

void init_objects(Object objects[], int *obj_count) {
	clear_objects(objects, obj_count);

	*obj_count = 4;

	// Sun
	objects[0] = (Object){
	.name = "Sun",
	.pos = {0, 0, 0},
	.vel = {0, 0, 0},
	.mass = 1.0f, // in solar masses
	.radius = 10.0f, // exaggerated size for visibility
	.color = {255, 255, 0}
	};

	// Mercury
	objects[1] = (Object){
	.name = "Mercury",
	.pos = {14.8f, 0, 0},
	.vel = {0, 0, 47.4e3f}, // m/s, will be rescaled later
	.mass = 0.33e24f / MASS_SCALE,
	.radius = 3.0f,
	.color = {153, 153, 153}
	};

	// Venus
	objects[2] = (Object){
	.name = "Venus",
	.pos = {21.80f, 0, 0},
	.vel = {0, 0, 35.0e3f},
	.mass = 4.87e24f / MASS_SCALE,
	.radius = 3.4f,
	.color = {255, 204, 153}
	};

	// Earth
	objects[3] = (Object){
	.name = "Earth",
	.pos = {38.0f, 0, 0},
	.vel = {0, 0, 29.8e3f},
	.mass = 5.97e24f / MASS_SCALE,
	.radius = 4.0f,
	.color = {0, 0, 255}
	};

	// Fix velocities with orbital speed
	for (int i = 1; i < *obj_count; i++) {
		initial_velocity(&objects[i], &objects[0]);
	}
}

void initial_velocity(Object *obj, Object *central) {
	Vec3D r = vec3d_sub(obj->pos, central->pos);
	float dist = sqrt(r.x*r.x + r.z*r.z);

	float speed = sqrt(G * central->mass / dist);

	// perpendicular direction in X-Z plane
	Vec3D vel = { -r.z / dist, 0, r.x / dist };

	// set initial velocity
	obj->vel = vec3d_scale(vel, speed);
}

void draw_object(const Object *obj) {
	printf("Drawing object %s at (%.2f, %.2f, %.2f)\n", obj->name, obj->pos.x, obj->pos.y, obj->pos.z);
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

// Vec3D *compute_gravity(Object objects[], int obj_count) {
void compute_gravity(Object objects[], int obj_count, Vec3D forces[]) {
	// Vec3D *forces = malloc(obj_count * sizeof(Vec3D));
	// memset(forces, 0, obj_count*sizeof(Vec3D));
	
	for (int i = 0; i < obj_count; i++) {
		forces[i] = (Vec3D){0.0f, 0.0f, 0.0f};
	}

	for (int i = 0; i < obj_count; i++) {
		for (int j = i+1; j < obj_count; j++) {
			// if (i == j) continue;

			Vec3D r = vec3d_sub(objects[j].pos, objects[i].pos);
			float dist2 = r.x * r.x + r.y * r.y + r.z * r.z + 1e-6f; // softening factor to avoid singularities
			float dist = sqrtf(dist2);

			float force_mag = G * objects[i].mass * objects[j].mass / dist2;
			Vec3D force = (Vec3D){
				force_mag * r.x / dist,
				force_mag * r.y / dist,
				force_mag * r.z / dist,
			};

			// newton's third law for equal and opposite reaction
			forces[i] = vec3d_add(forces[i], force);
			forces[j] = vec3d_sub(forces[j], force); // equal and opposite reaction
		}
	}

}

void leapfrog_step(Object *objects, int obj_count, float dt) {
	// Vec3D *forces = compute_gravity(objects, obj_count);
	Vec3D forces[MAX_OBJECTS];
	compute_gravity(objects, obj_count, forces);

	for (int i = 0; i < obj_count; i++) {
		Vec3D acc = {
			forces[i].x / objects[i].mass,
			forces[i].y / objects[i].mass,
			forces[i].z / objects[i].mass,
		};

		// update velocity by half step
		objects[i].vel = vec3d_add(objects[i].vel, (Vec3D){
			acc.x * (dt *0.5f),
			acc.y * (dt * 0.5f),
			acc.z * (dt * 0.5f),
		});

		objects[i].pos = vec3d_add(objects[i].pos, (Vec3D){
			objects[i].vel.x * dt,
			objects[i].vel.y * dt,
			objects[i].vel.z * dt,
		});
	}
	
	// recompute acceleration at new position
	compute_gravity(objects, obj_count, forces);

	for (int i = 0; i < obj_count; i++) {
		Vec3D acc = (Vec3D){
			forces[i].x / objects[i].mass,
			forces[i].y / objects[i].mass,
			forces[i].z / objects[i].mass,
		};

		// update velocity by another half step
		objects[i].vel = vec3d_add(objects[i].vel, (Vec3D){
			acc.x * (dt *0.5f),
			acc.y * (dt * 0.5f),
			acc.z * (dt * 0.5f),
		});
	}
}
