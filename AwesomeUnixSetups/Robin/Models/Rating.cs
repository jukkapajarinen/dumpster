namespace Robin
{
    public class Rating
    {
        public int RatingId { get; set; }
        public string RedditId1 { get; set; }
        public string RedditId2 { get; set; }
        public string WinnerId { get; set; }
        public long CreatedUtc { get; set; }
    }
}