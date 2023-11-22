module.exports = {
  jwtSecret: process.env.JWT_SECRET,
  port: process.env.PORT,
  mysql: {
    host: process.env.DATABASE_HOSTL,
    port: process.env.DATABASE_PORTL,
    user: process.env.DATABASE_USERL,
    password: process.env.DATABASE_PSWD,
    database: process.env.DATABASE_DB
  }
};