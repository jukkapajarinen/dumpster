const hero = {
  title: '@jukkapajarinen',
  subTitle: 'Student and Software Engineer (B.Eng.)',
  subSubTitle: 'I turn coffee into code.'
}

let projects = {
  title: 'Software projects',
  subTitle: 'Click the links to see more about them.',
  project: 'Project',
  items: [
    {
      name: 'Taskman-backend',
      link: 'https://taskman-jukkapajarinen.herokuapp.com/',
      tags: ['express', 'heroku', 'jwt', 'md5', 'mysql', 'MVC', 'Nodejs', 'REST']
    },
    {
      name: 'Flappy Block',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.flappyblock',
      tags: ['Admob', 'Android', 'AndroidGameLoop', 'Google Play', 'Java']
    },
    {
      name: 'Flag Quiz EU',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.flagquizeu',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: 'Emojidoku',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.emojidoku',
      tags: ['Admob', 'Android', 'Google Play', 'Java', 'JSudoku', 'NotoColorEmoji']
    },
    {
      name: 'Tap Tap Tap',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.taptaptap',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: 'Flag Quiz USA',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.flagquizusa',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: 'Flag Quiz',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.flagquiz',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: 'Tic Tac Toe',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.tictactoe',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: 'Flood It',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.floodit',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: 'BitbucketPage-React',
      link: 'https://bitbucket.org/jukkapajarinen/bitbucketpage-react',
      tags: ['Bulma', 'npm', 'React', 'SCSS']
    },
    {
      name: 'BitbucketPage-jQuery',
      link: 'https://bitbucket.org/jukkapajarinen/bitbucketpage-jquery',
      tags: ['Bulma', 'Handlebars', 'jQuery', 'npm', 'SCSS', 'Webpack']
    },
    {
      name: 'AndroidGameLoop',
      link: 'https://bitbucket.org/jukkapajarinen/androidgameloop',
      tags: ['2D game-loop', '60 FPS-CAP', 'Android', 'Java', 'MIT']
    },
    {
      name: 'Sudoku',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.supersudoku',
      tags: ['Admob', 'Android', 'Google Play', 'Java', 'JSudoku']
    },
    {
      name: 'Superpong',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkaboyar.colorpong',
      tags: ['Admob', 'Android', 'AndroidGameLoop', 'Google Play', 'Java']
    },
    {
      name: 'ElectionGame',
      link: 'https://bitbucket.org/jukkapajarinen/electiongame',
      tags: ['C++', 'Qt']
    },
    {
      name: 'cardiary-frontend',
      link: 'https://bitbucket.org/jukkapajarinen/cardiary-frontend',
      tags: ['Axios', 'Bootstrap 3', 'C3 Charts', 'MIT', 'npm', 'React', 'React-router', 'Redux']
    },
    {
      name: 'SwingSQLiteExample',
      link: 'https://bitbucket.org/jukkapajarinen/swingsqliteexample',
      tags: ['Gradle', 'MigLayout', 'Java', 'JFormDesigner', 'JUnit', 'SQLite', 'Swing']
    },
    {
      name: 'SwingQuizExample',
      link: 'https://bitbucket.org/jukkapajarinen/swingquizexample',
      tags: ['Gradle', 'MigLayout', 'Java', 'JFormDesigner', 'JSON', 'JUnit', 'Swing']
    }
  ]
};

projects.items.forEach((item, index) => {
  item.index = index + 1;
});

export var heroData = hero;
export let projectData = projects;