import {createStore, combineReducers, applyMiddleware} from "redux";
import {createLogger} from 'redux-logger';
import thunk from 'redux-thunk';
import promise from "redux-promise-middleware";
import mathReducer from './reducers/mathReducer';
import userReducer from './reducers/userReducer';

const myLogger = (store) => (next) => (action) => {
  //console.log("logged action: ", action);
  next(action);
};

const store = createStore(
  combineReducers({mathReducer, userReducer}),
  {},
  applyMiddleware(myLogger, createLogger(), thunk, promise())
);

export default store;