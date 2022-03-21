#include "TG3D.h"

TG3D::TG3D(void) {
	for (int l = 0; l < 4; l++) {
		for (int c = 0; c < 4; c++) {
			m[l][c] = (l == c) ? 1.0F : 0.0F;
		}
	}
}

TG3D::TG3D(float *v){
	int i = 0;
	for (int l = 0; l < 4; l++) {
		for (int c = 0; c < 4; c++) {
			m[l][c] = v[i];
			i++;
		}
	}
}

TG3D::TG3D(TG3D *tg) {
	int i = 0;
	for (int l = 0; l < 4; l++) {
		for (int c = 0; c < 4; c++) {
			m[l][c] = tg->m[l][c];
		}
	}
}

TG3D::~TG3D(void){}