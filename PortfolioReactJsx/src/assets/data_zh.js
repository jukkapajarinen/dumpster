const hero = {
  title: '@jukkapajarinen',
  subTitle: '学生和软件工程师（工学学士）',
  subSubTitle: '我把咖啡变成了软件！'
}

let projects = {
  title: '软件项目',
  subTitle: '请点击链接',
  project: '项目',
  items: [
    {
      name: 'Taskman-backend',
      link: 'https://taskman-jukkapajarinen.herokuapp.com/',
      tags: ['express', 'heroku', 'jwt', 'md5', 'mysql', 'MVC', 'Nodejs', 'REST']
    },
    {
      name: '飞扬的广场',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.flappyblock',
      tags: ['Admob', 'Android', 'AndroidGameLoop', 'Google Play', 'Java']
    },
    {
      name: '欧洲联盟测试',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.flagquizeu',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: '表情数独',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.emojidoku',
      tags: ['Admob', 'Android', 'Google Play', 'Java', 'JSudoku', 'NotoColorEmoji']
    },
    {
      name: '点击',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.taptaptap',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: '美国测试',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.flagquizusa',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: '国旗测试',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.flagquiz',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: '井字棋',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.tictactoe',
      tags: ['Admob', 'Android', 'Google Play', 'Java']
    },
    {
      name: '洪水',
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
      name: '数独',
      link: 'https://play.google.com/store/apps/details?id=fi.jukkapajarinen.supersudoku',
      tags: ['Admob', 'Android', 'Google Play', 'Java', 'JSudoku']
    },
    {
      name: '超乓',
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

export const heroData = hero;
export let projectsData = projects;