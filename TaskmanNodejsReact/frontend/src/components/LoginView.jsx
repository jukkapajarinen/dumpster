import React, { Component } from 'react';
import Store from '../stores/AppStore';
import { fetchHelper } from '../helpers';

class LoginView extends Component {
  login(e) {
    e.preventDefault();
    fetchHelper('api/login', undefined, 'post', {'username': e.target.login_username.value, 'password': e.target.login_password.value})
      .then(json => {
        localStorage.setItem('TASKMAN_JWT', json.token);
        this.props.store.set('loggedIn')(true);
        fetchHelper('api/users/current', json.token, 'get')
          .then(json => {
            this.props.store.set('username')(json.username);
            this.props.store.set('userId')(json.id);
            this.props.store.set('email')(json.email);
          })
          .catch(() => {
            localStorage.removeItem('TASKMAN_JWT');
            this.props.store.set('loggedIn')(false);
          });
      })
      .catch(() => {
        localStorage.removeItem('TASKMAN_JWT');
        this.props.store.set('loggedIn')(false);
      });
  }

  render() {
    return (
      <main className="container">
        <div className="row mt-4 mb-4">
          <div className="col-md-12">
            <form onSubmit={e => this.login(e)}>
              <div className="form-group">
                <input name="login_username" type="text" className="form-control" placeholder="Username" />
              </div>
              <div className="form-group">
                <input name="login_password" type="password" className="form-control" placeholder="Password" />
              </div>
              <div className="form-group">
                <button type="submit" className="btn btn-secondary btn-block">Login</button>
              </div>
            </form>
          </div>
        </div>
      </main>
    );
  }
}

export default Store.withStore(LoginView);
