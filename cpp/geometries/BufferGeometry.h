#ifndef __THREE_BUFFER_GEOMETRY__
#define __THREE_BUFFER_GEOMETRY__


#include "../my_std/map.hpp"
#include "../core/BufferAttribute.h"
#include "../math/Sphere.h"
#include "../math/Box3.h"

const int POSITION_ATTRIBUTE = 0;


class BufferGeometry {
public:
	BufferAttribute *index;
	polygon_map<int, BufferAttribute*> attributes;
	Sphere *boundingSphere;

	BufferGeometry();

	BufferAttribute* getIndex();

	BufferGeometry* setIndex(
		BufferAttribute *_index
	);

	BufferGeometry* addAttribute(
		int atrribute_key,
		BufferAttribute *attribute
	);

	BufferAttribute* getAttribute(
		int atrribute_key
	);

	BufferGeometry* computeBoundingSphere();
};

#endif
