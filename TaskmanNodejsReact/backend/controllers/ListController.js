const config = require('../config');
const jwt = require('jsonwebtoken');
const ListModel = require('../models/ListModel');

module.exports = class ListController {

  // Constructor is empty
  constructor() { }

  // Use all routes at once
  use(path, app) {
    this.addList(path, app);
    this.getList(path, app);
    this.getLists(path, app);
    this.updateList(path, app);
    this.deleteList(path, app);
  }

  // Add new list
  addList(path, app) {
    app.post(path + '/lists', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let data = {
              userid: decoded.userid,
              name: req.body.name,
              priority: req.body.priority
            };
            ListModel.save(data, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Read list by user
  getList(path, app) {
    app.get(path + '/lists/:id', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = {
              listid: req.params.id,
              userid: decoded.userid
            };
            ListModel.find(search, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Read all lists by user
  getLists(path, app) {
    app.get(path + '/lists', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = { userid: decoded.userid };
            ListModel.findAll(search, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Update list
  updateList(path, app) {
    app.put(path + '/lists/:id', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = {
              listid: req.params.id,
              userid: decoded.userid
            };
            let data = {
              name: req.body.name,
              priority: req.body.priority
            };
            ListModel.update(search, data, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Delete list
  deleteList(path, app) {
    app.delete(path + '/lists/:id', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = {
              listid: req.params.id,
              userid: decoded.userid
            };
            ListModel.delete(search, (json) => res.send(json));
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