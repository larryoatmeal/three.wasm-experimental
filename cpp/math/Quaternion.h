#ifndef __THREE_QUATERNION__
#define __THREE_QUATERNION__

class Quaternion {
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);

	bool equals(
		Quaternion *q
	);

	Quaternion* copy(
		Quaternion *q
	);

	Quaternion* setFromEuler(
		float x, float y, float z
	);
};

#endif
