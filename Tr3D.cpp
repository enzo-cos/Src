#include "Tr3D.h"
#include "CH3D.h"
#include "TG3D.h"

Tr3D::Tr3D(void) {
	x = y = z = 0.0;
}

Tr3D::Tr3D(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Tr3D::Tr3D(TG3D* tg) {
	x = y = z = 0.0; //TODO
}

Tr3D::Tr3D(CH3D* ch) {
	x = ch->x;
	y = ch->y;
	z = ch->z;
}

Tr3D::Tr3D(Tr3D* tr) {
	x = tr->x;
	y = tr->y;
	z = tr->z;
}

Tr3D::~Tr3D(void) {}