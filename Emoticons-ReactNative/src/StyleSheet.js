let getStyleSheet = (primary, secondary) => {
  return {
    content: {backgroundColor: '#eeeeee'},
    drawerHeader: {backgroundColor: primary, flex: 1, flexDirection: 'row', alignItems: 'center'},
    drawerHeaderText: {color: '#ffffff', fontSize: 18, fontWeight: 'bold', paddingLeft: 10},
    drawerListItemIcon: {paddingRight: 15},
    navBar: {backgroundColor: primary},
    statusBar: {backgroundColor: secondary},
    headerRow: {paddingTop: 15, color: primary, fontSize: 14},
    emptyRow: {color: '#848284', fontSize: 14},
    itemRow: {flex: 1, justifyContent: 'center', alignItems: 'center'},
    homeContent: {backgroundColor: '#eeeeee', paddingHorizontal: 15, paddingBottom: 15},
    footer: {backgroundColor: primary, height: 'auto'}
  }
};

export const StyleSheet = {
  red: getStyleSheet('#F44336', '#C62828'),
  pink: getStyleSheet('#E91E63', '#AD1457'),
  purple: getStyleSheet('#9C27B0', '#6A1B9A'),
  deepPurple: getStyleSheet('#673AB7', '#4527A0'),
  indigo: getStyleSheet('#3F51B5', '#283593'),
  blue: getStyleSheet('#2196F3', '#1565C0'),
  lightBlue: getStyleSheet('#03A9F4', '#0277BD'),
  cyan: getStyleSheet('#00BCD4', '#00838F'),
  teal: getStyleSheet('#009688', '#00695C'),
  green: getStyleSheet('#4CAF50', '#2E7D32'),
  lightGreen: getStyleSheet('#8BC34A', '#558B2F'),
  lime: getStyleSheet('#CDDC39', '#9E9D24'),
  yellow: getStyleSheet('#FFEB3B', '#F9A825'),
  amber: getStyleSheet('#FFC107', '#FF8F00'),
  orange: getStyleSheet('#FF9800', '#EF6C00'),
  deepOrange: getStyleSheet('#ff5722', '#D84315'),
  brown: getStyleSheet('#795548', '#4E342E'),
  grey: getStyleSheet('#9E9E9E', '#424242'),
  blueGrey: getStyleSheet('#607D8B', '#37474F'),
};