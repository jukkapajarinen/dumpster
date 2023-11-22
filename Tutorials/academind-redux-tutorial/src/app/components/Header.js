import React, { Component } from 'react';
import PropTypes from 'prop-types';
import {NavLink as Link} from "react-router-dom";

class Header extends Component {
  render() {
    return (
      <nav className="navbar navbar-expand-lg navbar-dark bg-dark">
        <div className="navbar-collapse">
          <ul className="navbar-nav">
            <li className="nav-item"><Link className="nav-link" to="/home" activeClassName="active">Home</Link></li>
            <li className="nav-item"><Link className="nav-link" to="/user/jukka" activeClassName="active">User</Link></li>
          </ul>
        </div>
      </nav>
    );
  }
}

export default Header;