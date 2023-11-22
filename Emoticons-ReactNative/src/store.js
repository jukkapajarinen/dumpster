import {createStore, combineReducers, applyMiddleware} from 'redux';
import logger from 'redux-logger';
import General from './reducers/GeneralReducer';
import Settings from './reducers/SettingsReducer';

export default createStore(
  combineReducers({
    General,
    Settings
  }),
  applyMiddleware(logger)
);
