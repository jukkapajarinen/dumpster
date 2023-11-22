using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace Robin
{
    public class Reddit
    {
        [JsonProperty("data")]
        public RedditData Data { get; set; }
    }

    public class RedditData
    {
        [JsonProperty("children")]
        public List<RedditChild> Children { get; set; }
    }

    public class RedditChild
    {
        [JsonProperty("data")]
        public RedditChildData Data { get; set; }
    }

    public class RedditChildData
    {
        [JsonProperty("id")]
        public string Id { get; set; }

        [JsonProperty("title")]
        public string Title { get; set; }

        [JsonProperty("url")]
        public Uri Url { get; set; }

        [JsonProperty("permalink")]
        public string Permalink { get; set; }

        [JsonProperty("author")]
        public string Author { get; set; }

        [JsonProperty("score")]
        public long Score { get; set; }

        [JsonProperty("created_utc")]
        public long CreatedUtc { get; set; }
    }
}