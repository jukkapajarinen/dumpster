import React, { Component } from 'react';

class RegisterView extends Component {
  register(e) {
    e.preventDefault();
    console.log('register');
  }

  render() {
    return (
      <main className="container">
        <div className="row mt-4 mb-4">
          <div className="col-md-12">
            <h2>Register a new user</h2>
            <form>
              <div className="form-group">
                <input type="text" className="form-control" placeholder="Username" title="Username" />
              </div>
              <div className="form-group">
                <input type="email" className="form-control" placeholder="Email" title="Email" />
              </div>
              <div className="form-group">
                <input type="password" className="form-control" placeholder="Password" title="Password" />
              </div>
              <div className="form-group">
                <input type="password" className="form-control" placeholder="Password again" title="Password again" />
              </div>
              <div className="form-group">
                <button onClick={e => this.register(e)} type="submit" className="btn btn-secondary btn-block">Register</button>
              </div>
            </form>
          </div>
        </div>
      </main>
    );
  }
}

export default RegisterView;
