export const updatePrimaryColor = (primaryColor) => {
  return {
    type: 'PRIMARY_COLOR_UPDATE',
    payload: {'primaryColor': primaryColor}
  };
}

export const updateDefaultCategory = (defaultCategory) => {
  return {
    type: 'DEFAULT_CATEGORY_UPDATE',
    payload: {'defaultCategory': defaultCategory}
  };
}

export const updateDefaultAction = (defaultAction) => {
  return {
    type: 'DEFAULT_ACTION_UPDATE',
    payload: {'defaultAction': defaultAction}
  };
}

export const updateRecent = (recentObj) => {
  return {
    type: 'RECENT_UPDATE',
    payload: {'recent': recentObj}
  };
}

export const updateAdsRemoved = (adsRemoved) => {
  return {
    type: 'ADS_REMOVED_UPDATE',
    payload: {
      'adsRemoved': adsRemoved
    }
  };
}

export const updateAdLocksOpened = () => {
  return {
    type: 'AD_LOCKS_OPENED_UPDATE'
  };
}

export const clearRecentlyUsed = () => {
  return {
    type: 'CLEAR_RECENTLY_USED'
  };
}

export const restoreDefaults = () => {
  return {
    type: 'RESTORE_DEFAULTS'
  };
}