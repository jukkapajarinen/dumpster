import React, { Component } from 'react';
import { BrowserRouter as Router, Switch, Route, Redirect } from 'react-router-dom';
import Store from '../stores/AppStore';
import Navbar from './Navbar';
import MainView from './MainView';
import LoginView from './LoginView';
import RegisterView from './RegisterView';
import UserView from './UserView';

class App extends Component {
  render() {
    return (
      <Router>
        <div className="page-wrapper">
          <Navbar menuItems={{
            'left': this.props.store.get('loggedIn') ? [{ 'to': '/', 'name': 'Home' }, { 'to': '/profile', 'name': 'Profile' }] : [],
            'right': this.props.store.get('loggedIn') ? [{ 'to': '/logout', 'name': 'Logout' }] : [{ 'to': '/register', 'name': 'Register' }, { 'to': '/login', 'name': 'Login' }]}} />
          <Switch>
            <Route exact path="/" component={this.props.store.get('loggedIn') ? MainView : LoginView} />
            <Route exact path="/profile" component={this.props.store.get('loggedIn') ? UserView : LoginView} />
            <Route exact path="/register" render={() => !this.props.store.get('loggedIn') ? <RegisterView /> : <Redirect to="/" />} />
            <Route exact path="/login" render={() => !this.props.store.get('loggedIn') ? <LoginView /> : <Redirect to="/" />} />
            <Route component={this.props.store.get('loggedIn') ? MainView : LoginView} />
          </Switch>
        </div>
      </Router>
    );
  }
}

export default Store.withStore(App);
