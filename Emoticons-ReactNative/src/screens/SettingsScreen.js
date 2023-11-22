import React, {Component} from 'react';
import {connect} from 'react-redux';
import {AsyncStorage, ToastAndroid} from 'react-native';
import Icon from 'react-native-vector-icons/MaterialCommunityIcons';
import {Container, Content, Grid, Row, Col} from 'native-base';
import {Text, ListItem, Right, Switch, Picker, Item, Body} from 'native-base';
import StaticHeader from '../components/StaticHeader';
import {AdMobRewarded} from 'react-native-admob';
import {updatePrimaryColor, updateDefaultCategory, updateDefaultAction} from '../actions/SettingsActions';
import {updateAdsRemoved, updateAdLocksOpened, restoreDefaults, clearRecentlyUsed} from '../actions/SettingsActions';
import {StyleSheet as s} from '../StyleSheet';

AdMobRewarded.setAdUnitID('ca-app-pub-6773879736419389/3876181358');

class SettingsScreen extends Component {
  saveReduxToAsyncStorage(action, value) {
    switch(action) {
      case 'primaryColor':
        AsyncStorage.setItem('@EmoticonsStore:primaryColor', value);
        break;
      case 'defaultCategory':
        AsyncStorage.setItem('@EmoticonsStore:defaultCategory', value);
        break;
      case 'defaultAction':
        AsyncStorage.setItem('@EmoticonsStore:defaultAction', value);
        break;
      case 'clearRecentlyUsed':
        AsyncStorage.removeItem('@EmoticonsStore:recentArr');
        break;
      case 'restoreDefaults':
        AsyncStorage.removeItem('@EmoticonsStore:primaryColor');
        AsyncStorage.removeItem('@EmoticonsStore:defaultCategory');
        AsyncStorage.removeItem('@EmoticonsStore:defaultAction');
        AsyncStorage.removeItem('@EmoticonsStore:recentArr');
        break;
      case 'adsRemoved':
        AsyncStorage.setItem('@EmoticonsStore:adsRemoved', value);
        break;
    }
  }

  render() {
    return (
      <Container>
        <StaticHeader/>
        <Content style={s[this.props.primaryColor].content}>
          <ListItem itemHeader>
            <Text>Preferences</Text>
          </ListItem>
          <ListItem>
            <Body>
              <Picker
                prompt='Primary color'
                selectedValue={this.props.primaryColor}
                onValueChange={(value) => {
                  this.props.updatePrimaryColor(value);
                  this.saveReduxToAsyncStorage('primaryColor', value)}}>
                <Item label='Red' value={'red'} />
                <Item label='Pink' value={'pink'} />
                <Item label='Purple' value={'purple'} />
                <Item label='Deep Purple' value={'deepPurple'} />
                <Item label='Indigo' value={'indigo'} />
                <Item label='Blue' value={'blue'} />
                <Item label='Light blue' value={'lightBlue'} />
                <Item label='Cyan' value={'cyan'} />
                <Item label='Teal' value={'teal'} />
                <Item label='Green' value={'green'} />
                <Item label='Light Green' value={'lightGreen'} />
                <Item label='Lime' value={'lime'} />
                <Item label='Yellow' value={'yellow'} />
                <Item label='Amber' value={'amber'} />
                <Item label='Orange' value={'orange'} />
                <Item label='Deep Orange' value={'deepOrange'} />
                <Item label='Brown' value={'brown'} />
                <Item label='Grey' value={'grey'} />
                <Item label='Blue Grey' value={'blueGrey'} />
              </Picker>
            </Body>
          </ListItem>
          <ListItem>
            <Body>
              <Picker
                prompt='Default category'
                selectedValue={this.props.defaultCategory}
                onValueChange={(value) => {
                  this.props.updateDefaultCategory(value);
                  this.saveReduxToAsyncStorage('defaultCategory', value)}}>
                <Item label="Recently used" value={'recent'} />
                <Item label="Positive emotions" value={'positive'} />
                <Item label="Negative emotions" value={'negative'} />
                <Item label="Neutral emotions" value={'neutral'} />
                <Item label="Various actions" value={'actions'} />
                <Item label="Animals" value={'animals'} />
                <Item label="Others" value={'others'} />
                <Item label="Western style" value={'western'} />
              </Picker>
            </Body>
          </ListItem>
          <ListItem>
            <Body>
              <Picker
                prompt='Default action'
                selectedValue={this.props.defaultAction}
                onValueChange={(value) => {
                  this.props.updateDefaultAction(value);
                  this.saveReduxToAsyncStorage('defaultAction', value)}} >
                <Item label="Share" value={'share'} />
                <Item label="Clipboard" value={'clipboard'} />
              </Picker>
            </Body>
          </ListItem>

          <ListItem itemHeader>
            <Text>Actions</Text>
          </ListItem>
          <ListItem button onPress={() => {
            ToastAndroid.show('Action performed', ToastAndroid.SHORT);
            this.props.clearRecentlyUsed();
            this.saveReduxToAsyncStorage('clearRecentlyUsed')}}>
            <Body>
              <Text>Clear recently used</Text>
            </Body>
            <Right>
              <Icon name="delete" size={20} />
            </Right>
          </ListItem>
          <ListItem button onPress={() => {
            ToastAndroid.show('Action performed', ToastAndroid.SHORT);
            this.props.restoreDefaults();
            this.saveReduxToAsyncStorage('restoreDefaults')}}>
            <Body>
              <Text>Restore default settings</Text>
            </Body>
            <Right>
              <Icon name="undo" size={20} />
            </Right>
          </ListItem>
          {this.props.adsRemoved !== true ?
          <ListItem button onPress={() => {
            AdMobRewarded.requestAd(AdMobRewarded.showAd);
            AdMobRewarded.addEventListener('rewardedVideoDidRewardUser', () => {
              this.props.updateAdLocksOpened();
              if(this.props.adLocksOpened >= 3) {
                ToastAndroid.show('Removed ads from app!', ToastAndroid.SHORT);
                this.props.updateAdsRemoved(true);
                this.saveReduxToAsyncStorage('adsRemoved', true);
              }
            });
          }}>
            <Body>
              <Text>Remove Ads ({this.props.adLocksOpened} / 3 <Icon name="lock-open" size={14} />)</Text>
            </Body>
            <Right>
              <Icon name="currency-usd-off" size={20} />
            </Right>
          </ListItem> : null}
        </Content>
      </Container>
    );
  }
}

const mapStateToProps = state => ({
  primaryColor: state.Settings.primaryColor,
  defaultCategory: state.Settings.defaultCategory,
  defaultAction: state.Settings.defaultAction,
  adLocksOpened: state.Settings.adLocksOpened,
  adsRemoved: state.Settings.adsRemoved
});

const mapDispatchToProps = dispatch => ({
  updatePrimaryColor: primaryColor => dispatch(updatePrimaryColor(primaryColor)),
  updateDefaultCategory: defaultCategory => dispatch(updateDefaultCategory(defaultCategory)),
  updateDefaultAction: defaultAction => dispatch(updateDefaultAction(defaultAction)),
  updateAdLocksOpened: () => dispatch(updateAdLocksOpened()),
  updateAdsRemoved: adsRemoved => dispatch(updateAdsRemoved(adsRemoved)),
  clearRecentlyUsed: () => dispatch(clearRecentlyUsed()),
  restoreDefaults: () => dispatch(restoreDefaults())
});

export default connect(mapStateToProps, mapDispatchToProps)(SettingsScreen);