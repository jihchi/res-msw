# res-msw

[![Travis (.org)](https://img.shields.io/travis/jihchi/res-msw)](https://travis-ci.org/jihchi/res-msw) [![npm](https://img.shields.io/npm/v/res-msw)](https://www.npmjs.com/package/res-msw) [![Coveralls github](https://img.shields.io/coveralls/github/jihchi/res-msw)](https://coveralls.io/github/jihchi/res-msw) ![npm](https://img.shields.io/npm/dm/res-msw) ![NPM](https://img.shields.io/npm/l/res-msw)

> [msw](https://github.com/mswjs/msw) bindings for [BuckleScript](https://github.com/bloomberg/bucklescript) in [Reason](https://github.com/facebook/reason)

- [Installation](#installation)
- [Usage](#usage)
  - [API](#api)
    - [`Node` module](#node-module)
    - [`ServiceWorker` module](#serviceworker-module)
    - [`Rest` module](#rest-module)
    - [`GraphQL` module](#graphql-module)
    - [Example of Rest](#example-of-rest)
    - [Example of GraphQL](#example-of-graphql)
- [Testing the library](#testing-the-library)
- [Contributions](#contributions)

# Installation

**Prerequisite**: you have installed [msw](https://github.com/mswjs/msw).

```sh
npm install --save-dev res-msw

# or ...

yarn add -D res-msw
```

# Usage

Add to `bsconfig.json`

```diff
  ...
  "bs-dependencies": [
+   "res-msw"
  ]
  ...
```

## API

`MSW` is the root namespace module, includes following namespaces and modules:

- `rest`
- `graphql`
- `Node` module
- `ServiceWorker` module
- `Rest` module
- `GraphQL` module

### `Node` module

- `setup(array(requestHandler))`
- `server |> listen()`
- `server |> close()`
- `server |> resetHandlers()`
- `server |> restoreHandlers()`
- `server |> user(requestHandler)`
- `rest |> get(string, (req, res, ctx) => { });`
- `rest |> post(string, (req, res, ctx) => { });`
- `rest |> put(string, (req, res, ctx) => { });`
- `rest |> patch(string, (req, res, ctx) => { });`
- `rest |> delete(string, (req, res, ctx) => { });`
- `rest |> options(string, (req, res, ctx) => { });`

### `ServiceWorker` module

- `setup(array(requestHandler))`
- `worker |> start()`
- `worker |> stop()`
- `worker |> resetHandlers()`
- `worker |> restoreHandlers()`
- `worker |> user(requestHandler)`
- `graphql |> query(string, (req, res, ctx) => { });`
- `graphql |> mutation(string, (req, res, ctx) => { });`

### `Rest` module

- `res |> mock(array(responseTransformer))`
- `res |> mockOnce(array(responseTransformer))`
- `ctx |> status(int)`
- `ctx |> set(string, string)`
- `ctx |> delay(int)`
- `ctx |> fetch(req)`
- `ctx |> text(string)`
- `ctx |> json(Js.Json.t)`
- `ctx |> xml(string)`

### `GraphQL` module

- `res |> mock(array(responseTransformer))`
- `res |> mockOnce(array(responseTransformer))`
- `ctx |> status(int)`
- `ctx |> set(string, string)`
- `ctx |> delay(int)`
- `ctx |> fetch(req)`
- `ctx |> data(Js.Json.t)`
- `ctx |> errors(array(Js.Json.t))`

### Example of Rest

For more example, please refer to [`MSW_node_test.re`](/__tests__/MSW_node_test.re) and [`mocks.re`](/__tests__/support/mocks.re).

```res
open MSW

let getRepoInfo =
  rest |> get(
    @reason.raw_literal("https://api.github.com/repos/:owner/:repo")
    "https://api.github.com/repos/:owner/:repo",
    (req, res, ctx) => {
      let owner =
        req.params
        ->Js.Dict.get(@reason.raw_literal("owner") "owner")
        ->Belt.Option.getWithDefault(@reason.raw_literal("N/A") "N/A")
      let repo =
        req.params
        ->Js.Dict.get(@reason.raw_literal("repo") "repo")
        ->Belt.Option.getWithDefault(@reason.raw_literal("N/A") "N/A")

      res |> Rest.mock([
        ctx |> Rest.status(200),
        ctx |> Rest.text(
          @reason.raw_literal("owner: ") "owner: " ++
          (owner ++
          (@reason.raw_literal(", repo: ") ", repo: " ++ repo)),
        ),
      ]
    },
  )

let getRepoInfoError =
  rest |> get(
    @reason.raw_literal("https://api.github.com/repos/:owner/:repo")
    "https://api.github.com/repos/:owner/:repo",
    (req, res, ctx) =>
      res |> Rest.mock([
        ctx |> Rest.status(500),
        ctx |> Rest.text(@reason.raw_literal("Oops") "Oops"),
      ]),
  )

let server = Node.setup([getRepoInfo])

server->listen()
server->use(getRepoInfoError)
server->restoreHandlers()
server->resetHandlers()
server->close()
)
```

### Example of GraphQL

For more example, please refer to [`MSW_browser.re`](/__tests__/support/MSW_browser.re) and [`mocks.re`](/__tests__/support/mocks.re).

```res
open MSW

let queryUserDetail =
  graphql |> query(
    @reason.raw_literal("GetUserDetail") "GetUserDetail",
    (req, res, ctx) =>
      res |> GraphQL.mock([
        ctx |> GraphQL.status(200),
        ctx |> GraphQL.data(
          Js.Dict.fromList(list{
            (@reason.raw_literal("name") "name", req.variables["name"]),
          }) |> Js.Json.object_,
        ),
      ]),
  )

let queryUserDetailError =
  graphql |> query(
    @reason.raw_literal("GetUserDetail") "GetUserDetail",
    (req, res, ctx) => {
      let message = (
        @reason.raw_literal("message") "message",
        Js.Json.string(
          @reason.raw_literal("This is a mocked error: ")
          "This is a mocked error: " ++
          req.variables["name"],
        ),
      )
      let location = Js.Dict.fromList(list{
        (@reason.raw_literal("line") "line", Js.Json.number(1.0)),
        (@reason.raw_literal("column") "column", Js.Json.number(2.0)),
      })
      let locations = (
        @reason.raw_literal("locations") "locations",
        Js.Json.objectArray([location]),
      )

      res |> GraphQL.mock([
        ctx |> GraphQL.status(200),
        ctx |> GraphQL.errors([
          Js.Dict.fromList(list{message, locations}) |> Js.Json.object_,
        ]),
      ])
    },
  )

let worker = ServiceWorker.setup([queryUserDetail])

worker->start()
worker->use(GetUserDetailError)
worker->restoreHandlers()
worker->resetHandlers()
worker->stop()
```

# Testing the library

```
npm test
```

this will compile and execute tests with `bs-jest`

# Contributions

Don't hesitate to open a PR with a new binding - while bumping up the amount of covered bindings in the README.
There are tests, use them and write the most simple test you can think of to make sure that the bindings work correctly.
