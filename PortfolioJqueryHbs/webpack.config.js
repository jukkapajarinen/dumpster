let path = require('path');
let webpack = require('webpack');
let HtmlWebpackPlugin = require('html-webpack-plugin');
let CleanWebpackPlugin = require('clean-webpack-plugin');

module.exports = {
  entry: './src/index.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js'
  },
  module: {
    rules: [
      { test: /\.js$/, exclude: '/node_modules/', use: [{loader: 'babel-loader', options: {presets: ['es2015']}}] },
      { test: /\.scss$/, exclude:'/node_modules/', use: ['style-loader', 'css-loader', 'sass-loader'] },
      { test: /\.(jpg|png|ico)$/, exclude: '/node_modules/', use: [{ loader: 'file-loader', options: { name: '[name].[ext]' } }] },
      { test: /\.hbs$/, exclude: '/node_modules/', use: ['handlebars-loader'] },
      { test: /\.html$/, exclude:'/node_modules/', use: ['html-loader'] }
    ]
  },
  devtool: 'eval-source-map',
  plugins: [
    new HtmlWebpackPlugin({ template: 'index.html' }),
    new CleanWebpackPlugin(['dist']),
    new webpack.ProvidePlugin({ $: 'jquery', jQuery: 'jquery' })
  ]
}