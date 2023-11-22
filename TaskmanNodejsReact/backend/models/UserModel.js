const config = require('../config');
const mysql = require('mysql');

module.exports = class UserModel {

  // Promise for easier async programming
  static execQuery(sql, params) {
    return new Promise((resolve, reject) => {
      let conn = mysql.createConnection(config.mysql);
      conn.query(sql, params, (err, rows) => {
        conn.end();
        if (err) {
          reject(err);
        } else {
          resolve(rows);
        }
      });
    });
  }

  // Save new user (used for registration)
  static save(data, callback) {
    UserModel.execQuery('INSERT INTO `User` (`username`, `md5`, `email`) VALUES (?, ?, ?);', [data.username, data.md5, data.email])
      .then(rows => UserModel.execQuery('SELECT `id`, `username`, `email` FROM `User` WHERE `id` = ? LIMIT 1;', [rows.insertId]))
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Find one user
  static find(search, callback) {
    UserModel.execQuery('SELECT `id`, `username`, `email` FROM `User` WHERE `id` = ? LIMIT 1;', [search.userid])
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Find one user by username
  static findByName(search, callback) {
    UserModel.execQuery('SELECT * FROM `User` WHERE `username` = ? LIMIT 1;', [search.username])
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Find all users (not allowed)
  static findAll(search, callback) {
    this.find(search, callback);
  }

  // Update user
  static update(search, data, callback) {
    UserModel.execQuery('UPDATE `User` SET `username` = ?, `md5` = ?, `email` = ? WHERE `id` = ?;', [data.username, data.md5, data.email, search.userid])
      .then(() => UserModel.execQuery('SELECT `id`, `username`, `email` FROM `User` WHERE `id` = ? LIMIT 1;', [search.userid]))
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Delete user
  static delete(search, callback) {
    UserModel.execQuery('DELETE FROM `User` WHERE `id` = ?;', [search.userid])
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }
};