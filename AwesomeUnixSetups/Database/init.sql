CREATE TABLE `Items` (
    `ItemId` int NOT NULL AUTO_INCREMENT,
    `RedditId` longtext CHARACTER SET utf8mb4 NULL,
    `Title` longtext CHARACTER SET utf8mb4 NULL,
    `Url` longtext CHARACTER SET utf8mb4 NULL,
    `ImgUrl` longtext CHARACTER SET utf8mb4 NULL,
    `Author` longtext CHARACTER SET utf8mb4 NULL,
    `Score` bigint NOT NULL,
    `Category` longtext CHARACTER SET utf8mb4 NULL,
    `CreatedUtc` bigint NOT NULL,
    `AddedUtc` bigint NOT NULL,
    CONSTRAINT `PK_Items` PRIMARY KEY (`ItemId`)
);

CREATE TABLE `Ratings` (
    `RatingId` int NOT NULL AUTO_INCREMENT,
    `RedditId1` longtext CHARACTER SET utf8mb4 NULL,
    `RedditId2` longtext CHARACTER SET utf8mb4 NULL,
    `WinnerId` longtext CHARACTER SET utf8mb4 NULL,
    `CreatedUtc` bigint NOT NULL,
    CONSTRAINT `PK_Ratings` PRIMARY KEY (`RatingId`)
);
