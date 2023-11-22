import React from "react";
import { render } from "react-dom";
import Header from './components2/Header';
import Home from './components2/Home';

class App extends React.Component {

  constructor() {
    super();
    this.state = {
      homeLink: "Home",
      homeMounted: true
    };
  }

  onGreet(){
    alert("hello");
  }

  onChangeLinkName(newName) {
    this.setState({
      homeLink: newName
    });
  }

  onChangeHomeMounted() {
    this.setState({
      homeMounted: !this.state.homeMounted
    });
  }

  render() {
    let homeCmp = "";
    if(this.state.homeMounted) {
      homeCmp = (
        <Home name={"jukka"} age={27} greet={this.onGreet} changeLink={(link) => this.onChangeLinkName(link)} initialLinkName={this.state.homeLink}>
          <p>child element</p>
        </Home>
      );
    }
    return (
      <div>
        <Header homeLink={this.state.homeLink} />
        <div className="container">
          <div className="row">
            <div className="col-xs-12">
              {homeCmp}
              <button onClick={() => this.onChangeHomeMounted()} className="btn btn-primary">(un)mount home comp</button>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

render(<App />, window.document.getElementById("app"));