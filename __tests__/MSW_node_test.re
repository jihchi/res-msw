open Js.Promise;
open Jest;
open Expect;
open MSW;

describe("Node Server", () => {
  let server =
    setupServer([|
      Mocks.Rest.get,
      Mocks.Rest.post,
      Mocks.Rest.put,
      Mocks.Rest.patch,
      Mocks.Rest.delete,
      Mocks.Rest.options,
      Mocks.GraphQL.queryOk,
      Mocks.GraphQL.queryError,
      Mocks.GraphQL.mutationOk,
      Mocks.GraphQL.mutationError,
    |]);

  beforeAll(() => {server->listen()});

  afterAll(() => {server->close()});

  describe("Rest", () => {
    testPromise("get works", () => {
      Fetch.fetch("https://api.github.com/repos/jihchi/bs-msw")
      |> then_(Fetch.Response.text)
      |> then_(text => {expect(text) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("post works", () => {
      Fetch.fetchWithInit(
        "https://api.github.com/repos/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Post, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(text => {expect(text) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("put works", () => {
      Fetch.fetchWithInit(
        "https://api.github.com/repos/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Put, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(text => {expect(text) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("patch works", () => {
      Fetch.fetchWithInit(
        "https://api.github.com/repos/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Patch, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(text => {expect(text) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("delete works", () => {
      Fetch.fetchWithInit(
        "https://api.github.com/repos/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Delete, ()),
      )
      |> then_(Fetch.Response.text)
      |> then_(text => {expect(text) |> toEqual("jihchi/bs-msw") |> resolve})
    });

    testPromise("options works", () => {
      Fetch.fetchWithInit(
        "https://api.github.com/repos/jihchi/bs-msw",
        Fetch.RequestInit.make(~method_=Options, ()),
      )
      |> then_(res => res->Fetch.Response.text)
      |> then_(text => {expect(text) |> toEqual("jihchi/bs-msw") |> resolve})
    });
  });

  describe("GraphQL", () => {
    let contentTypeJson =
      Fetch.HeadersInit.makeWithArray([|
        ("Content-Type", "application/json"),
      |]);

    testPromise("query works", () => {
      let body =
        {
          "query": {|
            query GetUserDetail {
              user {
                name
              }
            }
          |},
          "variables": {
            "name": "jihchi/bs-msw",
          },
        }
        ->Js.Json.stringifyAny
        ->Option.getWithDefault("")
        ->Fetch.BodyInit.make;

      Fetch.fetchWithInit(
        "http://this.does.not/matter",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~headers=contentTypeJson,
          ~body,
          (),
        ),
      )
      |> then_(res => res->Fetch.Response.text)
      |> then_(text => {
           expect(text)
           |> toEqual({|{"data":{"name":"jihchi/bs-msw"}}|})
           |> resolve
         });
    });

    testPromise("query error works", () => {
      let body =
        {
          "query": {|
            query GetUserDetailError {
              user {
                name
              }
            }
          |},
          "variables": {
            "name": "jihchi/bs-msw",
          },
        }
        ->Js.Json.stringifyAny
        ->Option.getWithDefault("")
        ->Fetch.BodyInit.make;

      Fetch.fetchWithInit(
        "http://this.does.not/matter",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~headers=contentTypeJson,
          ~body,
          (),
        ),
      )
      |> then_(res => res->Fetch.Response.text)
      |> then_(text => {
           expect(text)
           |> toEqual(
                {|{"errors":[{"message":"This is a mocked error: jihchi/bs-msw","locations":[{"line":1,"column":2}]}]}|},
              )
           |> resolve
         });
    });

    testPromise("mutation works", () => {
      let body =
        {
          "query": {|
            mutation Logout {
              logout {
                session
              }
            }
          |},
          "variables": {
            "referrer": "jihchi/bs-msw",
          },
        }
        ->Js.Json.stringifyAny
        ->Option.getWithDefault("")
        ->Fetch.BodyInit.make;

      Fetch.fetchWithInit(
        "http://this.does.not/matter",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~headers=contentTypeJson,
          ~body,
          (),
        ),
      )
      |> then_(res => res->Fetch.Response.text)
      |> then_(text => {
           expect(text)
           |> toEqual({|{"data":{"referrer":"jihchi/bs-msw"}}|})
           |> resolve
         });
    });

    testPromise("mutation error works", () => {
      let body =
        {
          "query": {|
            mutation Logout {
              logout {
                session
              }
            }
          |},
          "variables": {
            "referrer": "jihchi/bs-msw",
          },
        }
        ->Js.Json.stringifyAny
        ->Option.getWithDefault("")
        ->Fetch.BodyInit.make;

      Fetch.fetchWithInit(
        "http://this.does.not/matter",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~headers=contentTypeJson,
          ~body,
          (),
        ),
      )
      |> then_(res => res->Fetch.Response.text)
      |> then_(text => {
           expect(text)
           |> toEqual({|{"data":{"referrer":"jihchi/bs-msw"}}|})
           |> resolve
         });
    });
  });
});
