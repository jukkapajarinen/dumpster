const config = require('../config');
const crypto = require('crypto');
const jwt = require('jsonwebtoken');
const UserModel = require('../models/UserModel');

module.exports = class UserController {

  // Constructor is empty
  constructor() { }

  // Use all routes at once
  use(path, app) {
    this.getUser(path, app);
    this.updateUser(path, app);
    this.deleteUser(path, app);
  }

  // Creates md5 hash with salt
  createSaltedMd5(password, salt) {
    if (salt === undefined) salt = crypto.randomBytes(16).toString('hex');
    let hash = crypto.createHmac('sha512', salt);
    hash.update(password);
    return salt + ':' + hash.digest('hex');
  }

  // Read current user
  getUser(path, app) {
    app.get(path + '/users/current', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = { userid: decoded.userid };
            UserModel.find(search, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Update user
  updateUser(path, app) {
    app.put(path + '/users/:id', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err && req.body.password === req.body.password2) {
            let search = { userid: decoded.userid };
            let salted = this.createSaltedMd5(req.body.password);
            let data = {
              username: req.body.username,
              md5: salted,
              email: req.body.email
            };
            UserModel.update(search, data, (json) => res.send(json));
          } else {
            res.status(401).json();
          }
        });
      } else {
        res.status(401).json();
      }
    });
  }

  // Delete user
  deleteUser(path, app) {
    app.delete(path + '/users/:id', (req, res) => {
      if (req.headers.authorization !== undefined) {
        jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
          if (!err) {
            let search = { userid: decoded.userid };
            UserModel.delete(search, (json) => res.send(json));
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