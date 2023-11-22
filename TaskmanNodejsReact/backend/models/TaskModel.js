const config = require('../config');
const mysql = require('mysql');

module.exports = class TaskModel {

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

  // Save new task
  static save(data, callback) {
    TaskModel.execQuery('INSERT INTO `Task` (`listId`, `userId`, `name`, `state`, `priority`) VALUES (?, ?, ?, ?, ?);', [data.listid, data.userid, data.name, data.state, data.priority])
      .then(rows => TaskModel.execQuery('SELECT * FROM `Task` WHERE `id` = ? LIMIT 1;', [rows.insertId]))
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Find one task
  static find(search, callback) {
    TaskModel.execQuery('SELECT * FROM `Task` WHERE `id` = ? AND `userId` = ? LIMIT 1;', [search.taskid, search.userid])
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Find all tasks
  static findAll(search, callback) {
    TaskModel.execQuery('SELECT * FROM `Task` WHERE `userId` = ?;', [search.userid])
      .then(rows => callback(rows))
      .catch(err => callback(err));
  }

  // Update task
  static update(search, data, callback) {
    TaskModel.execQuery('UPDATE `Task` SET `name` = ?, `priority` = ?, `state` = ? WHERE `id` = ? AND `userId` = ?;', [data.name, data.priority, data.state, search.taskid, search.userid])
      .then(() => TaskModel.execQuery('SELECT * FROM `Task` WHERE `id` = ? LIMIT 1;', [search.taskid]))
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }

  // Delete task
  static delete(search, callback) {
    TaskModel.execQuery('DELETE FROM `Task` WHERE `id` = ? AND `userId` = ?;', [search.taskid, search.userid])
      .then(rows => callback(rows[0]))
      .catch(err => callback(err));
  }
};