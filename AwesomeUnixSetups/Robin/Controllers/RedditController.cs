using System;
using System.Threading.Tasks;
using System.Net.Http;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace Robin
{
    public class RedditController
    {
        private readonly HttpClient client = new HttpClient();

        public async Task<List<RedditChildData>> FetchUnixsetupPosts()
        {
            client.DefaultRequestHeaders.Accept.Clear();
            HttpResponseMessage task = await client.GetAsync("https://www.reddit.com/r/unixporn.json");
            String jsonString = await task.Content.ReadAsStringAsync();
            Reddit redditListing = JsonConvert.DeserializeObject<Reddit>(jsonString);
            List<RedditChild> posts = redditListing.Data.Children;
            List<RedditChildData> flattenedPosts = new List<RedditChildData>();
            foreach (RedditChild post in posts)
                flattenedPosts.Add(post.Data);
            return flattenedPosts;
        }
    }
}