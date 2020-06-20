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

```re
open MSW;

let getRepoInfo =
  rest
  |> get("https://api.github.com/repos/:owner/:repo", (req, res, ctx) => {
       let owner =
         req.params->Js.Dict.get("owner")->Belt.Option.getWithDefault("N/A");
       let repo =
         req.params->Js.Dict.get("repo")->Belt.Option.getWithDefault("N/A");

       res
       |> Rest.mock([|
            ctx |> Rest.status(200),
            ctx |> Rest.text("owner: " ++ owner ++ ", repo: " ++ repo),
          |]);
     });

let getRepoInfoError =
  rest
  |> get("https://api.github.com/repos/:owner/:repo", (req, res, ctx) =>
       res
       |> Rest.mock([|ctx |> Rest.status(500), ctx |> Rest.text("Oops")|])
     );

let server = Node.setup([|getRepoInfo|]);

server->listen();
server->use(getRepoInfoError);
server->restoreHandlers();
server->resetHandlers();
server->close();

```

### Example of GraphQL

For more example, please refer to [`MSW_browser.re`](/__tests__/support/MSW_browser.re) and [`mocks.re`](/__tests__/support/mocks.re).

```re
open MSW;

let queryUserDetail =
  graphql
  |> query("GetUserDetail", (req, res, ctx) =>
       res
       |> GraphQL.mock([|
            ctx |> GraphQL.status(200),
            ctx
            |> GraphQL.data(
                 Js.Dict.fromList([("name", req.variables##name)])
                 |> Js.Json.object_,
               ),
          |])
     );

let queryUserDetailError =
  graphql
  |> query("GetUserDetail", (req, res, ctx) => {
       let message = (
         "message",
         Js.Json.string("This is a mocked error: " ++ req.variables##name),
       );
       let location =
         Js.Dict.fromList([
           ("line", Js.Json.number(1.0)),
           ("column", Js.Json.number(2.0)),
         ]);
       let locations = ("locations", Js.Json.objectArray([|location|]));

       res
       |> GraphQL.mock([|
            ctx |> GraphQL.status(200),
            ctx
            |> GraphQL.errors([|
                 Js.Dict.fromList([message, locations]) |> Js.Json.object_,
               |]),
          |]);
     });

let worker = ServiceWorker.setup([|queryUserDetail|]);

worker->start();
worker->use(GetUserDetailError);
worker->restoreHandlers();
worker->resetHandlers();
worker->stop();

```

# Testing the library

```
npm test
```

this will compile and execute tests with `bs-jest`

# Contributions

Don't hesitate to open a PR with a new binding - while bumping up the amount of covered bindings in the README.
There are tests, use them and write the most simple test you can think of to make sure that the bindings work correctly.
