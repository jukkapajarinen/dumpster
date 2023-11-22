const gulp = require("gulp");
const gulpUtil = require("gulp-util");
const plugins = require("gulp-load-plugins")();
const browsersync = require("browser-sync").create();
const webpack = require("webpack");
const uglifyjsplugin = require("uglifyjs-webpack-plugin");
const autoprefixer = require("autoprefixer");
const cssnano = require("cssnano");
const path = require("path");

// Print names of installed gulp-plugins for debugging.
console.log("Installed Gulp-plugins:", plugins);

// Define post-css configuration
const postcssConfig = [
  autoprefixer({
    overrideBrowserslist: ["defaults"]
  }),
  cssnano({
    preset: ["default", { discardComments: { removeAll: true } }]
  })
];

// Define webpack configuration
const webpackConfig = {
  entry: { main: "./src/scripts/main.js" },
  output: { path: path.resolve(__dirname, "./build"), filename: "build.js" },
  plugins: [ new webpack.ProvidePlugin({ $: 'jquery', jQuery: 'jquery' }) ],
  optimization: {
    minimize: true,
    minimizer: [ new uglifyjsplugin({uglifyOptions: { output: { comments: false } }}) ],
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: "/node_modules/",
        use: [{ loader: "babel-loader", options: { presets: ["@babel/preset-env"] } }]
      }
    ]
  }
};

// Gulp task for building bundled stylesheet
let styles = () => {
  return gulp.src("./src/styles/*.css")
    .pipe(plugins.concat("build.css"))
    .pipe(plugins.cssimport())
    .pipe(plugins.postcss(postcssConfig))
    .pipe(gulp.dest("./build"))
};

// Gulp task for building bundled javascript file
let scripts = (callback) => {
  webpack(webpackConfig, (err, stats) => {
    if(err) throw new gulpUtil.PluginError("webpack", err);
    gulpUtil.log("[webpack]", stats.toString({ colors: true }));
    callback();
  });
};

// Gulp task for moving static files to build directory
let static = gulp.parallel(
  () => gulp.src("./src/fonts/**/*").pipe(gulp.dest("./build/fonts")),
  () => gulp.src("./node_modules/@fortawesome/fontawesome-free/webfonts/*.ttf").pipe(gulp.dest("./build/fonts")),
  () => gulp.src("./src/images/**/*").pipe(gulp.dest("./build/images")),
  () => gulp.src("./src/index.html").pipe(gulp.dest("./build"))
);

// Gulp task for cleaning / removing the build directory
let clean = () => {
  return gulp.src("./build", { read: false, allowEmpty: true })
    .pipe(plugins.clean());
};

// Gulp task for building all resources into full distribution
let build = gulp.parallel(static, scripts, styles);

// Gulp task for building and serving application for development
let serve = () => {
  browsersync.init({
    server: { baseDir: "./build" },
    port: 8080,
    ui: false
  });

  // Reload the app on any change in src
  gulp.watch("./src/**/*.*").on("change", gulp.series(build, () => browsersync.reload()));
};

// Export gulp tasks
module.exports = {
  styles: gulp.series(styles),
  scripts: gulp.series(scripts),
  static: gulp.series(static),
  clean: gulp.series(clean),
  build: gulp.series(clean, build),
  serve: gulp.series(clean, build, serve)
};
