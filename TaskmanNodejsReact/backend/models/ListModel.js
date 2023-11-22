const config = require('../config');
const mysql = require('mysql');

module.exports = class ListModel {

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

  // Save new list
  static save(data, callback) {
    ListModel.execQuery('INSERT INTO `List` (`userId`, `name`, `priority`) VALUES (?, ?, ?);', [data.userid, data.name, data.priority])
      .then(rows => ListModel.execQuery('SELECT * FROM `List` WHERE `id` = ? LIMIT 1;', [rows.insertId]))
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Find one list
  static find(search, callback) {
    ListModel.execQuery('SELECT * FROM `List` WHERE `id` = ? AND `userId` = ? LIMIT 1;', [search.listid, search.userid])
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Find all lists
  static findAll(search, callback) {
    ListModel.execQuery('SELECT * FROM `List` WHERE `userId` = ?;', [search.userid])
      .then(rows => callback(rows))
      .catch(err => callback(err));
  }

  // Update list
  static update(search, data, callback) {
    ListModel.execQuery('UPDATE `List` SET `name` = ?, `priority` = ? WHERE `id` = ? AND `userId` = ?;', [data.name, data.priority, search.listid, search.userid])
      .then(() => ListModel.execQuery('SELECT * FROM `List` WHERE `id` = ? LIMIT 1;', [search.listid]))
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Delete list
  static delete(search, callback) {
    ListModel.execQuery('DELETE FROM `List` WHERE id = ? AND userId = ?;', [search.listid, search.userid])
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }
};