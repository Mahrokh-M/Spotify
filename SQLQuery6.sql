-- DELETE FOREIGN KEY constraints
DECLARE @sql NVARCHAR(MAX) = '';

SELECT @sql = @sql + 'ALTER TABLE ' + t.name + ' DROP CONSTRAINT ' + fk.name + '; '
FROM sys.foreign_keys AS fk
JOIN sys.tables AS t ON fk.parent_object_id = t.object_id;

EXEC sp_executesql @sql;
------
DECLARE @sql NVARCHAR(MAX) = '';

SELECT @sql = @sql + 'DROP TABLE ' + t.name + '; '
FROM sys.tables AS t;

EXEC sp_executesql @sql;
-------------------------------
SELECT DB_NAME() AS CurrentDatabase;

--------------------------------------------------------------------------------------------------------------------
CREATE TABLE Users (
    user_id INT PRIMARY KEY IDENTITY,
    username VARCHAR(50) NOT NULL,
    [password] VARCHAR(50) NOT NULL,
    email VARCHAR(100) NOT NULL,
    birth_date DATE,
    [location] VARCHAR(100)
);
-----------------------------------------------------
CREATE TABLE Premium(
    user_id INT PRIMARY KEY,  
	Start_time DATETIME,
	End_time DATETIME,
	FOREIGN KEY (user_id) REFERENCES Users(user_id)
);
-----------------------------------------------------
CREATE TABLE Play_list(
    user_id INT ,
	[name] VARCHAR(50) NOT NULL ,
    ispublic BIT DEFAULT 0,
	address_of_picture VARCHAR(100),
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
	PRIMARY KEY(user_id,[name])
);
-----------------------------------------------------
CREATE TABLE Digital_wallet (
    Digital_wallet_id INT PRIMARY KEY IDENTITY,
    user_id INT,
    amount DECIMAL(10, 2),
    FOREIGN KEY (user_id) REFERENCES Users(user_id)
);
-----------------------------------------------------
CREATE TABLE Artists (
    artist_id INT PRIMARY KEY ,
    bio VARCHAR(MAX),
    FOREIGN KEY (artist_id) REFERENCES Users(user_id)
);
------------------------------------------------------------
CREATE TABLE Albums (
    album_id INT PRIMARY KEY IDENTITY,
	title VARCHAR(100) NOT NULL,
	artist_id_added INT,
    genre VARCHAR(50),
    release_date DATE,
	Age_category CHAR(2),
	country VARCHAR(50),
	address_of_picture VARCHAR(100),
	FOREIGN KEY (artist_id_added) REFERENCES Artists(artist_id)
);
-----------------------------------------------------
CREATE TABLE Songs (
    song_id INT PRIMARY KEY IDENTITY,
	artist_id_added INT,
	title VARCHAR(100)  NOT NULL,
	album_id INT,
    genre VARCHAR(50),
    release_date DATE,
    lyrics VARCHAR(MAX),
	Age_category CHAR(2),
	country VARCHAR(50),
	address_of_picture VARCHAR(100),
    can_be_added BIT DEFAULT 0,
	FOREIGN KEY (album_id) REFERENCES Albums(album_id),
	FOREIGN KEY (artist_id_added) REFERENCES Artists(artist_id)
);
----------------------------------------------------
CREATE TABLE Concerts (
    artist_id INT ,
    [location] VARCHAR(100),
    [date] DATETIME ,
	address_of_picture VARCHAR(100),
    FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
	PRIMARY KEY (artist_id,[date])
);
----------------------------------------------------
CREATE TABLE Tickets (
    ticket_id INT PRIMARY KEY IDENTITY,
    user_id INT,
	artist_id INT,
	price DECIMAL(10, 2),
    Expiration BIT DEFAULT 1,-- 1
	is_sold BIT DEFAULT 0,-- 0 
	date_concert DATETIME ,--**
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
	FOREIGN KEY (artist_id,date_concert) REFERENCES Concerts(artist_id,[date])
);
----------------------------------------------------
---------------------------------------------------
CREATE TABLE Favorite_Play_list(
    user_id INT,
    [name] VARCHAR(50) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
    FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
    PRIMARY KEY (user_id, [name])
);
---------------------------------------------------
CREATE TABLE Comment_Play_list(
    user_id INT ,
	[name] VARCHAR(50) NOT NULL ,
	[text] VARCHAR(100),
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
	PRIMARY KEY (user_id,[name])
);
---------------------------------------------------
CREATE TABLE Like_Play_list(
    user_id INT ,
	[name] VARCHAR(50) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
	PRIMARY KEY(user_id,[name])
);
----------------------------------------------------
CREATE TABLE Friend(
    user_id1 INT,
	user_id2 INT,
	accept BIT DEFAULT 0,
    FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
	FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
	PRIMARY KEY(user_id1,user_id2)
);
----------------------------------------------------
CREATE TABLE Message_Premium (
    user_id1 INT,
    user_id2 INT,
    [text] VARCHAR(100),
    FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
    FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
    PRIMARY KEY (user_id1, user_id2)
);
-------------------------------------------------------
CREATE TABLE follower(
	user_id1 INT,
	user_id2 INT,
    FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
	FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
	PRIMARY KEY(user_id1,user_id2)
);
-------------------------------------------------------
CREATE TABLE Comment_Album (
    user_id INT,                  
    album_id INT,
    [text] VARCHAR(100),
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
    FOREIGN KEY (album_id) REFERENCES Albums(album_id),
	PRIMARY KEY(user_id,album_id)
);
------------------------------------------------------
CREATE TABLE artist_has_song(
    song_id INT ,
	artist_id INT ,
    FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
	PRIMARY KEY(song_id,artist_id)
);
-------------------------------------------------------
CREATE TABLE artist_has_album(
    album_id INT,
	artist_id INT ,
    FOREIGN KEY (album_id) REFERENCES Albums(album_id),
	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
	PRIMARY KEY(album_id,artist_id)
);
-------------------------------------------------------
CREATE TABLE Playlist_has_song(
    [name]  VARCHAR(50),
	song_id INT ,
	user_id INT ,
    FOREIGN KEY (user_id,[name]) REFERENCES Play_list(user_id,[name]),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY([name],song_id,user_id)
);
-------------------------------------------------------
--??????
CREATE TABLE Favorite_Song(
    user_id INT,
	song_id INT,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------
CREATE TABLE Comment_song(
    song_id INT,
	[text] VARCHAR(100),
	user_id INT,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------
CREATE TABLE Like_song(
    song_id INT ,
	user_id INT ,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------
--DROP TABLE Like_album;
CREATE TABLE Like_album(
    user_id INT ,
	album_id INT ,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (album_id) REFERENCES Albums(album_id),
	PRIMARY KEY(user_id,album_id)

);
-------------------------------------------------------
CREATE TABLE Return_money(
    Digital_wallet_id INT ,
	artist_id INT  ,
    [date] DATETIME ,
	amount DECIMAL(10, 2), --**
    FOREIGN KEY (artist_id,[date]) REFERENCES Concerts(artist_id,[date]),
	FOREIGN KEY (Digital_wallet_id) REFERENCES Digital_wallet(Digital_wallet_id),
	PRIMARY KEY(artist_id,Digital_wallet_id,[date])
);
-------------------------------------------------------
CREATE TABLE Play_song(
   song_id INT ,
	user_id INT ,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
------------------------------------
CREATE TABLE User_Artist_Likes (
    user_id INT,
    artist_id INT,
    song_id INT ,
    Likes_Count INT,
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
	PRIMARY KEY(user_id,song_id)
);
--------------------------------
CREATE TABLE User_Genre_Likes (
    user_id INT,
    song_id INT ,
	Likes_Count INT,
	FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);

-------------------------------------------------------
CREATE PROCEDURE InsertUser
    @username NVARCHAR(50),
    @password NVARCHAR(50),
    @birth_date DATE,
    @location NVARCHAR(100),
    @Email NVARCHAR(100)
AS
BEGIN
    INSERT INTO Users (username, [password], email, birth_date, [location])
    VALUES (@username, @password, @Email, @birth_date, @location);
END

---------------------------------------------------
CREATE PROCEDURE InsertPremium
    @user_id INT, 
    @end_time DATETIME,
    @start_time DATETIME
AS 
BEGIN 
    INSERT INTO Premium (user_id, Start_time, End_time)
    VALUES (@user_id, @start_time, @end_time); 

    PRINT 'Premium subscription added successfully.'; 
END;

-------------------------------------------------------
CREATE PROCEDURE CreatePlaylist
    @user_id INT,
    @playlist_name NVARCHAR(50),
    @is_public BIT
AS
BEGIN
    -- Check if the user has a valid subscription
    IF EXISTS (
        SELECT 1
        FROM Premium
        WHERE user_id = @user_id AND End_time > GETDATE()
    )
    BEGIN
        -- Check if the playlist name is already used by the user
        IF NOT EXISTS (
            SELECT 1
            FROM Play_list
            WHERE user_id = @user_id
              AND [name] = @playlist_name
        )
        BEGIN
            -- Insert the playlist into Play_list table
            INSERT INTO Play_list (user_id, [name], ispublic)
            VALUES (@user_id, @playlist_name, @is_public);
            PRINT 'Playlist created successfully.';
        END
        ELSE
        BEGIN
            PRINT 'Playlist with this name already exists.';
        END;
    END
    ELSE
    BEGIN
        PRINT 'User does not have a valid subscription. Playlist creation is not allowed.';
    END;
END;
----------------------------------------------
CREATE PROCEDURE AddSongToPlaylist
    @user_id INT,
    @playlist_name NVARCHAR(50),
    @song_id INT
AS
BEGIN
    -- Check if the playlist exists for the user
    IF EXISTS (
        SELECT 1
        FROM Play_list
        WHERE user_id = @user_id AND [name] = @playlist_name
    )
    BEGIN
        -- Check if the song already exists in the playlist
        IF NOT EXISTS (
            SELECT 1
            FROM Playlist_has_song
            WHERE user_id = @user_id AND [name] = @playlist_name AND song_id = @song_id
        )
        BEGIN
            -- Insert the song into the playlist
            INSERT INTO Playlist_has_song (user_id, [name], song_id)
            VALUES (@user_id, @playlist_name, @song_id);
            PRINT 'Song added to playlist successfully.';
        END
        ELSE
        BEGIN
            PRINT 'This song is already in the playlist.';
        END
    END
    ELSE
    BEGIN
        PRINT 'The specified playlist does not exist for the user.';
    END
END;

--------------------
CREATE PROCEDURE ViewPlaylistSongsWithArtists
    @playlist_name NVARCHAR(50),
    @user_id INT
AS
BEGIN
    SELECT 
        PHS.[name] AS playlist_name,
        S.song_id,
        S.title AS song_title,
        STRING_AGG(U.username, ', ') AS artist_names,
        S.genre,
        S.release_date
    FROM 
        Playlist_has_song PHS
    INNER JOIN 
        Songs S ON PHS.song_id = S.song_id
    INNER JOIN 
        artist_has_song AHS ON S.song_id = AHS.song_id
    INNER JOIN 
        Artists A ON AHS.artist_id = A.artist_id
    INNER JOIN 
        Users U ON A.artist_id = U.user_id -- Assuming artist_id corresponds to user_id in Users
    WHERE 
        PHS.[name] = @playlist_name
    GROUP BY 
        PHS.[name], S.song_id, S.title, S.genre, S.release_date
    ORDER BY 
        S.song_id;
END;
-----------------------------------------------------
CREATE PROCEDURE AddCommentToPlaylist
    @user_id INT,
    @playlist_name NVARCHAR(50),
    @text VARCHAR(100)
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM Premium 
        WHERE user_id = @user_id AND End_time > GETDATE()
    )
    BEGIN
        INSERT INTO Comment_Play_list (user_id, [name], [text])
        VALUES (@user_id, @playlist_name, @text);
        PRINT 'Comment added successfully to playlist.';
    END
    ELSE
    BEGIN
        PRINT 'User does not have a valid subscription. Commenting is not allowed.';
    END
END
-----------------------------------------------------------------
CREATE PROCEDURE AddCommentToSong
    @user_id INT,
    @song_id INT,
    @text VARCHAR(100)
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM Premium
        WHERE user_id = @user_id AND End_time > GETDATE()
    )
    BEGIN
        INSERT INTO Comment_song (song_id, [text], user_id)
        VALUES (@song_id, @text, @user_id);
        
        PRINT 'Comment added successfully to song.';
    END
    ELSE
    BEGIN
        PRINT 'User does not have a valid subscription. Commenting is not allowed.';
    END
END
----------------------------------------------------------------
CREATE PROCEDURE AddCommentToAlbum
    @user_id INT,
    @album_id INT,
    @text VARCHAR(100)
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM Premium
        WHERE user_id = @user_id AND End_time > GETDATE()
    )
    BEGIN
        INSERT INTO Comment_Album (user_id, album_id, [text])
        VALUES (@user_id, @album_id, @text);
        
        PRINT 'Comment added successfully to album.';
    END
    ELSE
    BEGIN

        PRINT 'User does not have a valid subscription. Commenting is not allowed.';
    END
END
-----------------------------------------------------------------
CREATE PROCEDURE LikeSong
    @user_id INT,
    @song_id INT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM Premium
        WHERE user_id = @user_id AND End_time > GETDATE()
    )
    BEGIN
        IF NOT EXISTS (
            SELECT 1     -- Using SELECT 1 in SQL is a shorthand way to check the existence of a record or condition without selecting any specific columns. It's efficient because it avoids selecting unnecessary data and simply returns a constant value (1) to indicate if the condition exists or not.
            FROM Like_song
            WHERE user_id = @user_id AND song_id = @song_id
        )
        BEGIN
            INSERT INTO Like_song (user_id, song_id)
            VALUES (@user_id, @song_id);
            
            PRINT 'Song liked successfully.';
        END
        ELSE
        BEGIN
            PRINT 'You have already liked this song.';
        END
    END
    ELSE
    BEGIN
        PRINT 'User does not have a valid subscription. Liking is not allowed.';
    END
END
---------------------------------------------------------------
CREATE PROCEDURE LikeAlbum
    @user_id INT,
    @album_id INT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM Premium
        WHERE user_id = @user_id AND End_time > GETDATE()
    )
    BEGIN
        IF NOT EXISTS (
            SELECT 1
            FROM Like_album
            WHERE user_id = @user_id AND album_id = @album_id
        )
        BEGIN
            INSERT INTO Like_album (user_id, album_id)
            VALUES (@user_id, @album_id);
            
            PRINT 'Album liked successfully.';
        END
        ELSE
        BEGIN
            PRINT 'You have already liked this album.';
        END
    END
    ELSE
    BEGIN
        PRINT 'User does not have a valid subscription. Liking is not allowed.';
    END
END
-------------------------------------------------------
CREATE PROCEDURE LikePlaylist
    @user_id INT,
    @playlist_name NVARCHAR(50)
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM Premium
        WHERE user_id = @user_id AND End_time > GETDATE()
    )
    BEGIN
        IF NOT EXISTS (
            SELECT 1
            FROM Like_Play_list
            WHERE user_id = @user_id AND [name] = @playlist_name
        )
        BEGIN
            INSERT INTO Like_Play_list(user_id, [name])
            VALUES (@user_id, @playlist_name);
            
            PRINT 'Playlist liked successfully.';
        END
        ELSE
        BEGIN
            PRINT 'You have already liked this playlist.';
        END
    END
    ELSE
    BEGIN
        PRINT 'User does not have a valid subscription. Liking is not allowed.';
    END
END
----------------------------------------------------------
CREATE PROCEDURE InsertUserArtistLikes
AS
BEGIN
    INSERT INTO User_Artist_Likes (user_id, artist_id, song_id, Likes_Count)
    SELECT 
        ls.user_id,
        ar.artist_id,
        ls.song_id,
        COUNT(ls.song_id) OVER (PARTITION BY ls.user_id, ar.artist_id) AS Likes_Count
    FROM 
        Like_song ls
    JOIN 
        Songs s ON ls.song_id = s.song_id
    JOIN 
        artist_has_song ahs ON s.song_id = ahs.song_id
    JOIN 
        Artists ar ON ahs.artist_id = ar.artist_id;
END;

CREATE PROCEDURE InsertUserGenreLikes
AS
BEGIN
    INSERT INTO User_Genre_Likes (user_id, song_id, Likes_Count)
    SELECT 
        ls.user_id,
        ls.song_id,
        COUNT(ls.song_id) OVER (PARTITION BY ls.user_id, s.genre) AS Likes_Count
    FROM 
        Like_song ls
    JOIN 
        Songs s ON ls.song_id = s.song_id;
END;



--EXEC GetUserInterests @user_id = 1;
-------------------------------------------------------
CREATE PROCEDURE GetRecommendedAlb
(
    @user_id INT
)
AS
BEGIN
    SELECT TOP 10
        A.album_id,
        A.title AS album_title,
        U.username AS artist_name,
        A.genre,
        A.release_date
    FROM 
        Albums A
    INNER JOIN 
        artist_has_album AHA ON A.album_id = AHA.album_id
	INNER JOIN	 User_Artist_Likes UAL ON  UAL.user_id = @user_id
    INNER JOIN 
        Artists AR ON AHA.artist_id = AR.artist_id
    INNER JOIN 
        Users U ON AR.artist_id = U.user_id
    WHERE 
        A.album_id  IN (SELECT album_id FROM Like_album WHERE user_id = @user_id)
    ORDER BY 
        NEWID(); -- Random order for diversity in recommendations
END;

------------------------------------------------------------------------
CREATE PROCEDURE GetRecommendedSongsByArtistLike
(
    @user_id INT
)
AS
BEGIN
    SELECT TOP 10
        --S.song_id,
        S.title AS song_title,
        U.username AS artist_name,
        S.genre,
        S.release_date
    FROM
        Songs S
    INNER JOIN
        artist_has_song ASHS ON ASHS.song_id = S.song_id
    INNER JOIN
        Artists A ON ASHS.artist_id = A.artist_id
    INNER JOIN
        User_Artist_Likes UAL ON A.artist_id = UAL.artist_id
	INNER JOIN 
        Users U ON A.artist_id = U.user_id
    WHERE
        UAL.user_id = @user_id
    AND
        S.song_id IN (SELECT song_id FROM Like_song WHERE user_id = @user_id)
    ORDER BY
        UAL.Likes_Count DESC, NEWID();
END;
CREATE PROCEDURE GetRecommendedSongsByGenreLike
(
    @user_id INT
)
AS
BEGIN
    WITH GenreLikes AS (
        SELECT 
            UGL.user_id,
            S.song_id,
            S.title AS song_title,
            S.genre,
            UGL.Likes_Count
        FROM 
            User_Genre_Likes UGL
        INNER JOIN 
            Songs S ON UGL.song_id = S.song_id
        WHERE 
            UGL.user_id = @user_id
    )
    
    SELECT TOP 10
        --S.song_id,
        S.title AS song_title,
        U.username AS artist_name,
        S.genre,
        S.release_date
    FROM 
        Songs S
    INNER JOIN 
        artist_has_song ASHS ON ASHS.song_id = S.song_id
    INNER JOIN 
        Artists A ON ASHS.artist_id = A.artist_id
    INNER JOIN 
        GenreLikes GL ON S.song_id = GL.song_id
	INNER JOIN 
        Users U ON A.artist_id = U.user_id
    WHERE 
        S.song_id IN (SELECT song_id FROM Like_song WHERE user_id = @user_id) -- Exclude songs liked by the user
    ORDER BY 
        GL.Likes_Count DESC, NEWID(); -- Order by likes count of genre and then randomize
END;



------------------------------------------------------------------------------------------------------------
INSERT INTO Friend (user_id1, user_id2, accept)
VALUES 
(1, 2, 1),
(2, 3, 1);
EXEC AddSongToPlaylist
    @user_id =1,
    @playlist_name ='Playlist1',
    @song_id =2;

EXEC ViewPlaylistSongsWithArtists
    @playlist_name= 'Playlist1',
    @user_id =1;
	SELECT * FROM Play_list;

INSERT INTO Users (username, [password], email, birth_date, [location])
VALUES 
('user1', 'password1', 'user1@example.com', '1990-01-01', 'City1'),
('user2', 'password2', 'user2@example.com', '1991-02-02', 'City2'),
('user3', 'password3', 'user3@example.com', '1992-03-03', 'City3'),
('user4', 'password4', 'user4@example.com', '1994-03-03', 'City4');
-- INSERT INTO Permium
INSERT INTO Users (username, [password], email, birth_date, [location])
VALUES
('user4', 'password4', 'user4@example.com', '1994-03-03', 'City4');
SELECT * FROM Users;
INSERT INTO Premium (user_id, Start_time, End_time)
VALUES 
(1,'2024-01-01 12:13:10', '2024-12-31 12:13:10'),
(2,'2024-02-01 12:13:10', '2024-12-31 12:13:10'),
(3,'2024-03-01 12:13:10', '2024-12-31 12:13:10');
INSERT INTO Premium (user_id, Start_time, End_time)
VALUES 
(4,'2024-01-01 12:15:10', '2025-12-31 12:13:10');
SELECT * FROM Users;
-- INSERT INTO Play_list
INSERT INTO Play_list (user_id, [name], ispublic, address_of_picture)
VALUES 
(1, 'Playlist1', 1, 'path/to/picture1.jpg'),
(2, 'Playlist2', 0, 'path/to/picture2.jpg'),
(3, 'Playlist3', 1, 'path/to/picture3.jpg');

-- INSERT INTO Digital_wallet
INSERT INTO Digital_wallet (user_id, amount)
VALUES 
(1, 100.00),
(2, 150.00),
(3, 200.00);

-- INSERT INTO Artists
INSERT INTO Artists (artist_id,bio)
VALUES 
(1,'Artist Bio 1'),
(2,'Artist Bio 2'),
(3,'Artist Bio 3');
INSERT INTO Albums (title, artist_id_added, genre, release_date, Age_category, country, address_of_picture)
VALUES 
('Album1', 1, 'Rock', '2024-01-01', 'PG', 'USA', 'path/to/album1.jpg'),
('Album2', 2, 'Pop', '2024-02-01', 'PG', 'UK', 'path/to/album2.jpg'),
('Album3', 3, 'Jazz', '2024-03-01', 'R', 'Canada', 'path/to/album3.jpg');
INSERT INTO Songs (artist_id_added, title, album_id, genre, release_date, lyrics, Age_category, country, address_of_picture, can_be_added)
VALUES 
(1, 'Song1', 1, 'Rock', '2024-01-01', 'Lyrics of Song1', 'PG', 'USA', 'path/to/song1.jpg', 1),
(2, 'Song2', 2, 'Pop', '2024-02-01', 'Lyrics of Song2', 'PG', 'UK', 'path/to/song2.jpg', 1),
(3, 'Song3', 3, 'Jazz', '2024-03-01', 'Lyrics of Song3', 'R', 'Canada', 'path/to/song3.jpg', 1);
INSERT INTO Concerts (artist_id, [location], [date], address_of_picture)
VALUES 
(1, 'Venue1', '2025-05-01 20:00:00', 'path/to/concert1.jpg'),
(2, 'Venue2', '2029-06-01 20:00:00', 'path/to/concert2.jpg'),
(3, 'Venue3', '2027-07-01 20:00:00', 'path/to/concert3.jpg');
INSERT INTO artist_has_album (album_id, artist_id)
VALUES 
(1, 1),
(2, 2),
(3, 3);
INSERT INTO artist_has_song (song_id, artist_id)
VALUES 
(1, 1),
(2, 2),
(3, 3);
INSERT INTO Like_album (user_id, album_id)
VALUES 
(1, 1),
(2, 2);
INSERT INTO Like_song (song_id, user_id)
VALUES 
(1, 1),
(2, 2);
INSERT INTO artist_has_album (album_id, artist_id)
VALUES 
(1, 1),
(2, 2),
(3, 3);

	EXEC LikePlaylist
    @user_id = 1,  
    @playlist_name ='Playlist1';
	SELECT * FROM  GetRecommendedSongs(2);
	SELECT * FROM  Playlist_has_song ;
	CREATE PROCEDURE GetRecommendedSongs
(
    @user_id INT
)
GetRecommendedSongs @user_id=1;
GetRecommendedAlbums @user_id=1;
EXEC CreatePlaylist @user_id = 1;
EXEC InsertUserArtistLikes;
SELECT * FROM User_Artist_Likes;
EXEC InsertUserGenreLikes;
SELECT * FROM artist_has_album;
SELECT * FROM User_Genre_Likes;
EXEC GetRecommendedAlb @user_id=1;
EXEC GetRecommendedSongsByArtistLike @user_id=1;
EXEC GetRecommendedSongsByGenreLike @user_id=1;