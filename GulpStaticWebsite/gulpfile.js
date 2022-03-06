const gulp = require("gulp");
const gulpUtil = require("gulp-util");
const gulpSass = require("gulp-sass")(require("sass"));
const plugins = require("gulp-load-plugins")();
const browserSync = require("browser-sync").create();
const webpack = require("webpack");
const terserPlugin = require("terser-webpack-plugin");
const autoprefixer = require("autoprefixer");
const cssnano = require("cssnano");
const path = require("path");

/**********************************************************************/
/* Define post-css configuration
/**********************************************************************/
const postcssConfig = [
  autoprefixer({
    overrideBrowserslist: ["defaults"],
  }),
  cssnano({
    preset: [
      "default",
      {
        discardComments: { removeAll: true },
        normalizeUrl: false,
      },
    ],
  }),
];

/**********************************************************************/
/* Define webpack configuration
/**********************************************************************/
const webpackConfig = {
  mode: "production",
  entry: { main: "./scripts/main.js" },
  output: { path: path.resolve(__dirname, "./_build"), filename: "build.js" },
  plugins: [new webpack.ProvidePlugin({ $: "jquery", jQuery: "jquery" })],
  optimization: {
    minimize: true,
    minimizer: [
      new terserPlugin({
        terserOptions: { format: { comments: false } },
        extractComments: false,
      }),
    ],
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: "/node_modules/",
        use: [
          {
            loader: "babel-loader",
            options: { presets: ["@babel/preset-env"] },
          },
        ],
      },
    ],
  },
};

/**********************************************************************/
/* Gulp tasks for bundling css & js and copying static files
/**********************************************************************/
const fonts = () => gulp.src("./fonts/**/*").pipe(gulp.dest("./_build/fonts"));
const icons = () =>
  gulp
    .src("./node_modules/@fortawesome/fontawesome-free/webfonts/*.ttf")
    .pipe(gulp.dest("./_build/fonts"));
const images = () =>
  gulp.src("./images/**/*").pipe(gulp.dest("./_build/images"));
const pages = () => gulp.src("./pages/**/*.html").pipe(gulp.dest("./_build"));
const static = gulp.parallel(fonts, icons, images, pages);
const styles = () =>
  gulp
    .src(["./styles/**/main.scss", "./styles/**/*.css"])
    .pipe(gulpSass.sync().on("error", gulpSass.logError))
    .pipe(plugins.concat("build.css"))
    .pipe(plugins.cssimport())
    .pipe(plugins.postcss(postcssConfig))
    .pipe(gulp.dest("./_build"));
const scripts = (callback) => {
  webpack(webpackConfig, (err, stats) => {
    if (err) throw new gulpUtil.PluginError("webpack", err);
    gulpUtil.log("[webpack]", stats.toString({ colors: true }));
    callback();
  });
};

/**********************************************************************/
/* Gulp tasks for cleaning, building and serving
/**********************************************************************/
const clean = () =>
  gulp.src("./_build", { read: false, allowEmpty: true }).pipe(plugins.clean());
const build = gulp.parallel(static, styles, scripts);
const serve = () => {
  browserSync.init({
    server: { baseDir: "./_build" },
    port: 8080,
    ui: false,
  });
  gulp.watch(["./fonts/**/*.*", "./images/**/*.*", "./pages/**/*.*"]).on(
    "change",
    gulp.series(static, () => browserSync.reload())
  );
  gulp.watch("./scripts/**/*.*").on(
    "change",
    gulp.series(scripts, () => browserSync.reload())
  );
  gulp.watch("./styles/**/*.*").on(
    "change",
    gulp.series(styles, () => browserSync.reload())
  );
};

/**********************************************************************/
/* Export gulp tasks
/**********************************************************************/
module.exports = {
  clean: gulp.series(clean),
  build: gulp.series(clean, build),
  serve: gulp.series(clean, build, serve),
};
