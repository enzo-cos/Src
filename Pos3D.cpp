#include "CH3D.h"
#include "POS3D.h"


	Pos3D::Pos3D(float x, float y, float z) :CH3D(x, y, z, 1.0F){}

	Pos3D::Pos3D(void) :Pos3D(0.0F, 0.0F, 0.0F){}

	Pos3D::Pos3D(Pos3D *p):CH3D(p){}

	Pos3D::~Pos3D(void){}



