module.exports = {
  entry: './__tests__/support/MSW_browser.bs.js',
  devtool: 'inline-source-map',
  devServer: {
    contentBase: './__tests__/support',
    hot: false,
    compress: true,
    liveReload: false,
  },
  resolve: {
    fallback: { timers: false, http: false, https: false, util: false },
  },
};
