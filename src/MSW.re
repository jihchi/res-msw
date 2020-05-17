module Base = {
  type t;

  type request = {params: Js.Dict.t(string)};
  type response;
  type responseTransformer;
  type completeTransformer;
  type responseResolver = (request, response, t) => completeTransformer;

  let makeResponse:
    (response, array(responseTransformer)) => completeTransformer = [%raw
    {|
  function (response, transformers) {
      return response(...transformers);
  }
|}
  ];

  [@bs.send] external status: (t, int) => responseTransformer = "status";
  [@bs.send] external set: (t, string, string) => responseTransformer = "set";
  [@bs.send] external delay: (t, int) => responseTransformer = "delay";
  [@bs.send] external fetch: (t, request) => responseTransformer = "fetch";
};

module Rest = {
  include Base;

  [@bs.module "msw"] [@bs.val] external rest: t = "rest";

  [@bs.send] external text: (t, string) => responseTransformer = "text";
  [@bs.send] external json: (t, Js.Json.t) => responseTransformer = "json";
  [@bs.send] external xml: (t, string) => responseTransformer = "xml";
};

module GraphQL = {
  include Base;

  [@bs.module "msw"] [@bs.val] external graphql: t = "graphql";

  [@bs.send] external data: (t, Js.Json.t) => responseTransformer = "data";
  [@bs.send]
  external errors: (t, array(Js.Json.t)) => responseTransformer = "errors";
};

type schemaAPI;
type nodeServer;
type requestHandler;

[@bs.module "msw"] [@bs.variadic]
external setupWorker: array(requestHandler) => schemaAPI = "setupWorker";

[@bs.send] external start: (schemaAPI, unit) => unit = "start";

[@bs.send] external stop: (schemaAPI, unit) => unit = "stop";

[@bs.module "msw/node"] [@bs.variadic]
external setupServer: array(requestHandler) => nodeServer = "setupServer";

[@bs.send] external listen: (nodeServer, unit) => unit = "listen";

[@bs.send] external close: (nodeServer, unit) => unit = "close";

[@bs.send]
external get: (Rest.t, string, Rest.responseResolver) => requestHandler =
  "get";

[@bs.send]
external post: (Rest.t, string, Rest.responseResolver) => requestHandler =
  "post";

[@bs.send]
external put: (Rest.t, string, Rest.responseResolver) => requestHandler =
  "put";

[@bs.send]
external patch: (Rest.t, string, Rest.responseResolver) => requestHandler =
  "patch";

[@bs.send]
external delete: (Rest.t, string, Rest.responseResolver) => requestHandler =
  "delete";

[@bs.send]
external options: (Rest.t, string, Rest.responseResolver) => requestHandler =
  "options";

[@bs.send]
external query: (GraphQL.t, string, GraphQL.responseResolver) => requestHandler =
  "query";

[@bs.send]
external mutation:
  (GraphQL.t, string, GraphQL.responseResolver) => requestHandler =
  "mutation";

let rest = Rest.rest;

let graphql = GraphQL.graphql;
