import 'jquery';
import 'handlebars/dist/handlebars.min.js';
import '@fortawesome/fontawesome-free/js/all.js';
import './styles/main.scss';
import './favicon.png';
import appHero from './templates/hero.hbs';
import appSome from './templates/some.hbs';
import appProjects from './templates/projects.hbs';
import appFooter from './templates/footer.hbs';
import { heroData as hero_en,  projectData as projects_en } from './assets/data_en.js';
import { heroData as hero_zh, projectsData as projects_zh } from './assets/data_zh.js';

let lang = (navigator.language || navigator.languages[0] || navigator.userLanguage).substring(0, 2);
if (window.localStorage.getItem('lang') === 'en' || window.localStorage.getItem('lang') === 'zh')
  lang = window.localStorage.getItem('lang');

let loadPage = () => {

  let html = appHero(lang === 'zh' ? hero_zh : hero_en);
  html += appSome({lang: lang});
  html += appProjects(lang === 'zh' ? projects_zh : projects_en);
  html += appFooter({ lang: lang === 'en' ? '中文' : 'English' });

  $('div#app').html(html);
  $('a#changeLanguageLink').on('click', (e) => {
    e.preventDefault();
    window.localStorage.removeItem('lang'); 
    window.localStorage.setItem('lang', lang === 'en' ? 'zh' : 'en');
    window.location.reload();
  });

};

$(window).on('load hashchange', () => loadPage());

