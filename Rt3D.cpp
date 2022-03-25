#include "Rt3D.h"

Rt3D::Rt3D(void) {
	x = y = z = w = 0.0F;
}
Rt3D::Rt3D(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}
Rt3D::Rt3D(Rt3D* rt) {
	x = rt->x;
	y = rt->y;
	z = rt->z;
	w = rt->w;
}
Rt3D::~Rt3D(void) {}

