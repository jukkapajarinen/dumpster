import React, { Component } from 'react';
import PropTypes from 'prop-types';

class User extends Component {
  onNavigateHome() {
    this.props.history.push("/home");
  }

  render() {
    console.log(this.props);
    return (
      <div>
        <h1>User component</h1>
        <p>Hello {this.props.match.params.id} from User component!</p>
        <button onClick={() => this.onNavigateHome()} className="btn btn-primary">Go Home!</button>
      </div>
    );
  }
}

export default User;