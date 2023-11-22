import React, { Component } from 'react';
import PropTypes from 'prop-types';
import Header from './Header';

class Root extends Component {
  render() {
    return (
      <div className="container">
        <Header/>
        {this.props.children}
      </div>
    );
  }
}

export default Root;