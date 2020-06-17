/**
 * @jest-environment ./__tests__/support/browser-environment.js
 */

describe('Service Worker', () => {
  beforeAll(async () => {
    await page.goto('http://localhost:8080', { waitUntil: 'networkidle0' });
  });

  afterAll(async () => {});

  describe('Rest', () => {
    test('get works', async () => {
      const actual = await page.evaluate(async () => {
        const res = await fetch('https://api.github.com/repos/jihchi/bs-msw');
        const body = await res.text();
        return { status: res.status, body };
      });

      expect(actual).toEqual({ status: 200, body: 'jihchi/bs-msw' });
    });
  });

  describe('GraphQL', () => {
    test('query works', async () => {
      const actual = await page.evaluate(async () => {
        const res = await fetch('http://localhost:8080/graphql', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({
            query: `
              query GetUserDetail {
                user {
                  name
                }
              }`,
            variables: {
              name: 'jihchi/bs-msw',
            },
          }),
        });
        const body = await res.text();
        return { status: res.status, body };
      });

      expect(actual).toEqual({
        status: 200,
        body: '{"data":{"name":"jihchi/bs-msw"}}',
      });
    });
  });
});
