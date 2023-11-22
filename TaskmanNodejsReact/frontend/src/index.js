import React from 'react';
import ReactDOM from 'react-dom';
import Store from './stores/AppStore';
import App from './components/App';
import './styles/main.css';

const root = (
  <Store.Container>
    <App />
  </Store.Container>
);

ReactDOM.render(root, document.getElementById('root'));
