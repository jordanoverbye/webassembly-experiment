const express = require('express');
const app = express();
const endsWith = require('lodash/endsWith');

app.use(
  express.static('public', {
    setHeaders: (res, path, stat) => {
      if (endsWith(path, '.wasm')) {
        res.set('Content-Type', 'application/wasm');
      }
    },
  })
);

const port = 1234;

app.listen(port, () =>
  console.log(`Started server at http://localhost:${port}`)
);
