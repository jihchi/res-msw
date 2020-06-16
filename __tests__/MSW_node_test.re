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
