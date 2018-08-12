# Clipem - Node.js Clipboard Manager

[![License](https://img.shields.io/npm/l/node-clip.svg)](LICENSE)
[![Version](https://img.shields.io/npm/v/node-clip.svg)](https://www.npmjs.com/package/clipem)
[![Downloads](https://img.shields.io/npm/dt/node-clip.svg)](https://www.npmjs.com/package/clipem)

Native API for NodeJS allowing system clipboard operations (built in C++, node-addon-api)

## Development - Alpha phase

This is an early development version. It is released but could suffer from some bugs and is Windows only (future systems are coming).

## Requirements

This module require atleast `NodeJS 8`

Note that you will have a warning about N-API in version < 10, you can disable it by adding the `--no-warnings` flag to `node`

## Installation

```
npm i --save clipit
```

## Usage

```
var clipit = require("clipit")
```


```
// Copying


clipit.copy('Hello, this is a native copy !', () => {
	// Do something when it has been copied
})
// Synchronous way
clipit.copySync('Hello, this is a native copy !')
```

```
// Pasting

clipit.paste((err, res) => {
	// The pasted text is in the `res` parameter
	console.log(res)
})
// Synchronous way
let pasted = clipit.pasteSync()
```

## Support

This package supports the following systems :

 * Windows native clipboard 

Darwin OS X and Linux native clipboards are in progress