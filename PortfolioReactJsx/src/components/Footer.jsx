import React from 'react';

let changeLanguage = (prevLang) => {
  window.localStorage.removeItem('lang');
  window.localStorage.setItem('lang', prevLang === 'en' ? 'zh' : 'en');
  window.location.reload();
}

const Footer = (props) => (
  <footer className="footer" id="footer-section">
    <div className="container">
      <div className="columns">
        <div className="column has-text-left has-text-centered-mobile">
          <p>© Jukka Pajarinen</p>
        </div>
        <div className="column has-text-right has-text-centered-mobile">
          <a href="/" onClick={() => changeLanguage(props.lang)}>{props.lang === 'en' ? '中文' : 'English'}</a>
        </div>
      </div>
    </div>
  </footer>
);

export default Footer;
