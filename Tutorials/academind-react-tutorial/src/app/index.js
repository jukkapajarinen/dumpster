import React from "react";
import {render} from "react-dom";
import {BrowserRouter as Router, Switch, Route} from "react-router-dom";
import Root from './components/Root';
import Home from './components/Home';
import User from './components/User';

class App extends React.Component {
  render() {
    return (
      <Router>
        <Root>
          <Switch>
            <Route exact path="/" component={Home} />
            <Route path="/user/:id" component={User} />
            <Route path="/home" component={Home} />
          </Switch>
        </Root>
      </Router>
    );
  }
}

render(<App />, window.document.getElementById("app"));