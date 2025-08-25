/* util.h */

#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024

typedef signed char i8;
typedef unsigned char u8;

#define bool i8
#define true 1
#define false 0

typedef struct {
	float x, y, z;
} Vec3D;

inline Vec3D vec3d_add(Vec3D a, Vec3D b) {
	return (Vec3D){a.x + b.x, a.y + b.y, a.z + b.z};
}

typedef struct {
	u8 r, g, b, a;
} Color;
