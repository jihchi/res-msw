module.exports = {
  setupFiles: ['<rootDir>/jest.setup.js'],
  testPathIgnorePatterns: ['/node_modules/', '<rootDir>/__tests__/support/'],
  coveragePathIgnorePatterns: ['/node_modules/', '<rootDir>/__tests__/'],
};
