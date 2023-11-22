const crypto = require('crypto');
const config = require('../config');
const jwt = require('jsonwebtoken');
const UserModel = require('../models/UserModel');

module.exports = class AuthController {

  // Constructor is empty
  constructor() { }

  // Use all routes at once
  use(path, app) {
    this.register(path, app);
    this.login(path, app);
    this.renew(path, app);
  }

  // Creates md5 hash with salt
  createSaltedMd5(password, salt) {
    if (salt === undefined) salt = crypto.randomBytes(16).toString('hex');
    let hash = crypto.createHmac('sha512', salt);
    hash.update(password);
    return salt + ':' + hash.digest('hex');
  }

  // Register to REST API
  register(path, app) {
    app.post(path + '/register', (req, res) => {
      if (req.body.password === req.body.password2) {
        let salted = this.createSaltedMd5(req.body.password);
        let data = {
          username: req.body.username,
          md5: salted,
          email: req.body.email
        };
        UserModel.save(data, (json) => {
          let token = jwt.sign({
            exp: Math.floor(Date.now() / 1000) + (60 * 60),
            iat: Math.floor(Date.now() / 1000),
            userid: json.id
          }, config.jwtSecret);
          res.status(200).json({ token: token });
        });
      } else {
        res.status(400).json();
      }
    });
  }

  // Login to REST API
  login(path, app) {
    app.post(path + '/login', (req, res) => {
      let search = { username: req.body.username };
      UserModel.findByName(search, (json) => {
        if (json.md5 !== undefined && this.createSaltedMd5(req.body.password, json.md5.split(':')[0]) === json.md5) {
          let token = jwt.sign({
            exp: Math.floor(Date.now() / 1000) + (60 * 60),
            iat: Math.floor(Date.now() / 1000),
            userid: json.id
          }, config.jwtSecret);
          res.status(200).json({ token: token });
        } else {
          res.status(401).json();
        }
      });
    });
  }

  // Renew JWT token
  renew(path, app) {
    app.post(path + '/renew', (req, res) => {
      jwt.verify(req.headers.authorization.split(' ')[1], config.jwtSecret, (err, decoded) => {
        if (!err) {
          let newToken = jwt.sign({
            exp: Math.floor(Date.now() / 1000) + (60 * 60),
            iat: Math.floor(Date.now() / 1000),
            userid: decoded.userid
          }, config.jwtSecret);
          res.status(200).json({ token: newToken });
        } else {
          res.status(401).json();
        }
      });
    });
  }
};