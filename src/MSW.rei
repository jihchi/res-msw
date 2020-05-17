module Rest: {
  type t;

  type request = {params: Js.Dict.t(string)};
  type response;
  type responseTransformer;
  type completeTransformer;
  type responseResolver = (request, response, t) => completeTransformer;

  let makeResponse:
    (response, array(responseTransformer)) => completeTransformer;

  let status: (t, int) => responseTransformer;
  let set: (t, string, string) => responseTransformer;
  let delay: (t, int) => responseTransformer;
  let fetch: (t, request) => responseTransformer;

  let text: (t, string) => responseTransformer;
  let json: (t, Js.Json.t) => responseTransformer;
  let xml: (t, string) => responseTransformer;

  let rest: t;
};

module GraphQL: {
  type t;

  type request = {params: Js.Dict.t(string)};
  type response;
  type responseTransformer;
  type completeTransformer;
  type responseResolver = (request, response, t) => completeTransformer;

  let makeResponse:
    (response, array(responseTransformer)) => completeTransformer;

  let status: (t, int) => responseTransformer;
  let set: (t, string, string) => responseTransformer;
  let delay: (t, int) => responseTransformer;
  let fetch: (t, request) => responseTransformer;

  let data: (t, Js.Json.t) => responseTransformer;
  let errors: (t, array(Js.Json.t)) => responseTransformer;

  let graphql: t;
};

type schemaAPI;
type nodeServer;
type requestHandler;

let setupWorker: array(requestHandler) => schemaAPI;

let start: (schemaAPI, unit) => unit;

let stop: (schemaAPI, unit) => unit;

let setupServer: array(requestHandler) => nodeServer;

let listen: (nodeServer, unit) => unit;

let close: (nodeServer, unit) => unit;

let get: (Rest.t, string, Rest.responseResolver) => requestHandler;

let post: (Rest.t, string, Rest.responseResolver) => requestHandler;

let put: (Rest.t, string, Rest.responseResolver) => requestHandler;

let patch: (Rest.t, string, Rest.responseResolver) => requestHandler;

let delete: (Rest.t, string, Rest.responseResolver) => requestHandler;

let options: (Rest.t, string, Rest.responseResolver) => requestHandler;

let query: (GraphQL.t, string, GraphQL.responseResolver) => requestHandler;

let mutation: (GraphQL.t, string, GraphQL.responseResolver) => requestHandler;

let rest: Rest.t;

let graphql: GraphQL.t;
