#ifndef __THREE_MATRIX4__
#define __THREE_MATRIX4__

#include <math.h>
#include "Vector3.h"
#include "Quaternion.h"

class Vector3;

class Matrix4 {
public:
	float elements[16];

	Matrix4();

	Matrix4* copy(
		Matrix4 *m
	);

	Matrix4* multiplyMatrices(
		Matrix4 *a,
		Matrix4 *b
	);

	Matrix4* compose(
		Vector3 *position,
		Quaternion *quaternion,
		Vector3 *scale
	);

	Matrix4* getInverse(
		Matrix4 *m
	);

	Matrix4* makePerspective(
		float left,
		float right,
		float top,
		float bottom,
		float near,
		float far
	);

	float getMaxScaleOnAxis();
};

#endif