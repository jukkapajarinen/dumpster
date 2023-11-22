namespace Robin
{
    public class Item
    {
        public int ItemId { get; set; }
        public string RedditId { get; set; }
        public string Title { get; set; }
        public string Url { get; set; }
        public string ImgUrl { get; set; }
        public string Author { get; set; }
        public long Score { get; set; }
        public string Category { get; set; }
        public long CreatedUtc { get; set; }
        public long AddedUtc { get; set; }
    }
}