import React, { Component } from 'react';
import PropTypes from 'prop-types';

class User extends Component {
  onNavigateHome() {
    this.props.history.push("/home");
  }

  render() {
    return (
      <div>
        <h1>User component</h1>
        <p>Hello {this.props.username} from User component!</p>
        <button onClick={() => this.props.changeUsername("kati")} className="btn btn-primary">Change name to Kati</button>
        <hr/>
        <button onClick={() => this.onNavigateHome()} className="btn btn-primary">Go Home!</button>
      </div>
    );
  }
}

export default User;