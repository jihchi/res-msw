# bs-msw [![Travis (.org)](https://img.shields.io/travis/jihchi/bs-msw)](https://travis-ci.org/jihchi/bs-msw) [![npm](https://img.shields.io/npm/v/bs-msw)](https://www.npmjs.com/package/bs-msw) [![Coveralls github](https://img.shields.io/coveralls/github/jihchi/bs-msw)](https://coveralls.io/github/jihchi/bs-msw) ![npm](https://img.shields.io/npm/dm/bs-msw) ![NPM](https://img.shields.io/npm/l/bs-msw)

> [msw](https://github.com/mswjs/msw) bindings for [BuckleScript](https://github.com/bloomberg/bucklescript) in [Reason](https://github.com/facebook/reason)

# Installation

**Prerequisite**: you have installed [msw](https://github.com/mswjs/msw).

```sh
npm install --save-dev bs-msw

# or ...

yarn add -D bs-msw
```

# Usage

Add to `bsconfig.json`

```diff
  ...
  "bs-dependencies": [
+   "bs-msw"
  ]
  ...
```

## API

For more example, please refer to [`MSW_test.re`](/__tests__/MSW_test.re)

`MSW` is the root namespace module.

# Testing the library

```
npm test
```

this will compile and execute tests with `bs-jest`

# Contributions

Don't hesitate to open a PR with a new binding - while bumping up the amount of covered bindings in the README.
There are tests, use them and write the most simple test you can think of to make sure that the bindings work correctly.
