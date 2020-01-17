# three.wasm-experimental
Experimental Three.js WASM (WIP)

## Overview

This is a standalone WASM version that has no dependencies on emscripten JS glue code nor on the standard library. 

## Build
```
./build.sh 
```
* Must have emcc installed (v1.39.5)

## EMCC flags
There are some important flags/environment variables to pay attention to, see `build.sh`

* Disable all stdlibs
```
export EMCC_ONLY_FORCED_STDLIBS=1
```
* Disable unneeded features
```
-fno-exceptions -fno-rtti -s ERROR_ON_UNDEFINED_SYMBOLS=0
```

## JS - C++ interop
To call C++ from JS, add to the extern block in `export.cpp` and make sure to add the C++ function to `-s EXPORTED_FUNCTIONS` in `build.sh`
```
extern "C" {
  void* my_c_function(int arg1, int arg2)
}
```
Then in JS, simply call
```
WASM.my_c_function(1, 2)
```

To call JS from C++, which is necessary to say expose `console.log` or any of the WebGL calls, add to the extern block in `js-external.h`. Make sure to use `extern` keyword foro the function itself and that there is no method body.
```
extern "C" {
  extern void* my_js_function(int arg1, int arg2);
}
```
Then in JS, to register the function
```
methods["my_js_function"] = my_js_callback;
```
`methods` is just an object that is passed to `WebAssembly.instantiate()`.

Note all return values and args are basically just numbers/pointers




## TODO

* Currently all gl calls are not implemented.
* Using custom dumb malloc that can only allocate and never frees.
* Using custom vector and map classes that are very naive. The map class basically just iterates through the entire list to find an element lol.
* simple helper to pass arrays/strings

