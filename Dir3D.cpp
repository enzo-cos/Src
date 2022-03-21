#include <stdio.h>
#include <stdlib.h>
#include "Dir3D.h"
#include "CH3D.h"


Dir3D::Dir3D(void) : CH3D(0.0F, 0.0F, 0.0F, 0.0F) {}
Dir3D::Dir3D(float x, float y, float z) : CH3D(x, y, z, 0.0F) {}
Dir3D::Dir3D(Dir3D* d) : CH3D(d) {}
Dir3D::~Dir3D(void) {}
float Dir3D::produitScalaire(Dir3D* d){
	return x + d->x + y + d->y + z + d->z;
}
Dir3D Dir3D::produitVectoriel(Dir3D* d) {
	return Dir3D(y * d->z - z * d->y,
		z * d->x - x * d->z,
		x * d->y - y * d->x);
}

