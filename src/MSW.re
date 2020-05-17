type schemaAPI;
type nodeServer;

type requestHandler = {
  mask: string,
  predicate: string => bool,
};

type request = {params: Js.Dict.t(string)};
type context;
type response;

type responseTransformer;
type responseTransformers;

type responseResolver = (request, response, context) => responseTransformers;

type rest;
type graphql;

[@bs.module "msw"] [@bs.val] external rest: rest = "rest";

[@bs.module "msw"] [@bs.val] external graphql: graphql = "graphql";

// Context
[@bs.send] external status: (context, int) => responseTransformer = "status";

[@bs.send]
external set: (context, string, string) => responseTransformer = "set";

[@bs.send] external delay: (context, int) => responseTransformer = "delay";

[@bs.send] external fetch: (context, request) => responseTransformer = "fetch";

// REST Utilities
[@bs.send] external text: (context, string) => responseTransformer = "text";

[@bs.send] external json: (context, Js.Json.t) => responseTransformer = "json";

[@bs.send] external xml: (context, string) => responseTransformer = "xml";

// GraphQL Utilities
[@bs.send] external data: (context, Js.Json.t) => responseTransformer = "data";

[@bs.send]
external errors: (context, array(Js.Json.t)) => responseTransformer =
  "errors";

[@bs.module "msw"] [@bs.variadic]
external setupWorker: array(requestHandler) => schemaAPI = "setupWorker";

[@bs.send]
external get: (rest, string, responseResolver) => requestHandler = "get";

[@bs.send]
external post: (rest, string, responseResolver) => requestHandler = "post";

[@bs.send]
external put: (rest, string, responseResolver) => requestHandler = "put";

[@bs.send]
external patch: (rest, string, responseResolver) => requestHandler = "patch";

[@bs.send]
external delete: (rest, string, responseResolver) => requestHandler = "delete";

[@bs.send]
external options: (rest, string, responseResolver) => requestHandler =
  "options";

[@bs.send]
external query: (rest, string, responseResolver) => requestHandler = "query";

[@bs.send]
external mutation: (rest, string, responseResolver) => requestHandler =
  "mutation";

[@bs.send] external start: (schemaAPI, unit) => unit = "start";

[@bs.send] external stop: (schemaAPI, unit) => unit = "stop";

[@bs.module "msw/node"] [@bs.variadic]
external setupServer: array(requestHandler) => nodeServer = "setupServer";

[@bs.send] external listen: (nodeServer, unit) => unit = "listen";

[@bs.send] external close: (nodeServer, unit) => unit = "close";

let makeResponse:
  (response, array(responseTransformer)) => responseTransformers = [%raw
  {|
  function (response, transformers) {
      return response(...transformers);
  }
|}
];
