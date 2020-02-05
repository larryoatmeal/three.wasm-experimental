#include "Matrix4.h"

Matrix4::Matrix4() {
	this->elements[0] = 1.0;
	this->elements[1] = 0.0;
	this->elements[2] = 0.0;
	this->elements[3] = 0.0;
	this->elements[4] = 0.0;
	this->elements[5] = 1.0;
	this->elements[6] = 0.0;
	this->elements[7] = 0.0;
	this->elements[8] = 0.0;
	this->elements[9] = 0.0;
	this->elements[10] = 1.0;
	this->elements[11] = 0.0;
	this->elements[12] = 0.0;
	this->elements[13] = 0.0;
	this->elements[14] = 0.0;
	this->elements[15] = 1.0;
}

Matrix4* Matrix4::copy(
	Matrix4 *m
) {
	this->elements[0] = m->elements[0];
	this->elements[1] = m->elements[1];
	this->elements[2] = m->elements[2];
	this->elements[3] = m->elements[3];
	this->elements[4] = m->elements[4];
	this->elements[5] = m->elements[5];
	this->elements[6] = m->elements[6];
	this->elements[7] = m->elements[7];
	this->elements[8] = m->elements[8];
	this->elements[9] = m->elements[9];
	this->elements[10] = m->elements[10];
	this->elements[11] = m->elements[11];
	this->elements[12] = m->elements[12];
	this->elements[13] = m->elements[13];
	this->elements[14] = m->elements[14];
	this->elements[15] = m->elements[15];
	return this;
}

Matrix4* Matrix4::multiplyMatrices(
	struct Matrix4 *a,
	struct Matrix4 *b
) {
	float a11 = a->elements[0];
	float a12 = a->elements[4];
	float a13 = a->elements[8];
	float a14 = a->elements[12];
	float a21 = a->elements[1];
	float a22 = a->elements[5];
	float a23 = a->elements[9];
	float a24 = a->elements[13];
	float a31 = a->elements[2];
	float a32 = a->elements[6];
	float a33 = a->elements[10];
	float a34 = a->elements[14];
	float a41 = a->elements[3];
	float a42 = a->elements[7];
	float a43 = a->elements[11];
	float a44 = a->elements[15];

	float b11 = b->elements[0];
	float b12 = b->elements[4];
	float b13 = b->elements[8];
	float b14 = b->elements[12];
	float b21 = b->elements[1];
	float b22 = b->elements[5];
	float b23 = b->elements[9];
	float b24 = b->elements[13];
	float b31 = b->elements[2];
	float b32 = b->elements[6];
	float b33 = b->elements[10];
	float b34 = b->elements[14];
	float b41 = b->elements[3];
	float b42 = b->elements[7];
	float b43 = b->elements[11];
	float b44 = b->elements[15];

	this->elements[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
	this->elements[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
	this->elements[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
	this->elements[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

	this->elements[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
	this->elements[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
	this->elements[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
	this->elements[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

	this->elements[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
	this->elements[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
	this->elements[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
	this->elements[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

	this->elements[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
	this->elements[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
	this->elements[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
	this->elements[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

	return this;
}

Matrix4* Matrix4::compose(
	struct Vector3 *position,
	struct Quaternion *quaternion,
	struct Vector3 *scale
) {
	float x = quaternion->x;
	float y = quaternion->y;
	float z = quaternion->z;
	float w = quaternion->w;

	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;

	float xx = x * x2;
	float xy = x * y2;
	float xz = x * z2;

	float yy = y * y2;
	float yz = y * z2;
	float zz = z * z2;

	float wx = w * x2;
	float wy = w * y2;
	float wz = w * z2;

	float sx = scale->elements[0];
	float sy = scale->elements[1];
	float sz = scale->elements[2];

	this->elements[0] = (1.0 - (yy + zz)) * sx;
	this->elements[1] = (xy + wz) * sx;
	this->elements[2] = (xz - wy) * sx;
	this->elements[3] = 0.0;

	this->elements[4] = (xy - wz) * sy;
        this->elements[5] = (1.0 - (xx + zz)) * sy;
        this->elements[6] = (yz + wx) * sy;
        this->elements[7] = 0.0;

        this->elements[8] = (xz + wy) * sz;
        this->elements[9] = (yz - wx) * sz;
        this->elements[10] = (1.0 - (xx + yy)) * sz;
        this->elements[11] = 0.0;

        this->elements[12] = position->elements[0];
        this->elements[13] = position->elements[1];
        this->elements[14] = position->elements[2];
        this->elements[15] = 1.0;

	return this;
}

Matrix4* Matrix4::getInverse(
	Matrix4 *m
) {
	float n11 = m->elements[0];
	float n21 = m->elements[1];
	float n31 = m->elements[2];
	float n41 = m->elements[3];
	float n12 = m->elements[4];
	float n22 = m->elements[5];
	float n32 = m->elements[6];
	float n42 = m->elements[7];
	float n13 = m->elements[8];
	float n23 = m->elements[9];
	float n33 = m->elements[10];
	float n43 = m->elements[11];
	float n14 = m->elements[12];
	float n24 = m->elements[13];
	float n34 = m->elements[14];
	float n44 = m->elements[15];

	float t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
	float t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
	float t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
	float t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

	float det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

	if ( det == 0.0 ) {

		// TODO: Error handling
		return this;

	}

	float detInv = 1.0 / det;

	this->elements[0] = t11 * detInv;
	this->elements[1] = ( n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44 ) * detInv;
	this->elements[2] = ( n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44 ) * detInv;
	this->elements[3] = ( n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43 ) * detInv;

	this->elements[4] = t12 * detInv;
	this->elements[5] = ( n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44 ) * detInv;
	this->elements[6] = ( n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44 ) * detInv;
	this->elements[7] = ( n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43 ) * detInv;

	this->elements[8] = t13 * detInv;
	this->elements[9] = ( n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44 ) * detInv;
	this->elements[10] = ( n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44 ) * detInv;
	this->elements[11] = ( n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43 ) * detInv;

	this->elements[12] = t14 * detInv;
	this->elements[13] = ( n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34 ) * detInv;
	this->elements[14] = ( n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34 ) * detInv;
	this->elements[15] = ( n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33 ) * detInv;

	return this;
}

Matrix4* Matrix4::makePerspective(
	float left,
	float right,
	float top,
	float bottom,
	float near,
	float far
) {
	float x = 2.0 * near / ( right - left );
	float y = 2.0 * near / ( top - bottom );

	float a = ( right + left ) / ( right - left );
	float b = ( top + bottom ) / ( top - bottom );
	float c = - ( far + near ) / ( far - near );
	float d = - 2 * far * near / ( far - near );

	this->elements[0] = x;
	this->elements[4] = 0.0;
	this->elements[8] = a;
	this->elements[12] = 0.0;
	this->elements[1] = 0.0;
	this->elements[5] = y;
	this->elements[9] = b;
	this->elements[13] = 0.0;
	this->elements[2] = 0.0;
	this->elements[6] = 0.0;
	this->elements[10] = c;
	this->elements[14] = d;
	this->elements[3] = 0.0;
	this->elements[7] = 0.0;
	this->elements[11] = -1.0;
	this->elements[15] = 0.0;

	return this;
}

float Matrix4::getMaxScaleOnAxis() {
	float scaleXSq = this->elements[0] * this->elements[0] +
		this->elements[1] * this->elements[1] +
		this->elements[2] * this->elements[2];
	float scaleYSq = this->elements[4] * this->elements[4] +
		this->elements[5] * this->elements[5] +
		this->elements[6] * this->elements[6];
	float scaleZSq = this->elements[8] * this->elements[8] +
		this->elements[9] * this->elements[9] +
		this->elements[10] * this->elements[10];

	float max = scaleXSq >= scaleYSq ? scaleXSq : scaleYSq;
	return sqrt(max >= scaleZSq ? max : scaleZSq);
}
