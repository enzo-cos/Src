#include "CH3D.h"

class CH3D {
	CH3D::CH3D(void) {
		x = y = z = w = 0.0F;
	}
	CH3D::CH3D(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	CH3D::CH3D(CH3D* ch) {
		x = ch->x;
		y = ch->y;
		z = ch->z;
		w = ch->w;
	}
	CH3D::~CH3D(void){}
};