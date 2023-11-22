const initialState = {
  primaryColor: 'deepOrange',
  defaultCategory: 'positive',
  defaultAction: 'share',
  recent: {'Recently used': []},
  adLocksOpened: 0,
  adsRemoved: false
};

const SettingsReducer = (state = initialState, action) => {
  switch (action.type) {
    case 'PRIMARY_COLOR_UPDATE':
      return {...state, primaryColor: action.payload.primaryColor};
    case 'DEFAULT_CATEGORY_UPDATE':
      return {...state, defaultCategory: action.payload.defaultCategory};
    case 'DEFAULT_ACTION_UPDATE':
      return {...state, defaultAction: action.payload.defaultAction};
    case 'RECENT_UPDATE':
      return {...state, recent: action.payload.recent};
    case 'ADS_REMOVED_UPDATE':
      return {...state, adsRemoved: action.payload.adsRemoved};
    case 'AD_LOCKS_OPENED_UPDATE':
      return {...state, adLocksOpened: state.adLocksOpened + 1};
    case 'CLEAR_RECENTLY_USED':
      return {...state, recent: initialState.recent};
    case 'RESTORE_DEFAULTS':
      return {
        ...state,
        primaryColor: initialState.primaryColor,
        defaultCategory: initialState.defaultCategory,
        defaultAction: initialState.defaultAction,
        recent: initialState.recent
      };
    default:
      return state;
  }
};

export default SettingsReducer;
