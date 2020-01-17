# three.wasm-experimental
Experimental Three.js WASM (WIP)

## Overview

This is a standalone WASM version that has no dependencies on emscripten JS glue code nor on the standard library. 

# TODO

Currently all gl calls are not implemented.
Using custom dumb malloc that can only allocate and never frees.
Using custom vector and map classes that are very naive. The map class basically just iterates through the entire list to find an element lol.

https://raw.githack.com/takahirox/three.wasm-experimental/master/index.html
