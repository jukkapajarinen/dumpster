import React, {Component} from 'react';
import {connect} from 'react-redux';
import {Router, Scene} from 'react-native-router-flux';
import {AsyncStorage} from 'react-native';
import {Drawer} from 'native-base';
import {closeDrawer} from './actions/GeneralActions';
import {updatePrimaryColor, updateDefaultCategory, updateDefaultAction} from './actions/SettingsActions';
import {updateRecent, updateAdsRemoved} from './actions/SettingsActions';
import DrawerContent from './components/DrawerContent';
import HomeScreen from './screens/HomeScreen';
import SettingsScreen from './screens/SettingsScreen';

const RouterWithRedux = connect()(Router);

class App extends Component {
  constructor(props) {
    super(props);
    this.loadAsyncStorageToRedux();
  }

  loadAsyncStorageToRedux() {
    AsyncStorage.getItem('@EmoticonsStore:primaryColor')
    .then(value => value !== null ? this.props.updatePrimaryColor(value) : null)
    .catch(error => {console.log('ERROR @EmoticonsStore:primaryColor', error)});

    AsyncStorage.getItem('@EmoticonsStore:defaultCategory')
    .then(value => value !== null ? this.props.updateDefaultCategory(value) : null)
    .catch(error => {console.log('ERROR @EmoticonsStore:defaultCategory', error)});

    AsyncStorage.getItem('@EmoticonsStore:defaultAction')
    .then(value => value !== null ? this.props.updateDefaultAction(value) : null)
    .catch(error => {console.log('ERROR @EmoticonsStore:defaultAction', error)});

    AsyncStorage.getItem('@EmoticonsStore:recentArr')
    .then(value => value !== null ? this.props.updateRecent({'Recently used': JSON.parse(value)}) : null)
    .catch(error => {console.log('ERROR @EmoticonsStore:recentArr', error)});

    AsyncStorage.getItem('@EmoticonsStore:adsRemoved')
    .then(value => value !== null ? this.props.updateAdsRemoved(value) : null)
    .catch(error => {console.log('ERROR @EmoticonsStore:adsRemoved', error)});
  }

  render() {
    return (
      <Drawer
        content={<DrawerContent/>}
        open={this.props.drawerState === 'opened'}
        onClose={() => this.props.closeDrawer()}>
        <RouterWithRedux>
          <Scene key="root">
            <Scene key="home" component={HomeScreen} initial hideNavBar/>
            <Scene key="settings" component={SettingsScreen} hideNavBar/>
          </Scene>
        </RouterWithRedux>
      </Drawer>
    );
  }
}

const mapStateToProps = state => ({
  drawerState: state.General.drawerState,
  adsRemoved: state.Settings.adsRemoved
});

const mapDispatchToProps = dispatch => ({
  closeDrawer: () => dispatch(closeDrawer()),
  updatePrimaryColor: primaryColor => dispatch(updatePrimaryColor(primaryColor)),
  updateDefaultCategory: defaultCategory => dispatch(updateDefaultCategory(defaultCategory)),
  updateDefaultAction: defaultAction => dispatch(updateDefaultAction(defaultAction)),
  updateRecent: recentObj => dispatch(updateRecent(recentObj)),
  updateAdsRemoved: adsRemoved => dispatch(updateAdsRemoved(adsRemoved))
});

export default connect(mapStateToProps, mapDispatchToProps)(App);