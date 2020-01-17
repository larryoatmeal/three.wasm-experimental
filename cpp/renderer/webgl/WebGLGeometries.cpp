#include "WebGLGeometries.h"
#include "../../js_external.h"
WebGLGeometries::WebGLGeometries(
	WebGLAttributes *_attributes
): attributes(_attributes) {}

void WebGLGeometries::update(
	BufferGeometry *geometry
) {
	if(geometry->index != NULL) {
		this->attributes->update(geometry->index, GL_ELEMENT_ARRAY_BUFFER);
	}

	polygon_vec<BufferAttribute*> geometry_attribute_elements = geometry->attributes.elements;
	for(unsigned int i = 0; i < geometry_attribute_elements.size(); i++){
		this->attributes->update(geometry_attribute_elements[i], GL_ARRAY_BUFFER);
	}
	//
	// for(std::map<std::string, BufferAttribute*>::iterator it =
	// 	geometry->attributes.begin();
	// 	it != geometry->attributes.end(); ++it) {
	// 	this->attributes->update(it->second, GL_ARRAY_BUFFER);
	// }
}
