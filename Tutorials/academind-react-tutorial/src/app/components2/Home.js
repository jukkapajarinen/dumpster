import React, { Component } from 'react';
import PropTypes from 'prop-types';

class Home extends Component {

  constructor(props) {
    super();
    this.state = {
      age: props.age,
      status: 0,
      homeLink: props.initialLinkName
    };
    setTimeout(() => {
      this.setState({
        status: 1
      });
    }, 3000);
    console.log("constructor");
  }

  componentWillMount() {
    console.log("componentwillmount");
  }

  componentDidMount() {
    console.log("componentdidmount");
  }

  componentWillReceiveProps(nextprops) {
    console.log("componentWillReceiveProps", nextprops);
  }

  shouldComponentUpdate(nextprops, nextstate) {
    console.log("shouldComponentUpdate" + nextprops + ":" + nextstate);
    return true;
  }

  componentWillUpdate(nextprops, nextstate) {
    console.log("shouldComponentUpdate" + nextprops + ":" + nextstate);
  }

  componentDidUpdate(prevprops, prevstate) {
    console.log("componentDidUpdate" + prevprops + ":" + prevstate);
  }

  componentWillUnmount() {
    console.log("componentWillUnmount");

  }

  onMakeMeYounger() {
    this.setState({
      age: this.state.age - 1
    });
  }

  onChangeLink() {
    this.props.changeLink(this.state.homeLink);
  }

  onHandleChange(e) {
    this.setState({
      homeLink: e.target.value
    })
  }

  render() {
    return (
      <div>
        <p>I'm a component!</p>
        <p>Your name is {this.props.name} and age is {this.state.age}</p>
        <p>Status: {this.state.status}</p>
        <button onClick={() => this.onMakeMeYounger()} className="btn btn-primary">Make me younger!</button>
        <hr/>
        <button onClick={this.props.greet} className="btn btn-primary">greet</button>
        <hr/>
        <button onClick={() => this.onChangeLink()} className="btn btn-primary">change header link</button>
        <hr/>
        <input type="text" value={this.state.homeLink} onChange={(e) => this.onHandleChange(e)}/>
        <button onClick={() => this.onChangeLink()} className="btn btn-primary">change header link</button>
      </div>
    );
  }
}

Home.PropTypes = {
  name: PropTypes.string,
  age: PropTypes.number,
  greet: PropTypes.func,
  changeLink: PropTypes.func,
  initialLinkName: PropTypes.string
};

export default Home;