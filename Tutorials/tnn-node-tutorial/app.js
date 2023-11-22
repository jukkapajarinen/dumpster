var express = require('express');
var todoController = require('./controllers/todoController');
var bodyparser = require('body-parser');
var app = express();

app.set('view engine', 'ejs');
app.use(express.static('./public'));
app.use(bodyparser.urlencoded({extended:false}));
todoController(app);

app.listen(3000);
console.log('Listening on port 3000');