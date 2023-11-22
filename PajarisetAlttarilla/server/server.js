const express = require('express');
const session = require('express-session');
const bodyParser = require('body-parser');
const path = require('path');

let app = express();

app.use(session({
  secret: "2020häät1010",
  resave: true,
  saveUninitialized: true
}));
app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());
app.use('/assets', express.static(path.join(__dirname, '/../build/assets')));
app.use('/.well-known', express.static(path.join(__dirname, '/../build/.well-known')));

app.get('/', (req, res) => {
  if (req.session.authenticated) {
    res.sendFile(path.join(__dirname, '/../build/index.html'));
  }
  else {
    res.sendFile(path.join(__dirname, '/../build/login.html'));
  }
});

app.post('/auth', (req, res) => {
  if (req.body.password == "xxx") {
    req.session.authenticated = true;
  }
  res.redirect('/');
});

app.get('*', (req, res) => {
  res.redirect('/');
});

let port = process.env.PORT || 8080;
app.listen(port || 8080, () => {
  console.log(`App listening on port ${port}`);
  console.log('Press Ctrl+C to quit.');
});

module.exports = app;