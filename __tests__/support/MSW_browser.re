open MSW;

module Option = Belt.Option;

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
                   Js.Dict.fromList([("referrer", req.variables##referrer)])
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
