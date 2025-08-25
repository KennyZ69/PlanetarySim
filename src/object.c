/* object.c */

#include <string.h>
#include "in/object.h"


void clear_objects(Object objects[], int *obj_count) {
	*obj_count = 0;
	memset(objects, 0, sizeof(Object) * MAX_OBJECTS);
}

void init_objects(Object objects[], int *obj_count) {
	clear_objects(objects, obj_count);
}

void add_object(const char *name, Vec3D pos, Vec3D vel, double mass, float radius, Color color) {

}
