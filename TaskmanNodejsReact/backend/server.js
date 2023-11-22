const config = require('./config');
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');
const bodyparser = require('body-parser');
const AuthController = require('./controllers/AuthController');
const TaskController = require('./controllers/TaskController');
const ListController = require('./controllers/ListController');
const UserController = require('./controllers/UserController');

// Init express app
let app = new express();

// Init custom controllers
let auth = new AuthController();
let task = new TaskController();
let list = new ListController();
let user = new UserController();

// Set up middleware
app.use('/', express.static('public'));
app.use(cors());
app.use(helmet());
app.use(morgan('combined'));
app.use(bodyparser.json({ type: 'application/json' }));
auth.use('/api', app);
task.use('/api', app);
list.use('/api', app);
user.use('/api', app);

// Start listening HTTP
app.listen(config.port, () => console.log('Listening at port:' + config.port));
