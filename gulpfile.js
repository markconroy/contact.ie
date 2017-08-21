var gulp = require('gulp-help')(require('gulp'));
    sourcemaps = require('gulp-sourcemaps'),
    sass = require('gulp-sass'),
    autoprefixer = require('gulp-autoprefixer'),
    cleancss = require('gulp-clean-css'),
    notify = require('gulp-notify'),
    spritesmith = require('gulp.spritesmith'),
    browserSync = require('browser-sync').create();
    sassGlob = require('gulp-sass-bulk-import');
    csscomb = require('gulp-csscomb');
    sassLint = require('gulp-sass-lint');

// Error notifications.
var reportError = function (error) {
  notify({
    title: 'Gulp Task Error',
    message: 'Check the console.'
  }).write(error);
  // print the error in terminal.
  console.log(error.toString());
  this.emit('end');
};

gulp.task('styles', 'Creates production-ready css', function() {
  return gulp.src('./sass/**/*.scss')
    .pipe(sassGlob())
    .pipe(sass().on('error', sass.logError))
    .pipe(autoprefixer({browsers: ['last 2 versions', 'ie 9']}))
    .pipe(gulp.dest('css'));
});

gulp.task('styles:dev', 'Creates developer-friendly css', function() {
  return gulp.src('sass/*.scss')
    .pipe(sourcemaps.init())
    .pipe(sassGlob())
    .pipe(sass().on('error', reportError))
    .pipe(autoprefixer({browsers: ['last 2 versions', 'ie 9']}))
    .pipe(sourcemaps.write())
    .pipe(gulp.dest('css'))
    .pipe(browserSync.stream());
});

gulp.task('lint', false, function() {
  return gulp.src('sass/**/*.s+(a|c)ss')
    .pipe(sassLint({
      options: {
        formatter: 'table'
      },
      configFile: '.sass-lint.yml'
    }))
    .pipe(sassLint.format())
    .pipe(sassLint.failOnError());
})

gulp.task('comb', false, function() {
  return gulp.src(['sass/**/*.scss'], {base: './'})
    .pipe(csscomb())
    .pipe(gulp.dest('./'));
})

gulp.task('sprite', false, function () {
  var spriteData = gulp.src('images/sprites/*.png')
    .pipe(spritesmith({
      /* this whole image path is used in css background declarations */
      imgName: '../images/sprites/sprite/sprite.png',
      cssName: '_sprites.scss'
    }));
  spriteData.img.pipe(gulp.dest('img'));
  spriteData.css.pipe(gulp.dest('sass'));
});

gulp.task('watch', 'Watches for your changes and refreshes all teh things', function() {
  var config = require('./gulpfile-config.json');
  // Set your localhost address
  browserSync.init({
    proxy: config.browserSync.proxy
  });
  // Watch .scss files
  gulp.watch(['images/sprites/*.png'], ['sprite']);
  gulp.watch(["sass/**/*.scss", "sprites.scss", 'images/**/*'], ['styles:dev']);
  gulp.watch(['css/style.css', 'js/**/*.js', '.php']).on('change', browserSync.reload);

});

gulp.task("default", ["help"]);
