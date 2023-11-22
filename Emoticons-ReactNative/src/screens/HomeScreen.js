import React, {Component} from 'react';
import {connect} from 'react-redux';
import {Share, AsyncStorage, ToastAndroid, Clipboard} from 'react-native';
import {Container, Content, Grid, Row, Col, Footer} from 'native-base';
import {Text, Card, CardItem, ListItem, Spinner} from 'native-base';
import {AdMobBanner, AdMobInterstitial} from 'react-native-admob';
import StaticHeader from '../components/StaticHeader';
import {EMOTICONS} from  '../Const';
import {updateRecent} from '../actions/SettingsActions';
import {StyleSheet as s} from '../StyleSheet';

AdMobInterstitial.setAdUnitID('ca-app-pub-6773879736419389/2458323751');

class HomeScreen extends Component {
  constructor(props) {
    super(props);
    this.handleEmoticonPress = this.handleEmoticonPress.bind(this);
    if(this.props.adsRemoved !== true) {
      AdMobInterstitial.requestAd(AdMobInterstitial.showAd);
    }
  }

  handleEmoticonPress(emoticon) {
    let recentArr = this.props.recent['Recently used'];
    if(!recentArr.includes(emoticon)) {
      recentArr.unshift(emoticon);
      recentArr = recentArr.slice(0, 16);
      AsyncStorage.setItem('@EmoticonsStore:recentArr', JSON.stringify(recentArr));
      this.props.updateRecent({'Recently used': recentArr});
    }
    if(this.props.defaultAction === 'clipboard') {
      ToastAndroid.show('Copied to clipboard', ToastAndroid.SHORT);
      Clipboard.setString(emoticon);
    } else {
      Share.share({message: emoticon}, {dialogTitle: emoticon})
      .then(res => console.log(res))
      .catch(err => console.log(err));
    }
  }

  generateListJSX() {
    let topCategory = this.props.topCategory !== undefined ? this.props.topCategory : this.props.defaultCategory;
    let emoticons = topCategory === 'recent' ? this.props.recent : EMOTICONS[topCategory];
    let jsx = [];
    for(let i=0 ; i<Object.keys(emoticons).length ; i++) {
      let category = Object.keys(emoticons)[i];
      jsx.push(
        <Row key={'headerRow'+i}>
          <Col>
            <Text style={s[this.props.primaryColor].headerRow}>{category}</Text>
          </Col>
        </Row>
      );
      if(emoticons[category].length <= 0) {
        jsx.push(
          <Row key={'emptyRow'+i}>
            <Col>
              <Text style={s[this.props.primaryColor].emptyRow}>Category is empty.</Text>
            </Col>
          </Row>
        )
      }
      for(let j=0 ; j<emoticons[category].length ; j+=2) {
        jsx.push(
          <Row key={'itemRow'+i+j}>
            <Col>
              <Card>
                <CardItem button onPress={() => this.handleEmoticonPress(emoticons[category][j])} style={s[this.props.primaryColor].itemRow}>
                  <Text style={emoticons[category][j].length > 16 ? {fontSize: 12} : null}>{emoticons[category][j]}</Text>
                </CardItem>
              </Card>
            </Col>
            <Col>
              {emoticons[category][j+1] !== undefined ?
                <Card>
                  <CardItem button onPress={() => this.handleEmoticonPress(emoticons[category][j+1])}  style={s[this.props.primaryColor].itemRow}>
                    <Text style={emoticons[category][j+1].length > 16 ? {fontSize: 12} : null}>{emoticons[category][j+1]}</Text>
                  </CardItem>
                </Card>
                : null}
            </Col>
          </Row>
        );
      }
    }
    return jsx;
  }

  render() {
    const jsx = this.generateListJSX();
    return (
      <Container>
        <StaticHeader/>
        <Content style={s[this.props.primaryColor].homeContent}>
          <Grid>
            {jsx}
          </Grid>
        </Content>
        {this.props.adsRemoved !== true ?
        <Footer style={s[this.props.primaryColor].footer}>
          <AdMobBanner bannerSize='smartBannerPortrait' adUnitID='ca-app-pub-6773879736419389/9981590551'/>
        </Footer> : null}
      </Container>
    );
  }
}

const mapStateToProps = state => ({
  primaryColor: state.Settings.primaryColor,
  defaultCategory: state.Settings.defaultCategory,
  defaultAction: state.Settings.defaultAction,
  recent: state.Settings.recent,
  adsRemoved: state.Settings.adsRemoved
});

const mapDispatchToProps = dispatch => ({
  updateRecent: recentObj => dispatch(updateRecent(recentObj))
});

export default connect(mapStateToProps, mapDispatchToProps)(HomeScreen);
