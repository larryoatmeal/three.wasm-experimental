#ifndef __THREE_VECTOR3__
#define __THREE_VECTOR3__

#include <math.h>
#include "Matrix4.h"




class Matrix4;

class Vector3 {
public:


    float elements[3];

	Vector3();

	Vector3(
		float _x,
		float _y,
		float _z
	);

	Vector3* set(
		float _x,
		float _y,
		float _z
	);

	Vector3* copy(
		Vector3 *v
	);

	bool equals(
		Vector3 *v
	);

	Vector3* applyMatrix4(
		Matrix4 *m
	);

	Vector3* setFromMatrixPosition(
		Matrix4 *m
	);

	Vector3* multiplyScalar(
		float scalar
	);

	float dot(
		Vector3 *v
	);

	float length();

	float distanceToSquared(
		Vector3* v
	);

	Vector3* addVectors(
		Vector3 *a,
		Vector3 *b
	);
};

#endif
