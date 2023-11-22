const gulp = require("gulp");
const gulpUtil = require("gulp-util");
const gulpSass = require("gulp-sass");
const plugins = require("gulp-load-plugins")();
const browsersync = require("browser-sync").create();
const webpack = require("webpack");
const uglifyjsplugin = require("uglifyjs-webpack-plugin");
const autoprefixer = require("autoprefixer");
const cssnano = require("cssnano");
const path = require("path");
const themeName = "jukkapajarinen";
gulpSass.compiler = require("node-sass");

/**********************************************************************/
/* Define post-css configuration
/**********************************************************************/
const postcssConfig = [
  autoprefixer({
    overrideBrowserslist: ["defaults"]
  }),
  cssnano({
    preset: ["default", { 
      discardComments: { removeAll: true },
      normalizeUrl: false
    }]
  })
];

/**********************************************************************/
/* Define webpack configuration
/**********************************************************************/
const webpackConfig = {
  mode: "production",
  entry: { main: "./src/scripts/main.js" },
  output: { path: path.resolve(__dirname, `./${themeName}/build`), filename: "build.js" },
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

/**********************************************************************/
/* Gulp task for building bundled stylesheet
/**********************************************************************/
let styles = () => {
  return gulp.src("./src/sass/*.scss")
    .pipe(gulpSass().on('error', gulpSass.logError))
    .pipe(plugins.concat("build.css"))
    .pipe(plugins.cssimport())
    .pipe(plugins.postcss(postcssConfig))
    .pipe(gulp.dest(`./${themeName}/build`));
};

/**********************************************************************/
/* Gulp task for building bundled javascript file
/**********************************************************************/
let scripts = (callback) => {
  webpack(webpackConfig, (err, stats) => {
    if(err) throw new gulpUtil.PluginError("webpack", err);
    gulpUtil.log("[webpack]", stats.toString({ colors: true }));
    callback();
  });
};

/**********************************************************************/
/* Gulp task for moving static files to build directory
/**********************************************************************/
let static = gulp.parallel(
  () => gulp.src("./src/fonts/**/*").pipe(gulp.dest(`./${themeName}/build/fonts`)),
  () => gulp.src("./node_modules/@fortawesome/fontawesome-free/webfonts/*.ttf").pipe(gulp.dest(`./${themeName}/build/fonts`)),
  () => gulp.src("./src/images/**/*").pipe(gulp.dest(`./${themeName}/build/images`))
);

/**********************************************************************/
/* Gulp task for cleaning / removing the build directory
/**********************************************************************/
let clean = () => {
  return gulp.src(`./${themeName}/build`, { read: false, allowEmpty: true })
    .pipe(plugins.clean());
};

/**********************************************************************/
/* Gulp task for building all resources into full distribution
/**********************************************************************/
let build = gulp.parallel(static, scripts, styles);

/**********************************************************************/
/* Gulp task for building and serving application for development
/**********************************************************************/
let serve = () => {
  browsersync.init({ proxy: "http://localhost:8080" });

  // Reload the app on any change in src
  gulp.watch(`./src/**/*.*`).on("change", gulp.series(build, () => browsersync.reload()));
  gulp.watch(`./${themeName}/templates/**/*.*`).on("change", gulp.series(build, () => browsersync.reload()));
};

/**********************************************************************/
/* Export gulp tasks
/**********************************************************************/
module.exports = {
  styles: gulp.series(styles),
  scripts: gulp.series(scripts),
  static: gulp.series(static),
  clean: gulp.series(clean),
  build: gulp.series(clean, build),
  serve: gulp.series(clean, build, serve)
};
