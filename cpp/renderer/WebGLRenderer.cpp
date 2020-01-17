﻿#include <stdlib.h>
// #include <algorithm>
#include "WebGLRenderer.h"
bool validEmscriptenResult(
	EMSCRIPTEN_RESULT result
) {

	// if(result == EMSCRIPTEN_RESULT_SUCCESS)
	// 	return 1;
	//
	// if(result == EMSCRIPTEN_RESULT_DEFERRED)
	// 	//printf("EMSCRIPTEN_RESULT_DEFERRED error\n");
	// else if(result == EMSCRIPTEN_RESULT_NOT_SUPPORTED)
	// 	//printf("EMSCRIPTEN_RESULT_NOT_SUPPORTED error\n");
	// else if(result == EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED)
	// 	//printf("EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED error\n");
	// else if(result == EMSCRIPTEN_RESULT_INVALID_TARGET)
	// 	//printf("EMSCRIPTEN_RESULT_INVALID_TARGETT error\n");
	// else if(result == EMSCRIPTEN_RESULT_UNKNOWN_TARGET)
	// 	//printf("EMSCRIPTEN_RESULT_UNKNOWN_TARGET error\n");
	// else if(result == EMSCRIPTEN_RESULT_INVALID_PARAM)
	// 	//printf("EMSCRIPTEN_RESULT_INVALID_PARAM error\n");
	// else if(result == EMSCRIPTEN_RESULT_FAILED)
	// 	//printf("EMSCRIPTEN_RESULT_FAILED error\n");
	// else if(result == EMSCRIPTEN_RESULT_NO_DATA)
	// 	//printf("EMSCRIPTEN_RESULT_NO_DATA error\n");
	// else
	// 	//printf("Unknown error\n");

	return 1;
}

GLuint loadShader(
	GLenum type,
	const char *code
) {
	GLuint shader = glCreateShader(type);

	if(shader == 0) {
		return 0;
	}

	glShaderSource(shader, 1, &code, 0);
	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(compiled == 0) {
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1) {
			char *infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, 0, infoLog);
			//printf("Error compiling code\n%s\n", infoLog);
			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint WebGLRenderer::compileShader() {
	GLbyte vertexShaderCode[] =
		"attribute vec3 position;\n"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 modelViewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat3 normalMatrix;\n"
		"uniform vec3 cameraPosition;\n"
		"void main()\n"
		"{\n"
		"	vec4 mvPosition = modelViewMatrix * vec4(position, 1.0);"
		"	gl_Position = projectionMatrix * mvPosition;\n"
		"}\n";

	GLbyte fragmentShaderCode[] =
		"precision mediump float;\n"
		"uniform vec3 color;\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = vec4(color, 1.0);\n"
		"}\n";

	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, (char *)vertexShaderCode);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, (char *)fragmentShaderCode);
	GLuint program = glCreateProgram();

	if(program == 0)
		return 0;

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "position");
	glLinkProgram(program);

	this->uniformLocationMap.put(UNIFORM_modelViewMatrix, glGetUniformLocation(program, "modelViewMatrix"));
	this->uniformLocationMap.put(UNIFORM_projectionMatrix, glGetUniformLocation(program, "projectionMatrix"));
	this->uniformLocationMap.put(UNIFORM_color, glGetUniformLocation(program, "color"));

	GLint linked;

	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if(linked == 0) {

		GLint infoLen = 0;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1) {
			char *infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetProgramInfoLog(program, infoLen, 0, infoLog);
			//printf("Error linking program:\n%s\n", infoLog);
			free(infoLog);
		}

		glDeleteProgram(program);
		return 0;
	}

	return program;
}

WebGLRenderer::WebGLRenderer(
	bool antialias
): currentGeometry(NULL), initialized(false),
	program(0), currentProgram(0), currentCamera(NULL) {
	//printf( "Context creation for %s\n", id );

	EmscriptenWebGLContextAttributes attrs;
	attrs.explicitSwapControl = 0;
	attrs.depth = 1;
	attrs.stencil = 1;
	attrs.antialias = antialias ? 1 : 0;
	attrs.majorVersion = 1;
	attrs.minorVersion = 0;
	this->context = emscripten_webgl_create_context(&attrs);

	if(this->context <= 0) {
		//printf("Context creation Error\n");
		console_error(0);
		validEmscriptenResult((EMSCRIPTEN_RESULT)this->context);
		return;
	}

	// if (! this->activateContext()) {
	// 	return;
	// }

	this->attributes = new WebGLAttributes();
	this->geometries = new WebGLGeometries(this->attributes);
}

bool WebGLRenderer::activateContext() {
	return validEmscriptenResult(
		emscripten_webgl_make_context_current(this->context));
}

WebGLRenderer* WebGLRenderer::setSize(
	int _width,
	int _height
) {
	this->width = _width;
	this->height = _height;
	return this;
}

WebGLRenderer* WebGLRenderer::viewport(
	int _width,
	int _height
) {
	glViewport(0.0, 0.0, _width, _height);
	return this;
}

WebGLRenderer* WebGLRenderer::clearColor(
	double r,
	double g,
	double b,
	double a
) {
	glClearColor(r, g, b, a);
	return this;
}

WebGLRenderer* WebGLRenderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
	return this;
}

polygon_vec<Object3D*> stack;
void WebGLRenderer::projectObject(
	Object3D *object,
	Camera *camera
) {

	int size = object->children.size();
	stack.push_back(object);
	while (!stack.empty())
  {
    Object3D* node = stack.back();

		if(node->type() == MeshType && this->frustum.intersectsObject(node)) {
			this->tmpVector3.setFromMatrixPosition(&node->matrixWorld)
				->applyMatrix4(&this->projScreenMatrix);
			struct RenderItem entry;
			entry.object = node;
			entry.z = this->tmpVector3.z;
			this->currentRenderList.push_back(entry);
			this->geometries->update(((Mesh*)node)->geometry);
		}

    stack.pop_back();
		for(int i = 0; i < node->children.size(); i++) {
				stack.push_back(node->children[i]);
		}
  }
}

void WebGLRenderer::renderObjects(
	polygon_vec<RenderItem> *renderList,
	Scene *scene,
	Camera *camera
) {
	int size = renderList->size();
	for(int i = 0, il = size; i < il; ++i) {
		this->renderObject((*renderList)[i].object, camera);
	}
}

void WebGLRenderer::renderObject(
	Object3D *object,
	Camera *camera
) {
	object->modelViewMatrix.multiplyMatrices(&camera->matrixWorldInverse,
		&object->matrixWorld);
	object->normalMatrix.getNormalMatrix(&object->modelViewMatrix);

	Mesh *mesh = (Mesh*)object;
	BufferGeometry *geometry = mesh->geometry;
	Material *material = mesh->material;

	bool refreshProgram = false;

	if(this->program != this->currentProgram) {
		glUseProgram(this->program);
		this->currentProgram = this->program;
		refreshProgram = true;
	}

	if(refreshProgram || camera != this->currentCamera) {
		GLfloat projectionMatrixElements[16];
		for(int i = 0; i < 16; ++i) {
			projectionMatrixElements[i] = camera->projectionMatrix.elements[i];
		}
		glUniformMatrix4fv(this->uniformLocationMap.get(UNIFORM_projectionMatrix), 1, GL_FALSE, projectionMatrixElements);
		this->currentCamera = camera;
	}

	if(this->currentGeometry != geometry) {
		auto geometry_attribute_elements = mesh->geometry->attributes.elements;
		for(int i = 0; i < geometry_attribute_elements.size(); i++){
			glBindBuffer(GL_ARRAY_BUFFER, this->attributes->get(geometry_attribute_elements[i]).buffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
		}
		// for(std::map<std::string, BufferAttribute*>::iterator it =
		// 	mesh->geometry->attributes.begin();
		// 	it != mesh->geometry->attributes.end(); ++it) {
		// 	glBindBuffer(GL_ARRAY_BUFFER, this->attributes->get(it->second).buffer);
		// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// 	glEnableVertexAttribArray(0);
		// }
		this->currentGeometry = geometry;
	}

	Vector3 *color = &((MeshBasicMaterial*)material)->color;

	int drawStart = 0;
	int drawCount = 0;

	if(mesh->geometry->index != NULL) {
		this->renderer.setIndex(mesh->geometry->index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
			this->attributes->get(geometry->index).buffer);
		drawCount = mesh->geometry->index->count;
	} else {
		drawCount = mesh->geometry->getAttribute(POSITION_ATTRIBUTE)->count;
	}

	GLfloat modelViewMatrixElements[16];
	for(int i = 0; i < 16; ++i) {
		modelViewMatrixElements[i] = (GLfloat)object->modelViewMatrix.elements[i];
	}
	glUniformMatrix4fv(this->uniformLocationMap.get(UNIFORM_modelViewMatrix), 1, GL_FALSE, modelViewMatrixElements);

	GLfloat colorElements[3];
	colorElements[0] = color->x;
	colorElements[1] = color->y;
	colorElements[2] = color->z;
	glUniform3fv(this->uniformLocationMap.get(UNIFORM_color), 1, colorElements);

	this->renderer.render(drawStart, drawCount);
}

struct painterSort {
	inline bool operator() (RenderItem entry1, RenderItem entry2) {
		return entry1.z < entry2.z;
	}
};

WebGLRenderer* WebGLRenderer::render(
	Scene *scene,
	Camera *camera
) {
	if(! this->initialized) {
		this->program = this->compileShader();
		this->initialized = true;
		this->activateContext();
		this->viewport(this->width, this->height);
		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);
	}

	scene->updateMatrixWorld(false);
	if(camera->parent == NULL) camera->updateMatrixWorld(false);

	this->projScreenMatrix.multiplyMatrices(
		&camera->projectionMatrix, &camera->matrixWorldInverse);
	this->frustum.setFromMatrix(&this->projScreenMatrix);

	this->projectObject(scene, camera);

	//use custom sorting algorithm
	

	// std::sort(this->currentRenderList.begin(), this->currentRenderList.end(),
	// 	painterSort());

	this->clear();
	this->renderObjects(&this->currentRenderList, scene, camera);
	//
	this->currentRenderList.clear();
	this->currentCamera = NULL;

	return this;
}
