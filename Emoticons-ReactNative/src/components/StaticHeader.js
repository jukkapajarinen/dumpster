import React, {Component} from 'react'
import {connect} from 'react-redux';
import {Share} from 'react-native';
import {Header, Left, Button, Icon, Body, Title, Right} from 'native-base';
import {openDrawer} from '../actions/GeneralActions';
import {StyleSheet as s} from '../StyleSheet';

class StaticHeader extends Component {
  render() {
    return (
      <Header androidStatusBarColor={s[this.props.primaryColor].statusBar.backgroundColor} style={s[this.props.primaryColor].navBar}>
        <Left>
          <Button transparent onPress={() => this.props.openDrawer()}>
            <Icon name="menu"/>
          </Button>
        </Left>
        <Body>
          <Title>Emoticons</Title>
        </Body>
        <Right>
          <Button transparent onPress={() => {
            Share.share(
              {message: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.emoticons'},
              {dialogTitle: 'Share this app!'})
            .then(res => console.log(res))
            .catch(err => console.log(err));
          }}>
            <Icon name='share' />
          </Button>
        </Right>
      </Header>
    );
  }
}

const mapStateToProps = state => ({
  primaryColor: state.Settings.primaryColor
});

const mapDispatchToProps = dispatch => ({
  openDrawer: () => dispatch(openDrawer())
});

export default connect(mapStateToProps, mapDispatchToProps)(StaticHeader);