#include "Vector3.h"

Vector3::Vector3()
 {
}

Vector3::Vector3(
	float _x,
	float _y,
	float _z
)
{
    this->elements[0] = _x;
    this->elements[1] = _y;
    this->elements[2] = _z;
}

Vector3* Vector3::set(
	float _x,
	float _y,
	float _z
) {
	this->elements[0] = _x;
	this->elements[1] = _y;
	this->elements[2] = _z;
	return this;
}

Vector3* Vector3::copy(
	Vector3 *v
) {
	this->elements[0] = v->elements[0];
	this->elements[1] = v->elements[1];
	this->elements[2] = v->elements[2];
	return this;
}

bool Vector3::equals(
	Vector3 *v
) {
	return this->elements[0] == v->elements[0] && this->elements[1] == v->elements[1] && this->elements[2] == v->elements[2];
}

Vector3* Vector3::applyMatrix4(
	Matrix4 *m
) {
	float x = this->elements[0];
	float y = this->elements[1];
	float z = this->elements[2];
	float w = 1.0 / (m->elements[3] * x + m->elements[7] * y + m->elements[11] * z + m->elements[15]);
	this->elements[0] = (m->elements[0] * x + m->elements[4] * y + m->elements[8] * z + m->elements[12]) * w;
	this->elements[1] = (m->elements[1] * x + m->elements[5] * y + m->elements[9] * z + m->elements[13]) * w;
	this->elements[2] = (m->elements[2] * x + m->elements[6] * y + m->elements[10] * z + m->elements[14]) * w;
	return this;
}

Vector3* Vector3::setFromMatrixPosition(
	Matrix4 *m
) {
	this->elements[0] = m->elements[12];
	this->elements[1] = m->elements[13];
	this->elements[2] = m->elements[14];
	return this;
}

Vector3* Vector3::multiplyScalar(
	float scalar
) {
	this->elements[0] *= scalar;
	this->elements[1] *= scalar;
	this->elements[2] *= scalar;
	return this;
}

float Vector3::dot(
	Vector3 *v
) {
	return this->elements[0] * v->elements[0] + this->elements[1] * v->elements[1] + this->elements[2] * v->elements[2];
}

float Vector3::length() {
	return sqrt(this->elements[0] * this->elements[0] + this->elements[1] * this->elements[1] + this->elements[2] * this->elements[2]);
}

float Vector3::distanceToSquared(
	Vector3* v
) {
	float dx = this->elements[0] - v->elements[0];
	float dy = this->elements[1] - v->elements[1];
	float dz = this->elements[2] - v->elements[2];
	return dx * dx + dy * dy + dz * dz;
}

Vector3* Vector3::addVectors(
	Vector3 *a,
	Vector3 *b
) {
	this->elements[0] = a->elements[0] + b->elements[0];
	this->elements[1] = a->elements[1] + b->elements[1];
	this->elements[2] = a->elements[2] + b->elements[2];
	return this;
}
