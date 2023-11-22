import React from "react";
import {connect} from 'react-redux';
import {BrowserRouter as Router, Switch, Route} from "react-router-dom";
import Root from '../components/Root';
import Home from '../components/Home';
import User from '../components/User';
import {setName} from '../actions/userActions';

class App extends React.Component {
  render() {
    return (
      <Router>
        <Root>
          <Switch>
            <Route exact path="/" render={() => <Home />} />
            <Route path="/user/:id" render={(routeProps) => <User {...routeProps} username={this.props.user.name} changeUsername={(name) => this.props.setName(name)} />} />
            <Route path="/home" render={() => <Home />} />
          </Switch>
        </Root>
      </Router>
    );
  }
}

const mapStateToProps = (state) => {
  return {
    user: state.userReducer,
    math: state.mathReducer
  };
}

const mapDispatchToProps = (dispatch) => {
  return {
    setName: (name) => dispatch(setName(name))
  };
}

export default connect(mapStateToProps, mapDispatchToProps)(App);