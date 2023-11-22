import React, { Component } from 'react';
import Store from '../stores/AppStore';
import { fetchHelper } from '../helpers';

class MainView extends Component {
  componentDidMount() {
    fetchHelper('api/lists', localStorage.getItem('TASKMAN_JWT'), 'get')
      .then(json => {
        this.props.store.set('lists')(json);
        this.props.store.set('listActive')(json[0].id);
        fetchHelper('api/tasks', localStorage.getItem('TASKMAN_JWT'), 'get')
          .then(json => {
            this.props.store.set('tasks')(json);
            this.props.store.set('tasksActive')(json.filter(task => task.listid === this.props.store.get('listActive')));
          })
          .catch(() => this.props.store.set('tasks')([]));
      })
      .catch(() => this.props.store.set('lists')([]));
  }

  selectList(e) {
    e.preventDefault();
    this.props.store.set('listActive')(parseInt(e.target.id, 10));
    this.props.store.set('tasksActive')(this.props.store.get('tasks').filter(task => task.listid === parseInt(e.target.id, 10)));
  }

  addList(e) {
    e.preventDefault();
    fetchHelper('api/lists', localStorage.getItem('TASKMAN_JWT'), 'post', { userid: this.props.store.get('userId'), name: e.target.parentNode.parentNode.children[0].value, priority: 999 })
      .then(json => {
        let json2 = this.props.store.get('lists');
        json2.push(json);
        this.props.store.set('lists')(json2);
      })
      .catch(() => {});
  }

  addTask(e) {
    e.preventDefault();
    let body = {listid: this.props.store.get('listActive'), name: e.target.parentNode.parentNode.children[0].value, state: 0, priority: 0};
    fetchHelper('api/tasks', localStorage.getItem('TASKMAN_JWT'), 'post', body)
      .then(json => {
        let oldTasks = this.props.store.get('tasks');
        let oldTasksActive = this.props.store.get('tasksActive');
        oldTasks.push(json);
        oldTasksActive.push(json);
        this.props.store.set('tasks')(oldTasks);
        this.props.store.set('tasksActive')(oldTasksActive);
      })
      .catch(() => {});
  }

  checkTask() {
    console.log('checkTask');
  }

  removeTask(e) {
    e.preventDefault();
    console.log('removeTask', e.target.parentNode.id);
    fetchHelper('api/tasks/'+e.target.parentNode.id, localStorage.getItem('TASKMAN_JWT'), 'delete')
      .then(() => {
        let newTasks = this.props.store.get('tasks').filter(task => task.id !== parseInt(e.target.parentNode.id, 10));
        let newTasksActive = this.props.store.get('tasksActive').filter(task => task.id !== parseInt(e.target.parentNode.id, 10));
        console.log(newTasks);
        console.log(newTasksActive);
        this.props.store.set('tasks')(newTasks);
        this.props.store.set('tasksActive')(newTasksActive);
      })
      .catch(() => {});
  }

  removeCurrentList(e) {
    e.preventDefault();
    console.log('removeCurrentList');
    // this.props.store.set('lists')(this.props.store.get('lists').filter(task => task.id !== parseInt(e.target.parentNode.id, 10)));
    // this.props.store.set('listActive')(this.props.store.get('listActive').filter(task => task.id !== parseInt(e.target.parentNode.id, 10)));
    // this.props.store.set('tasks')(this.props.store.get('tasks').filter(task => task.id !== parseInt(e.target.parentNode.id, 10)));
    // this.props.store.set('tasksActive')(this.props.store.get('tasksActive').filter(task => task.id !== parseInt(e.target.parentNode.id, 10)));
  }

  render() {
    return (
      <main className="container">
        <div className="row mt-4 mb-4">
          <div className="col-md-4">
            <h2>Your lists</h2>
            <div className="list-group mb-4">
              {this.props.store.get('lists').map((list, id) =>
                <a key={id} id={list.id} href="/" onClick={e => this.selectList(e)} className={'list-group-item d-flex justify-content-between align-items-center' + (list.id === this.props.store.get('listActive') ? ' active' : '')}>
                  {list.name} <span className="badge badge-secondary badge-pill">{list.itemCount}</span>
                </a>
              )}
              <div className="list-group-item">
                <div className="input-group">
                  <input type="text" id="newList" className="form-control" placeholder="Type a name..." />
                  <div className="input-group-append">
                    <button onClick={e => this.addList(e)} className="btn btn-secondary" type="button">Add List</button>
                  </div>
                </div>
              </div>
            </div>
          </div>

          <div className="col-md-8">
            <h2>Tasks</h2>
            <ul className="list-group">
              {this.props.store.get('tasksActive').map((task, id) =>
                <li key={id} id={task.id} className="list-group-item d-flex justify-content-between align-items-center">
                  <div className="custom-control custom-checkbox">
                    <input onClick={e => this.checkTask(e)} type="checkbox" className="custom-control-input" id={'task-'+task-id} />
                    <label className="custom-control-label" htmlFor={'task-'+task.id}>{task.name}</label>
                  </div>
                  <button onClick={e => this.removeTask(e)} type="button" className="close">&times;</button>
                </li>
              )}
              <li className="list-group-item">
                <div className="input-group">
                  <input type="text" id="newTask" className="form-control" placeholder="Type a name..." />
                  <div className="input-group-append">
                    <button onClick={e => this.addTask(e)} className="btn btn-secondary" type="button">Add Task</button>
                  </div>
                </div>
              </li>
            </ul>
            <a href="/" onClick={e => this.removeCurrentList(e)}>Remove current list</a>
          </div>
        </div>
      </main>
    );
  }
}

export default Store.withStore(MainView);
