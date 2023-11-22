using System;
using Microsoft.EntityFrameworkCore;
using Pomelo.EntityFrameworkCore.MySql.Infrastructure;

namespace Robin
{
    public class DatabaseController : DbContext
    {
        public DbSet<Item> Items { get; set; }
        public DbSet<Rating> Ratings { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            string host = Environment.GetEnvironmentVariable("DB_HOST");
            string port = Environment.GetEnvironmentVariable("DB_PORT");
            string db = Environment.GetEnvironmentVariable("DB_DATABASE");
            string user = Environment.GetEnvironmentVariable("DB_USER");
            string pswd = Environment.GetEnvironmentVariable("DB_PASSWORD");

            if (String.IsNullOrEmpty(host)) Console.WriteLine("Error: DB_HOST env variable is empty.");
            if (String.IsNullOrEmpty(port)) Console.WriteLine("Error: DB_PORT env variable is empty.");
            if (String.IsNullOrEmpty(db)) Console.WriteLine("Error: DB_DATABASE env variable is empty.");
            if (String.IsNullOrEmpty(user)) Console.WriteLine("Error: DB_USER env variable is empty.");
            if (String.IsNullOrEmpty(pswd)) Console.WriteLine("Error: DB_PASSWORD env variable is empty.");

            string connectionString = "Server="+host+";Port="+port+";Database="+db+";User="+user+";Password="+pswd+";";
            optionsBuilder.UseMySql(connectionString, mysqlOptions => {
                mysqlOptions.ServerVersion(new Version(10, 5), ServerType.MariaDb)
                    .EnableRetryOnFailure();
            });
        }
    }
}