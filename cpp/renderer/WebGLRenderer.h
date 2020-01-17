#ifndef __THREE_WEBGLRENDERER_H__
#define __THREE_WEBGLRENDERER_H__

#include <GLES2/gl2.h>
#include <vector>
#include "../my_std/map.hpp"
#include "../my_std/vec.hpp"
#include "../include/html5.h"
#include "../math/Matrix4.h"
#include "../math/Frustum.h"
#include "../core/Object3D.h"
#include "../materials/Materials.h"
#include "../objects/Mesh.h"
#include "../scenes/Scene.h"
#include "../cameras/Camera.h"
#include "./webgl/WebGLAttributes.h"
#include "./webgl/WebGLGeometries.h"
#include "./webgl/WebGLIndexedBufferRenderer.h"
#include "../js_external.h"


const int UNIFORM_modelViewMatrix = 0;
const int UNIFORM_projectionMatrix = 1;
const int UNIFORM_color = 2;

struct RenderItem {
	Object3D* object;
	double z;
};

class WebGLRenderer {
private:
	Matrix4 projScreenMatrix;
	polygon_vec<RenderItem> currentRenderList;
	WebGLAttributes *attributes;
	WebGLGeometries *geometries;
	WebGLIndexedBufferRenderer renderer;
	BufferGeometry *currentGeometry;
	GLuint program;
	GLuint currentProgram;
	Camera *currentCamera;
	Frustum frustum;
	Vector3 tmpVector3;
	polygon_map<int, int> uniformLocationMap;

	bool activateContext();

	GLuint compileShader();

	void projectObject(
		Object3D *object,
		Camera *camera
	);

	void renderObjects(
		polygon_vec<RenderItem> *renderList,
		Scene *scene,
		Camera *camera
	);

	void renderObject(
		Object3D *object,
		Camera *camera
	);

public:
	int width;
	int height;
	bool initialized;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

	WebGLRenderer(
		bool antialias
	);

	WebGLRenderer* setSize(
		int width,
		int height
	);

	WebGLRenderer* viewport(
		int width,
		int height
	);

	WebGLRenderer* clearColor(
		double r,
		double g,
		double b,
		double a
	);

	WebGLRenderer* clear();

	WebGLRenderer* render(
		Scene *scene,
		Camera *camera
	);
};

#endif
