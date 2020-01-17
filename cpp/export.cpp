#include "./math/Vector3.h"
#include "./math/Matrix4.h"
#include "./core/BufferAttribute.h"
#include "./core/Object3D.h"
#include "./geometries/BufferGeometry.h"
#include "./objects/Mesh.h"
#include "./materials/Materials.h"
#include "./scenes/Scene.h"
#include "./cameras/PerspectiveCamera.h"
#include "./renderer/WebGLRenderer.h"
#include "./my_std/vec.hpp"

// TODO: Replace with EMSCRIPTEN_BINDINGS?

// Overloading Global new operator
void* operator new(size_t sz)
{
	void* m = malloc(sz);
	return m;
}
// Overloading Global delete operator
void operator delete(void* m)
{
	free(m);
}

extern "C" {
	//C->JS
	int sizeOfVector3() {
		return sizeof(Vector3);
	}

	int sizeOfMatrix4() {
		return sizeof(Matrix4);
	}

	int sizeOfBufferAttribute() {
		return sizeof(BufferAttribute);
	}

	int sizeOfBufferGeometry() {
		return sizeof(BufferGeometry);
	}

	int sizeOfObject3D() {
		return sizeof(Object3D);
	}

	int sizeOfMesh() {
		return sizeof(Mesh);
	}

	int sizeOfMeshBasicMaterial() {
		return sizeof(MeshBasicMaterial);
	}

	int sizeOfPerspectiveCamera() {
		return sizeof(PerspectiveCamera);
	}

	int sizeOfWebGLRenderer() {
		return sizeof(WebGLRenderer);
	}

	int sizeOfScene() {
		return sizeof(Scene);
	}

	Vector3* Vector3_init(
		double x,
		double y,
		double z
	) {
		return new Vector3(x, y, z);
	}

	Matrix4* Matrix4_multiplyMatrices(
		Matrix4* self,
		Matrix4* a,
		Matrix4* b
	) {
		return self->multiplyMatrices(a, b);
	}

	BufferAttribute* BufferAttribute_init(
		void *array,
		BufferAttribute::type dataType,
		int dataLength,
		int itemSize
	) {
		return new BufferAttribute(array, dataType,
			dataLength, itemSize);
	}

	BufferGeometry* BufferGeometry_init(
	) {
		return new BufferGeometry();
	}

	BufferGeometry* BufferGeometry_addAttribute(
		BufferGeometry *geometry,
		int attribute_key,
		BufferAttribute *attribute
	) {
		geometry->addAttribute(attribute_key, attribute);
		return geometry;
	}

	BufferGeometry* BufferGeometry_setIndex(
		BufferGeometry *geometry,
		BufferAttribute *attribute
	) {
		geometry->setIndex(attribute);
		return geometry;
	}

		Object3D* Object3D_init(
	) {
		return new Object3D();
	}

	Object3D* Object3D_add(
		Object3D *object,
		Object3D *child
	) {
		return object->add(child);
	}

	void* Object3D_getPositionPointer(
		Object3D* object
	) {
		return &object->position;
	}

	Object3D* Object3D_updateMatrixWorld(
		Object3D *object,
		bool force
	) {
		object->updateMatrixWorld(force);
		return object;
	}

	Mesh* Mesh_init(
		BufferGeometry *geometry,
		Material *material
	) {
		return new Mesh(geometry, material);
	}

	MeshBasicMaterial* MeshBasicMaterial_init(
		float r, float g, float b
	) {
		return new MeshBasicMaterial(Vector3(r, g, b));
	}

	Scene* Scene_init(
	) {
		return new Scene();
	}

	PerspectiveCamera* PerspectiveCamera_init(
		double fov,
		double aspect,
		double near,
		double far
	) {
		return new PerspectiveCamera(fov, aspect, near, far);
	}

	WebGLRenderer* WebGLRenderer_init(
		bool antialias
	) {
		return new WebGLRenderer(antialias);
	}

	WebGLRenderer* WebGLRenderer_setSize(
		WebGLRenderer *renderer,
		int width,
		int height
	) {
		return renderer->setSize(width, height);
	}

	WebGLRenderer* WebGLRenderer_clearColor(
		WebGLRenderer *renderer,
		double r,
		double g,
		double b,
		double a
	) {
		return renderer->clearColor(r, g, b, a);
	}

	WebGLRenderer* WebGLRenderer_render(
		WebGLRenderer *renderer,
		Scene *scene,
		Camera *camera
	) {
		return renderer->render(scene, camera);
	}

	void initGl(
	) {
		//printf( "Context creation for %s\n", id );

		EmscriptenWebGLContextAttributes attrs;
		attrs.explicitSwapControl = 0;
		attrs.depth = 1;
		attrs.stencil = 1;
		attrs.antialias = 1;
		attrs.majorVersion = 1;
		attrs.minorVersion = 0;

		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context(&attrs);

		if(context <= 0) {
			//printf("Context creation Error\n");
			return;
		}

		emscripten_webgl_make_context_current(context);
	}

	void runTest(
		int loop
	) {
		for(int i = 0; i < loop; i++) {
			glClearColor(0.0, 0.0, 0.0, 0.0);
		}
	}

	extern unsigned char __heap_base;
	unsigned int bump_pointer = (unsigned int) &__heap_base;

	//need to keep alignment at 8bytes
	void *malloc(size_t size){
		unsigned int r = bump_pointer;
		if(size % 8 != 0){
			size = (size / 8 + 1) * 8;
		}
		bump_pointer = bump_pointer + size;
  	return (void *)r;
	};
	void free(void *ptr){

	};








	// void memcpy(void* dst, const void* src, int len) {
	//   char* s = (char*)src;
	//   char* d = (char*)dst;
	//
	//   for (int i = 0; i < len; ++i) {
	//     d[i] = s[i];
	//   }
	// }
	// void memcpy(void *dst, const void *src, int len);
	// void memset(void *pointer, uchar value, uint size);


}
