#/bin/bash
export EMCC_ONLY_FORCED_STDLIBS=1
emcc \
	-Os\
	-fno-exceptions\
	-fno-rtti\
	-o three-wasm.wasm\
	./cpp/*.cpp ./cpp/*/*.cpp ./cpp/*/*/*.cpp \
	-s ALLOW_MEMORY_GROWTH=0\
	-s TOTAL_MEMORY=100MB\
	-s ERROR_ON_UNDEFINED_SYMBOLS=0\
	-s ENVIRONMENT=web\
	-s EXIT_RUNTIME=0\
	-s EXPORTED_FUNCTIONS="[\
	'_sizeOfVector3',\
	'_sizeOfMatrix4',\
	'_sizeOfBufferAttribute',\
	'_sizeOfBufferGeometry',\
	'_sizeOfObject3D',\
	'_sizeOfMesh',\
	'_sizeOfMeshBasicMaterial',\
	'_sizeOfScene',\
	'_sizeOfPerspectiveCamera',\
	'_sizeOfWebGLRenderer',\
	'_Vector3_init',\
	'_Matrix4_multiplyMatrices',\
	'_BufferAttribute_init',\
	'_BufferGeometry_init',\
	'_BufferGeometry_setIndex',\
	'_BufferGeometry_addAttribute',\
	'_Object3D_init',\
	'_Object3D_add',\
	'_Object3D_getPositionPointer',\
	'_Object3D_updateMatrixWorld',\
	'_Mesh_init',\
	'_MeshBasicMaterial_init',\
	'_Scene_init',\
	'_PerspectiveCamera_init',\
	'_WebGLRenderer_init',\
	'_WebGLRenderer_setSize',\
	'_WebGLRenderer_clearColor',\
	'_WebGLRenderer_render',\
	'_initGl',\
	'_runTest']"\
