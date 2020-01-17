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
There are some important flags/environment variables to pay attention to.

* Disable all stdlibs
```
export EMCC_ONLY_FORCED_STDLIBS=1
```
* Disable unneeded features
```
-fno-exceptions -fno-rtti -s ERROR_ON_UNDEFINED_SYMBOLS=0
```

## TODO

* Currently all gl calls are not implemented.
* Using custom dumb malloc that can only allocate and never frees.
* Using custom vector and map classes that are very naive. The map class basically just iterates through the entire list to find an element lol.

