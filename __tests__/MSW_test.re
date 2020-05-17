open Js.Promise;
open Jest;
open Expect;
open MSW;

describe("MSW", () => {
  let server =
    setupServer([|
      rest->get("https://api.github.com/repos/:owner/:repo", (req, res, ctx) => {
        let owner =
          req.params
          ->Js.Dict.get("owner")
          ->Belt.Option.getWithDefault("N/A");

        let repo =
          req.params->Js.Dict.get("repo")->Belt.Option.getWithDefault("N/A");

        res->makeResponse([|
          ctx->status(200),
          ctx->text(Printf.sprintf("%s/%s", owner, repo)),
        |]);
      }),
    |]);

  beforeAll(() => {server->listen()});

  afterAll(() => {server->close()});

  testPromise("it works", () => {
    Fetch.fetch("https://api.github.com/repos/jihchi/bs-msw")
    |> then_(Fetch.Response.text)
    |> then_(res => {expect(res) |> toEqual("jihchi/bs-msw") |> resolve})
  });
});
