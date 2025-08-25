/* object.c */

#include <string.h>
#include "in/object.h"

Object objects[MAX_OBJECTS];
int obj_count = 0;

void clear_objects() {
	obj_count = 0;
	memset(objects, 0, sizeof(objects));
}

void init_objects() {
	clear_objects();
}

void add_object(const char *name, Vec3D pos, Vec3D vel, double mass, float radius, Color color) {

}
