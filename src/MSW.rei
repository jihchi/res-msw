module Rest: {
  type request = {params: Js.Dict.t(string)};
  type response;
  type context;

  type responseTransformer;
  type completeTransformer;
  type responseResolver = (request, response, context) => completeTransformer;

  let mock: (array(responseTransformer), response) => completeTransformer;

  let status: (int, context) => responseTransformer;
  let set: (string, string, context) => responseTransformer;
  let delay: (int, context) => responseTransformer;
  let fetch: (request, context) => responseTransformer;

  let text: (string, context) => responseTransformer;
  let json: (Js.Json.t, context) => responseTransformer;
  let xml: (string, context) => responseTransformer;
};

module GraphQL: {
  type request('a) = {
    variables: Js.t({..} as 'a),
    params: Js.Dict.t(string),
  };
  type response;
  type context;

  type responseTransformer;
  type completeTransformer;
  type responseResolver('a) = (request('a), response, context) => completeTransformer;

  let mock: (array(responseTransformer), response) => completeTransformer;

  let status: (int, context) => responseTransformer;
  let set: (string, string, context) => responseTransformer;
  let delay: (int, context) => responseTransformer;
  let fetch: (request('a), context) => responseTransformer;

  let data: (Js.Json.t, context) => responseTransformer;
  let errors: (array(Js.Json.t), context) => responseTransformer;
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

let get: (string, Rest.responseResolver, Rest.context) => requestHandler;

let post: (string, Rest.responseResolver, Rest.context) => requestHandler;

let put: (string, Rest.responseResolver, Rest.context) => requestHandler;

let patch: (string, Rest.responseResolver, Rest.context) => requestHandler;

let delete: (string, Rest.responseResolver, Rest.context) => requestHandler;

let options: (string, Rest.responseResolver, Rest.context) => requestHandler;

let query:
  (string, GraphQL.responseResolver('a), GraphQL.context) => requestHandler;

let mutation:
  (string, GraphQL.responseResolver('a), GraphQL.context) => requestHandler;

let rest: Rest.context;

let graphql: GraphQL.context;
