const config = require('../config');
const jwt = require('jsonwebtoken');
const TaskModel = require('../models/TaskModel');

module.exports = class TaskController {

  // Constructor is empty
  constructor() { }

  // Use all routes at once
  use(path, app) {
    this.addTask(path, app);
    this.getTask(path, app);
    this.getTasks(path, app);
    this.updateTask(path, app);
    this.deleteTask(path, app);
  }

  // Add new task
  addTask(path, app) {
    app.post(path + '/tasks', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let data = {
              userid: decoded.userid,
              listid: req.body.listid,
              name: req.body.name,
              state: req.body.state,
              priority: req.body.priority
            };
            TaskModel.save(data, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Read one task by user
  getTask(path, app) {
    app.get(path + '/tasks/:id', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = {
              taskid: req.params.id,
              userid: decoded.userid
            };
            TaskModel.find(search, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Read all tasks by user
  getTasks(path, app) {
    app.get(path + '/tasks', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = { userid: decoded.userid };
            TaskModel.findAll(search, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Update task
  updateTask(path, app) {
    app.put(path + '/tasks/:id', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = {
              taskid: req.params.id,
              userid: decoded.userid
            };
            let data = {
              name: req.body.name,
              state: req.body.state,
              priority: req.body.priority
            };
            TaskModel.update(search, data, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Delete task
  deleteTask(path, app) {
    app.delete(path + '/tasks/:id', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = {
              taskid: req.params.id,
              userid: decoded.userid
            };
            TaskModel.delete(search, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }
};