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
});
