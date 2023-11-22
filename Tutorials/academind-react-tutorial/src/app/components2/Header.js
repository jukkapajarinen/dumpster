import React, { Component } from 'react';

const Header = (props) => {
  return (
    <nav className="navbar navbar-light bg-light">
      <div className="container">
        <div className="navbar-collapse">
          <ul className="navbar-nav">
            <li className="nav-item"><a href="#">{props.homeLink}</a></li>
          </ul>
        </div>
      </div>
    </nav>
  );
}

export default Header;