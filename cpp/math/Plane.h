#ifndef __THREE_PLANE__
#define __THREE_PLANE__

#include "Vector3.h"

class Plane {
public:
	Vector3 normal;
	float constant;

	Plane();

	Plane* setComponents(
		float x,
		float y,
		float z,
		float w
	);

	Plane* normalize();

	float distanceToPoint(
		Vector3 *point
	);
};

#endif
