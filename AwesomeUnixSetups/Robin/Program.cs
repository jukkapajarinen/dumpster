using System;
using System.Threading.Tasks;
using System.Linq;
using System.Collections.Generic;

namespace Robin
{
    class Program
    {
        static async Task Main(string[] args)
        {
            DatabaseController db = new DatabaseController();
            RedditController reddit = new RedditController();

            List<RedditChildData> posts = await reddit.FetchUnixsetupPosts();
            foreach (var post in posts)
            {
                // Check that title contains [i3-gaps] etc.
                if (post.Title.Split('[', ']').Length >= 3)
                {
                    if (!db.Items.Any(i => i.RedditId == post.Id))
                    {
                        db.Add(new Item {
                            Title = post.Title,
                            Url = post.Permalink,
                            ImgUrl = post.Url.ToString(),
                            Author = post.Author,
                            Category = post.Title.Split('[', ']')[1],
                            RedditId = post.Id,
                            Score = post.Score,
                            CreatedUtc = post.CreatedUtc,
                            AddedUtc = DateTime.UtcNow.Ticks
                        });
                        Console.WriteLine("[" + DateTime.Now + "] Added: " + post.Title);
                    }
                    else
                    {
                        Console.WriteLine("[" + DateTime.Now + "] Skipped: " + post.Title);
                    }
                }
            }
            db.SaveChanges();
        }
    }
}
