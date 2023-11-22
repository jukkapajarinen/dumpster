var express = require('express');
var bodyparser = require('body-parser');
var app = express();

app.set('view engine', 'ejs');
app.use('/assets', express.static('assets'));
app.use(bodyparser.urlencoded({extended:false}));

app.get('/', function(req, res) {
  res.render('index');
});

app.get('/contact', function (req, res) {
  res.render('contact', {query: req.query});
});

app.post('/contact', function (req, res) {
  res.render('contact-success', {data: req.body});
});

app.get('/profile/:id', function(req, res) {
  var data = {age: 27, job: 'ninja', hobbies: ['eating', 'fishing', 'running']};
  res.render('profile', {person: req.params.id, data: data});
});

app.listen(3000, '127.0.0.1');