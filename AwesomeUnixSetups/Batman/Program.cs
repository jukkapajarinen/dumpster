using System;
using System.IO;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

namespace Batman
{
    public class Program
    {
        public static void Main(string[] args)
        {
            string host = Environment.GetEnvironmentVariable("BATMAN_HOST");
            string port = Environment.GetEnvironmentVariable("BATMAN_PORT");
            string webRoot = Directory.GetCurrentDirectory() + "/Public";
            string contentRoot = Directory.GetCurrentDirectory();
            string razorRoot = "/Views";

            if (String.IsNullOrEmpty(host)) Console.WriteLine("Error: BATMAN_HOST env variable is empty.");
            if (String.IsNullOrEmpty(port)) Console.WriteLine("Error: BATMAN_PORT env variable is empty.");

            IWebHostBuilder webApplication = new WebHostBuilder()
                .UseKestrel()
                .UseWebRoot(webRoot)
                .UseContentRoot(contentRoot)
                .UseUrls("http://"+host+":"+port)
                .Configure(app => {
                    app.UseStaticFiles();
                    app.UseRouting();
                    app.UseEndpoints(ep => ep.MapRazorPages());
                    app.UseStatusCodePagesWithRedirects("/");
                })
                .ConfigureServices(app => {
                    app.AddRazorPages().WithRazorPagesRoot(razorRoot);
                })
                .ConfigureLogging(app => {
                    app.ClearProviders();
                    app.AddConsole();
                });

            Console.WriteLine("Starting self-hosted Batman via Kestrel.");
            webApplication.Build().Run();
        }
    }
}
