import React, {Component} from 'react';
import {connect} from 'react-redux';
import {BackHandler, Linking, View, Image, AsyncStorage} from 'react-native';
import Icon from 'react-native-vector-icons/MaterialCommunityIcons';
import {Container, Content, List, ListItem, Text, Separator} from 'native-base';
import {Actions} from 'react-native-router-flux';
import {closeDrawer} from '../actions/GeneralActions';
import {updateAdsRemoved} from '../actions/SettingsActions';
import {StyleSheet as s} from '../StyleSheet';

class DrawerContent extends Component {
  render() {
    return (
      <Container>
        <Content style={s[this.props.primaryColor].content}>
          <View style={s[this.props.primaryColor].drawerHeader}>
            <Image source={require('../assets/drawer_icon.png')}/>
            <Text style={s[this.props.primaryColor].drawerHeaderText}>Emoticons</Text>
          </View>

          <List>
            <Separator>
              <Text>Categories</Text>
            </Separator>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['home']({topCategory: 'recent'});}}>
              <Icon name="format-list-bulleted" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Recently used</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['home']({topCategory: 'positive'});}}>
              <Icon name="format-list-bulleted" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Positive emotions</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['home']({topCategory: 'negative'});}}>
              <Icon name="format-list-bulleted" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Negative emotions</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['home']({topCategory: 'neutral'});}}>
              <Icon name="format-list-bulleted" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Neutral emotions</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['home']({topCategory: 'actions'});}}>
              <Icon name="format-list-bulleted" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Various actions</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['home']({topCategory: 'animals'});}}>
              <Icon name="format-list-bulleted" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Animals</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['home']({topCategory: 'others'});}}>
              <Icon name="format-list-bulleted" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Others</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['home']({topCategory: 'western'});}}>
              <Icon name="format-list-bulleted" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Western style</Text>
            </ListItem>

            <Separator>
              <Text>Application</Text>
            </Separator>
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['settings']();}}>
              <Icon name="settings" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Settings</Text>
            </ListItem>
            {this.props.adsRemoved !== true ?
            <ListItem onPress={() => {this.props.closeDrawer(); Actions['settings']();}}>
              <Icon name="currency-usd-off" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Remove Ads ({this.props.adLocksOpened} / 3 <Icon name="lock-open" size={14} />)</Text>
            </ListItem> : null}
            <ListItem onPress={() => {this.props.closeDrawer(); Linking.openURL('https://play.google.com/store/apps/details?id=fi.jukkapajarinen.emoticons').catch(err => { });}}>
              <Icon name="star" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Rate this App</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); Linking.openURL('https://play.google.com/store/apps/developer?id=Jukka+Pajarinen').catch(err => { });}}>
              <Icon name="dots-horizontal" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>More Apps</Text>
            </ListItem>
            <ListItem onPress={() => {this.props.closeDrawer(); BackHandler.exitApp()}}>
              <Icon name="close" size={20} style={s[this.props.primaryColor].drawerListItemIcon}/>
              <Text>Exit</Text>
            </ListItem>
          </List>
        </Content>
      </Container>
    );
  }
}

const mapStateToProps = state => ({
  primaryColor: state.Settings.primaryColor,
  adsRemoved: state.Settings.adsRemoved,
  adLocksOpened: state.Settings.adLocksOpened
});

const mapDispatchToProps = dispatch => ({
  closeDrawer: () => dispatch(closeDrawer()),
  updateAdsRemoved: adsRemoved => dispatch(updateAdsRemoved(adsRemoved))
});

export default connect(mapStateToProps, mapDispatchToProps)(DrawerContent);