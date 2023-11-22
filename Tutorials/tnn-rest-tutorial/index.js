const express = require('express');
const routes = require('./routes/api');
const bodyparser = require('body-parser');
const mongoose = require('mongoose');

const app = express();
mongoose.connect('mongodb://localhost/ninjago');
mongoose.Promise = global.Promise;
app.use(express.static('public'));
app.use(bodyparser.json({type: "application/json"}));
app.use('/api', routes);
app.use((err, req, res, next) => res.status(422).send({error: err.message}));

app.listen(process.env.port || 3000, function() {
  console.log('Listening requests at :3000');
});