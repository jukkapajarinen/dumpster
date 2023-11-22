import React, { Component } from 'react';
import { Link } from 'react-router-dom';
import Store from '../stores/AppStore';

class Navbar extends Component {
  toggleMenu() {
    this.props.store.set('menuOpen')(!this.props.store.get('menuOpen'));
  }

  logout(e) {
    e.preventDefault();
    localStorage.removeItem('TASKMAN_JWT');
    this.props.store.set('loggedIn')(false);
  }

  render() {
    return (
      <nav className="navbar navbar-expand-md navbar-dark bg-primary">
        <div className="container">
          <Link to="/" className="navbar-brand">Taskman</Link>
          <button className="navbar-toggler border-0" onClick={() => this.toggleMenu()}><span className="navbar-toggler-icon"></span></button>
          <div className={'navbar-collapse ' + (this.props.store.get('menuOpen') ? 'collapsed' : 'collapse')}>
            <ul className="navbar-nav mr-auto">
              {this.props.menuItems.left.map((link, id) => <li key={id} className="nav-item"><Link to={link.to} className="nav-link">{link.name}</Link></li>)}
            </ul>
            <ul className="navbar-nav">
              {this.props.menuItems.right.map((link, id) => (link.to === '/logout') ?
                <li key={id} className="nav-item"><a href={link.to} onClick={e => this.logout(e)} className="nav-link">{link.name}</a></li> :
                <li key={id} className="nav-item"><Link to={link.to} className="nav-link">{link.name}</Link></li>
              )}
            </ul>
          </div>
        </div>
      </nav>
    );
  }
}

export default Store.withStore(Navbar);
