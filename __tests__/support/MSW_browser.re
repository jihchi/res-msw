open MSW;

let worker =
  setupWorker([|
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

worker->start();

let injectToWindow = [%bs.raw
  {|(worker) => {
  window.bsmsw = {
    worker,
  }
}|}
];

injectToWindow(worker);
