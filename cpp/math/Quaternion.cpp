#include "Quaternion.h"
#include "math.h"
Quaternion::Quaternion()
: x(0.0), y(0.0), z(0.0), w(1.0) {
}

Quaternion::Quaternion(
	float _x,
	float _y,
	float _z,
	float _w
)
: x(_x), y(_y), z(_z), w(_w) {
}

bool Quaternion::equals(
	Quaternion *q
) {
	return this->x == q->x && this->y == q->y && this->z == q->z
		&& this->w == q->w;
}

Quaternion* Quaternion::copy(
	Quaternion *q
) {
	this->x = q->x;
	this->y = q->y;
	this->z = q->z;
	this->w = q->w;
	return this;
}


Quaternion* Quaternion::setFromEuler ( float x, float y, float z ) {

		// http://www.mathworks.com/matlabcentral/fileexchange/
		// 	20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors/
		//	content/SpinCalc.m
		float c1 = cos( x / 2 );
		float c2 = cos( y / 2 );
		float c3 = cos( z / 2 );
		float s1 = sin( x / 2 );
		float s2 = sin( y / 2 );
		float s3 = sin( z / 2 );

		this->x = s1 * c2 * c3 + c1 * s2 * s3;
		this->y = c1 * s2 * c3 - s1 * c2 * s3;
		this->z = c1 * c2 * s3 + s1 * s2 * c3;
		this->w = c1 * c2 * c3 - s1 * s2 * s3;

		return this;
	}
