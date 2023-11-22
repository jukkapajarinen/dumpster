using System;
using System.Linq;

namespace Batman
{
    public class MainController
    {
        public string[] RandomImageUrlPair()
        {
            string[] imageUrlPair = new string[2];
            DatabaseController db = new DatabaseController();
            Random rnd = new Random();

            int rowCount = db.Items.Count();
            int firstIdx = rnd.Next(0, rowCount);
            int secondIdx = rnd.Next(0, rowCount);
            while(firstIdx == secondIdx) secondIdx = rnd.Next(0, rowCount);

            imageUrlPair[0] = db.Items.Find(firstIdx).ImgUrl;
            imageUrlPair[1] = db.Items.Find(secondIdx).ImgUrl;

            return imageUrlPair;
        }
    }
}