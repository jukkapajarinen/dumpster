let webpack = require('webpack');
let path = require('path');

let DIST_DIR = path.resolve(__dirname, "dist");
let SRC_DIR = path.resolve(__dirname, "src");

let config = {
  mode: 'development',
  entry: SRC_DIR + "/app/index.js",
  output: {
    path: DIST_DIR + "/app",
    filename: "bundle.js",
    publicPath: "/app/"
  },
  module: {
    rules : [
      {
        test: /\.js?/,
        include: SRC_DIR,
        loader: "babel-loader",
        query: {
          presets: ["@babel/react", "@babel/preset-env"]
        }
      }
    ]
  }
};

module.exports = config;
