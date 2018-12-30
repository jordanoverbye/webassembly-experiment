# WebAssembly Experiment

My first time using WebAssembly, C and [Emscripten](http://kripken.github.io/emscripten-site/index.html).

![](https://i.imgur.com/I5sGKZC.png)

## Running locally

1. Install [Emscripten](http://kripken.github.io/emscripten-site/index.html)
2. Clone this repository
3. `yarn` to install dependencies
4. `yarn start` to start the server

To compile C to WebAssembly, run

```
emcc lib/app.c -s WASM=1 -s EXPORTED_FUNCTIONS='["_main", "_getCircles"]' -o public/app.js
```
