﻿#include "BufferGeometry.h"

BufferGeometry::BufferGeometry()
: index(NULL), boundingSphere(NULL) {}

BufferAttribute* BufferGeometry::getIndex() {
	return this->index;
}

BufferGeometry* BufferGeometry::setIndex(
	BufferAttribute *_index
) {
	this->index = _index;
	return this;
}

BufferGeometry* BufferGeometry::addAttribute(
	int attribute_key,
	BufferAttribute *attribute
) {
	this->attributes.put(attribute_key, attribute);
	return this;
}

BufferAttribute* BufferGeometry::getAttribute(
	int attribute_key
) {
	return this->attributes.get(attribute_key);
}

BufferGeometry* BufferGeometry::computeBoundingSphere() {
	Box3 box;
	Vector3 vector;

	if (this->boundingSphere == NULL) {
		this->boundingSphere = new Sphere();
	}

	BufferAttribute *position = attributes.get(POSITION_ATTRIBUTE);

	box.setFromBufferAttribute(position);
	box.getCenter(&this->boundingSphere->center);

	double maxRadiusSq = 0.0;

	for(int i = 0, il = position->count; i < il; ++i) {
		vector.x = (double)position->getXAsFloat(i);
		vector.y = (double)position->getYAsFloat(i);
		vector.z = (double)position->getZAsFloat(i);
		double distanceSq = this->boundingSphere->center.distanceToSquared(&vector);
		maxRadiusSq = maxRadiusSq >= distanceSq ? maxRadiusSq : distanceSq;
	}

	this->boundingSphere->radius = sqrt(maxRadiusSq);
	return this;
}
