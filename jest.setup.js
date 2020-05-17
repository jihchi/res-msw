fetch = require('node-fetch');

Object.defineProperty(navigator, 'serviceWorker', {
  writable: false,
  value: {
    addEventListener: () => null,
  },
})
