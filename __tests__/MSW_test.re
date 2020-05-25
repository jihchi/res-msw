open Js.Promise;
open Jest;
open Expect;
open MSW;

module Option = Belt.Option;

describe("Node Server", () => {
  let server =
    setupServer([|
      rest
      |> get("https://httpbin.org/:owner/:repo", (req, res, ctx) => {
           let body =
             Printf.sprintf(
               "%s/%s",
               req.params
               |> Js.Dict.get(_, "owner")
               |> Option.getWithDefault(_, "N/A"),
               req.params
               |> Js.Dict.get(_, "repo")
               |> Option.getWithDefault(_, "N/A"),
             );

           res
           |> Rest.mock([|ctx |> Rest.status(200), ctx |> Rest.text(body)|]);
         }),
      rest
      |> post("https://httpbin.org/anything/:owner/:repo", (req, res, ctx) => {
           let body =
             Printf.sprintf(
               "%s/%s",
               req.params
               |> Js.Dict.get(_, "owner")
               |> Option.getWithDefault(_, "N/A"),
               req.params
               |> Js.Dict.get(_, "repo")
               |> Option.getWithDefault(_, "N/A"),
             );

           res
           |> Rest.mock([|ctx |> Rest.status(200), ctx |> Rest.text(body)|]);
         }),
      rest
      |> put("https://httpbin.org/anything/:owner/:repo", (req, res, ctx) => {
           let body =
             Printf.sprintf(
               "%s/%s",
               req.params
               |> Js.Dict.get(_, "owner")
               |> Option.getWithDefault(_, "N/A"),
               req.params
               |> Js.Dict.get(_, "repo")
               |> Option.getWithDefault(_, "N/A"),
             );

           res
           |> Rest.mock([|ctx |> Rest.status(200), ctx |> Rest.text(body)|]);
         }),
      rest
      |> patch("https://httpbin.org/anything/:owner/:repo", (req, res, ctx) => {
           let body =
             Printf.sprintf(
               "%s/%s",
               req.params
               |> Js.Dict.get(_, "owner")
               |> Option.getWithDefault(_, "N/A"),
               req.params
               |> Js.Dict.get(_, "repo")
               |> Option.getWithDefault(_, "N/A"),
             );

           res
           |> Rest.mock([|ctx |> Rest.status(200), ctx |> Rest.text(body)|]);
         }),
      rest
      |> delete("https://httpbin.org/anything/:owner/:repo", (req, res, ctx) => {
           let body =
             Printf.sprintf(
               "%s/%s",
               req.params
               |> Js.Dict.get(_, "owner")
               |> Option.getWithDefault(_, "N/A"),
               req.params
               |> Js.Dict.get(_, "repo")
               |> Option.getWithDefault(_, "N/A"),
             );

           res
           |> Rest.mock([|ctx |> Rest.status(200), ctx |> Rest.text(body)|]);
         }),
      rest
      |> options("https://httpbin.org/anything/:owner/:repo", (req, res, ctx) => {
           let body =
             Printf.sprintf(
               "%s/%s",
               req.params
               |> Js.Dict.get(_, "owner")
               |> Option.getWithDefault(_, "N/A"),
               req.params
               |> Js.Dict.get(_, "repo")
               |> Option.getWithDefault(_, "N/A"),
             );

           res
           |> Rest.mock([|ctx |> Rest.status(200), ctx |> Rest.text(body)|]);
         }),
    |]);

  beforeAll(() => {server->listen()});

  afterAll(() => {server->close()});

  describe("Rest", () => {
    testPromise("get works", () => {
      Fetch.fetch("https://httpbin.org/jihchi/bs-msw")
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("post works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/anything/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Post, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("put works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/anything/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Put, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("patch works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/anything/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Patch, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("delete works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/anything/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Delete, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("options works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/anything/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Options, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });
  });
});

Skip.describe("Service Worker", () => {
  let worker =
    setupWorker([|
      rest
      |> get("https://api.github.com/repos/:owner/:repo", (req, res, ctx) => {
           let body =
             Printf.sprintf(
               "%s/%s",
               req.params
               |> Js.Dict.get(_, "owner")
               |> Option.getWithDefault(_, "N/A"),
               req.params
               |> Js.Dict.get(_, "repo")
               |> Option.getWithDefault(_, "N/A"),
             );

           res
           |> Rest.mock([|ctx |> Rest.status(200), ctx |> Rest.text(body)|]);
         }),
      graphql
      |> query("GetUserDetail", (req, res, ctx) => {
           res
           |> GraphQL.mock([|
                ctx |> GraphQL.status(200),
                ctx
                |> GraphQL.data(
                     Js.Dict.fromList([("name", req.variables##name)])
                     |> Js.Json.object_,
                   ),
              |])
         }),
      graphql
      |> mutation("Logout", (req, res, ctx) => {
           res
           |> GraphQL.mock([|
                ctx |> GraphQL.status(200),
                ctx
                |> GraphQL.data(
                     Js.Dict.fromList([
                       ("referrer", req.variables##referrer),
                     ])
                     |> Js.Json.object_,
                   ),
              |])
         }),
      graphql
      |> query("GetUserDetailError", (_req, res, ctx) => {
           res
           |> GraphQL.mock([|
                ctx |> GraphQL.status(200),
                ctx |> GraphQL.errors([|Js.Dict.empty() |> Js.Json.object_|]),
              |])
         }),
      graphql
      |> mutation("LogoutError", (_req, res, ctx) => {
           res
           |> GraphQL.mock([|
                ctx |> GraphQL.status(200),
                ctx |> GraphQL.errors([|Js.Dict.empty() |> Js.Json.object_|]),
              |])
         }),
    |]);

  beforeAll(() => {worker->start()});

  afterAll(() => {worker->stop()});

  describe("Rest", () => {
    testPromise("get works", () => {
      Fetch.fetch("https://api.github.com/repos/jihchi/bs-msw")
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("post works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/anything/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Post, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });
  });

  describe("GraphQL", () => {
    testPromise("query works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/graphql",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=
            Fetch.BodyInit.make(
              {|{ "query": "query GetUserDetail { user { name  } }", "variables": { "foo": 123 } }|},
            ),
          (),
        ),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("query error works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/graphql",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=
            Fetch.BodyInit.make(
              {|{ "query": "query GetUserDetailError { user { name } }", "variables": { "foo": 123 } }|},
            ),
          (),
        ),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("mutation works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/graphql",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=
            Fetch.BodyInit.make(
              {|{ "query": "mutation Logout { logout { session } }", "variables": { "foo": 123 } }|},
            ),
          (),
        ),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("mutation error works", () => {
      Fetch.fetchWithInit(
        "https://httpbin.org/graphql",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=
            Fetch.BodyInit.make(
              {|{ "query": "mutation LogoutError { logout { session } }", "variables": { "foo": 123 } }|},
            ),
          (),
        ),
      )
      |> then_(Fetch.Response.text)
      |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
    });
  });
});
