#include "Box3.h"

Box3::Box3() {}

bool Box3::isEmpty() {
	return (this->max.elements[0] < this->min.elements[0]) ||
		(this->max.elements[1] < this->min.elements[1]) ||
		(this->max.elements[2] < this->min.elements[2]);
}

Box3* Box3::setFromBufferAttribute(
	BufferAttribute *attribute
) {
	float largeValue = 1000000.0; // Fix me
	float minX = largeValue;
	float minY = largeValue;
	float minZ = largeValue;

	float maxX = -largeValue;
	float maxY = -largeValue;
	float maxZ = -largeValue;

	for(int i = 0, il = attribute->count; i < il; ++i) {
		float x = (float)attribute->getXAsFloat(i);
		float y = (float)attribute->getYAsFloat(i);
		float z = (float)attribute->getZAsFloat(i);

		if(x < minX) minX = x;
		if(y < minY) minY = y;
		if(z < minZ) minZ = z;

		if(x > maxX) maxX = x;
		if(y > maxY) maxY = y;
		if(z > maxZ) maxZ = z;
	}

	this->min.set(minX, minY, minZ);
	this->max.set(maxX, maxY, maxZ);

	return this;
}

Vector3* Box3::getCenter(
	Vector3* target
) {
	return this->isEmpty()
		? target->set(0.0, 0.0, 0.0)
		: target->addVectors(&this->min, &this->max)->multiplyScalar(0.5);
}
