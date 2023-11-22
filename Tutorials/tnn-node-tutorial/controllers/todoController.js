var mongoose = require('mongoose');

mongoose.connect('mongodb://test:test@127.0.0.1:27017/todos');
var todoSchema = new mongoose.Schema({item: String});
var Todo = mongoose.model('Todo', todoSchema);

module.exports = function(app) {
  app.get('/todo', function(req, res) {
    Todo.find({}, function(err, data) {
      if(err) throw err;
      res.render('todo', {todos: data});
    });
  });

  app.post('/todo', function(req, res) {
    var newTodo = Todo({item: req.body.item}).save(function(err, data) {
      if(!err)
        res.status(200).send();
      else
        throw err;
    });

  });

  app.delete('/todo/:id', function(req, res) {
    Todo.find({}, function(err, data){
      Todo.find({_id: data[req.params.id].id}).remove(function(err, data){
        if(!err)
          res.status(200).send();
        else
          throw err;
      });
    });
  });
};