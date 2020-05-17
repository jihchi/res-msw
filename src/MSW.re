module Base = {
  type request = {params: Js.Dict.t(string)};
  type response;
  type context;

  type responseTransformer;
  type completeTransformer;
  type responseResolver = (request, response, context) => completeTransformer;

  let mock: (array(responseTransformer), response) => completeTransformer = [%raw
    {|
  function (transformers, response) {
      return response(...transformers);
  }
|}
  ];

  [@bs.send]
  external rawStatus: (context, int) => responseTransformer = "status";
  let status = (code, ctx) => rawStatus(ctx, code);

  [@bs.send]
  external rawSet: (context, string, string) => responseTransformer = "set";
  let set = (key, value, ctx) => rawSet(ctx, key, value);

  [@bs.send]
  external rawDelay: (context, int) => responseTransformer = "delay";
  let delay = (ms, ctx) => rawDelay(ctx, ms);

  [@bs.send]
  external rawFetch: (context, request) => responseTransformer = "fetch";
  let fetch = (req, ctx) => rawFetch(ctx, req);
};

module Rest = {
  include Base;

  [@bs.module "msw"] [@bs.val] external instance: context = "rest";

  [@bs.send]
  external rawText: (context, string) => responseTransformer = "text";
  let text = (text, ctx) => rawText(ctx, text);

  [@bs.send]
  external rawJson: (context, Js.Json.t) => responseTransformer = "json";
  let json = (json, ctx) => rawJson(ctx, json);

  [@bs.send] external rawXml: (context, string) => responseTransformer = "xml";
  let xml = (xml, ctx) => rawXml(ctx, xml);
};

module GraphQL = {
  include Base;

  [@bs.module "msw"] [@bs.val] external instance: context = "graphql";

  [@bs.send]
  external rawData: (context, Js.Json.t) => responseTransformer = "data";
  let data = (json, ctx) => rawData(ctx, json);

  [@bs.send]
  external rawErrors: (context, array(Js.Json.t)) => responseTransformer =
    "errors";
  let errors = (errors, ctx) => rawErrors(ctx, errors);
};

type schemaAPI;
type nodeServer;
type requestHandler;

/* service worker */
[@bs.module "msw"] [@bs.variadic]
external setupWorker: array(requestHandler) => schemaAPI = "setupWorker";

[@bs.send] external start: (schemaAPI, unit) => unit = "start";

[@bs.send] external stop: (schemaAPI, unit) => unit = "stop";

/* node server */
[@bs.module "msw/node"] [@bs.variadic]
external setupServer: array(requestHandler) => nodeServer = "setupServer";

[@bs.send] external listen: (nodeServer, unit) => unit = "listen";

[@bs.send] external close: (nodeServer, unit) => unit = "close";

/* Rest request handlers */
[@bs.send]
external rawGet:
  (Rest.context, string, Rest.responseResolver) => requestHandler =
  "get";
let get = (url, resolver, ctx) => rawGet(ctx, url, resolver);

[@bs.send]
external rawPost:
  (Rest.context, string, Rest.responseResolver) => requestHandler =
  "post";
let post = (url, resolver, ctx) => rawPost(ctx, url, resolver);

[@bs.send]
external rawPut:
  (Rest.context, string, Rest.responseResolver) => requestHandler =
  "put";
let put = (url, resolver, ctx) => rawPut(ctx, url, resolver);

[@bs.send]
external rawPatch:
  (Rest.context, string, Rest.responseResolver) => requestHandler =
  "patch";
let patch = (url, resolver, ctx) => rawPatch(ctx, url, resolver);

[@bs.send]
external rawDelete:
  (Rest.context, string, Rest.responseResolver) => requestHandler =
  "delete";
let delete = (url, resolver, ctx) => rawDelete(ctx, url, resolver);

[@bs.send]
external rawOptions:
  (Rest.context, string, Rest.responseResolver) => requestHandler =
  "options";
let options = (url, resolver, ctx) => rawOptions(ctx, url, resolver);

/* GraphQL request handlers */
[@bs.send]
external rawQuery:
  (GraphQL.context, string, GraphQL.responseResolver) => requestHandler =
  "query";
let query = (url, resolver, ctx) => rawQuery(ctx, url, resolver);

[@bs.send]
external rawMutation:
  (GraphQL.context, string, GraphQL.responseResolver) => requestHandler =
  "mutation";
let mutation = (url, resolver, ctx) => rawMutation(ctx, url, resolver);

let rest = Rest.instance;

let graphql = GraphQL.instance;
