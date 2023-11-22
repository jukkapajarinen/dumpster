import React, { Component } from 'react';
import { render } from 'react-dom';
import '@fortawesome/fontawesome-free/js/all.js';
import './styles/main.css';
import Hero from './components/Hero';
import Some from './components/Some';
import Projects from './components/Projects';
import Footer from './components/Footer';
import { heroData as hero_en, projectData as projects_en } from './assets/data_en.js';
import { heroData as hero_zh, projectsData as projects_zh } from './assets/data_zh.js';

let lang = (navigator.language || navigator.languages[0] || navigator.userLanguage).substring(0, 2);
if (window.localStorage.getItem('lang') === 'en' || window.localStorage.getItem('lang') === 'zh') 
  lang = window.localStorage.getItem('lang');

class App extends Component {
  render() {
    return (
      <div className="wrapper">
        <Hero data={lang === 'zh' ? hero_zh : hero_en} />
        <Some lang={lang} />
        <Projects data={lang === 'zh' ? projects_zh : projects_en} />
        <Footer lang={lang}></Footer>
      </div>
    );
  }
}

render(<App />, document.getElementById('app'));
