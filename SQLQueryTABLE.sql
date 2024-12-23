---- DELETE FOREIGN KEY constraints
--DECLARE @sql NVARCHAR(MAX) = '';

--SELECT @sql = @sql + 'ALTER TABLE ' + t.name + ' DROP CONSTRAINT ' + fk.name + '; '
--FROM sys.foreign_keys AS fk
--JOIN sys.tables AS t ON fk.parent_object_id = t.object_id;

--EXEC sp_executesql @sql;
--------
--DECLARE @sql NVARCHAR(MAX) = '';

--SELECT @sql = @sql + 'DROP TABLE ' + t.name + '; '
--FROM sys.tables AS t;

--EXEC sp_executesql @sql;
---------------------------------
--SELECT DB_NAME() AS CurrentDatabase;
------------------------------------------------------------------------------------------------------------------------
--CREATE TABLE Users (
--    user_id INT PRIMARY KEY IDENTITY,
--    username VARCHAR(50) NOT NULL,
--    [password] VARCHAR(50) NOT NULL,
--    email VARCHAR(100) NOT NULL,
--    birth_date DATE,
--    [location] VARCHAR(100)
--);
-------------------------------------------------------
--CREATE TABLE Premium(
--    user_id INT PRIMARY KEY,  
--	Start_time DATETIME,
--	End_time DATETIME,
--	FOREIGN KEY (user_id) REFERENCES Users(user_id)
--);
-------------------------------------------------------

--CREATE TABLE Play_list(
--    user_id INT ,
--	[name] VARCHAR(50) NOT NULL ,
--    ispublic BIT DEFAULT 0,
--	address_of_picture VARCHAR(200),
--    FOREIGN KEY (user_id) REFERENCES Users(user_id),
--	PRIMARY KEY(user_id,[name])
--);
-------------------------------------------------------
----DROP:
--CREATE TABLE Digital_wallet (
--    Digital_wallet_id INT PRIMARY KEY IDENTITY,
--    user_id INT,
--    amount DECIMAL(10, 2) DEFAULT 0.00 NOT NULL,
--    FOREIGN KEY (user_id) REFERENCES Users(user_id)
--);
-------------------------------------------------------
--CREATE TABLE Artists (
--    artist_id INT PRIMARY KEY,
--    bio VARCHAR(MAX),
--    FOREIGN KEY (artist_id) REFERENCES Users(user_id)
--);
--------------------------------------------------------------
--CREATE TABLE Albums (
--    album_id INT PRIMARY KEY IDENTITY,
--	title VARCHAR(100) NOT NULL,
--	artist_id_added INT,
--    genre VARCHAR(50),
--    release_date DATE,
--	Age_category CHAR(2),
--	country VARCHAR(50),
--	address_of_picture VARCHAR(200),
--	FOREIGN KEY (artist_id_added) REFERENCES Artists(artist_id)
--);
-------------------------------------------------------
CREATE TABLE Songs (
    song_id INT PRIMARY KEY IDENTITY,
	artist_id_added INT,
	title VARCHAR(100)  NOT NULL,
	album_id INT NULL,
    genre VARCHAR(50),
    release_date DATE,
    lyrics VARCHAR(MAX),
	Age_category CHAR(2),
	country VARCHAR(50),
	address_of_picture VARCHAR(200),
    can_be_added BIT DEFAULT 0,
	FOREIGN KEY (album_id) REFERENCES Albums(album_id)ON DELETE CASCADE,
	FOREIGN KEY (artist_id_added) REFERENCES Artists(artist_id)
);
----------------------------------------------------
DROP TABLE Concerts
CREATE TABLE Concerts (
    artist_id INT ,
    [location] VARCHAR(100),
    [date] DATETIME ,
    cancel BIT  DEFAULT 0, --laghv nist
	address_of_picture VARCHAR(200),
    FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
	PRIMARY KEY (artist_id,[date])
);
------------------------------------------------------
CREATE TABLE Tickets (
    ticket_id INT PRIMARY KEY IDENTITY,
    user_id INT,
	artist_id INT,
	price DECIMAL(10, 2),
    Expiration BIT DEFAULT 0,-- 1
	is_sold BIT DEFAULT 0,-- 0 
	date_concert DATETIME ,--**
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
	FOREIGN KEY (artist_id,date_concert) REFERENCES Concerts(artist_id,[date])
);
------------------------------------------------------
CREATE TABLE Favorite_Play_list(
    user_id INT,
	user_id_owner INT,
    [name] VARCHAR(50) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
    FOREIGN KEY (user_id_owner, [name]) REFERENCES Play_list(user_id, [name]),
    PRIMARY KEY (user_id_owner,user_id, [name])
);
-----------------------------------------------------
CREATE TABLE Comment_Play_list(
    user_id INT ,
	[name] VARCHAR(50) NOT NULL ,
	[text] VARCHAR(100),
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
	PRIMARY KEY (user_id,[name])
);
-----------------------------------------------------
CREATE TABLE Like_Play_list(
    user_id INT ,
	[name] VARCHAR(50) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
	PRIMARY KEY(user_id,[name])
);
------------------------------------------------------
CREATE TABLE Friend(
    user_id1 INT,
	user_id2 INT,
	accept BIT DEFAULT 0,
    FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
	FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
	PRIMARY KEY(user_id1,user_id2)
);
------------------------------------------------------
CREATE TABLE Message_Premium (
    user_id1 INT,
    user_id2 INT,
    [text] VARCHAR(Max),
	CreatedDate DATETIME DEFAULT GETDATE(),
    FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
    FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
    PRIMARY KEY (user_id1, user_id2)
);
---------------------------------------------------------
CREATE TABLE follower(
	user_id1 INT,
	user_id2 INT,
  FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
	FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
	PRIMARY KEY(user_id1,user_id2)
);
---------------------------------------------------------
CREATE TABLE Comment_Album (
    user_id INT,                  
    album_id INT,
    [text] VARCHAR(MAX),
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
    FOREIGN KEY (album_id) REFERENCES Albums(album_id)ON DELETE CASCADE,
	PRIMARY KEY(user_id,album_id)
);
--------------------------------------------------------
CREATE TABLE artist_has_song(
    song_id INT ,
	artist_id INT ,
    FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
	PRIMARY KEY(song_id,artist_id)
);
---------------------------------------------------------
CREATE TABLE artist_has_album(
    album_id INT,
	artist_id INT ,
    FOREIGN KEY (album_id) REFERENCES Albums(album_id)ON DELETE CASCADE,
	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
	PRIMARY KEY(album_id,artist_id)
);
---------------------------------------------------------
CREATE TABLE Playlist_has_song(
    [name]  VARCHAR(50),
	song_id INT ,
	user_id INT ,
    FOREIGN KEY (user_id,[name]) REFERENCES Play_list(user_id,[name]),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
	PRIMARY KEY([name],song_id,user_id)
);
---------------------------------------------------------
CREATE TABLE Favorite_Song(
    user_id INT,
	song_id INT,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
	PRIMARY KEY(user_id,song_id)
);
---------------------------------------------------------
--DROP
DROP TABLE Comment_song
CREATE TABLE Comment_song(
    song_id INT,
	[text] VARCHAR(MAX),
	user_id INT,
	[date] DATETIME,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
	PRIMARY KEY(user_id,song_id,[date])
);
---------------------------------------------------------
CREATE TABLE Like_song(
    song_id INT ,
	user_id INT ,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
	PRIMARY KEY(user_id,song_id)
);
---------------------------------------------------------
CREATE TABLE Like_album(
    user_id INT ,
	album_id INT ,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (album_id) REFERENCES Albums(album_id)ON DELETE CASCADE,
	PRIMARY KEY(user_id,album_id)

);
-------------------------------------------------------------------------
CREATE TABLE Play_song(
   song_id INT ,
	user_id INT ,
    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------------------------
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
-------------------------------------------------------------------------
CREATE TABLE User_Genre_Likes (
	user_id INT,
	song_id INT ,
	Likes_Count INT,
	FOREIGN KEY (user_id) REFERENCES Premium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------------------------
CREATE TABLE Chat (
    chat_id INT PRIMARY KEY IDENTITY(1,1),
    sender_id INT NOT NULL,
    receiver_id INT NOT NULL,
    message_content VARCHAR(MAX) NOT NULL,
    sent_at DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (sender_id) REFERENCES Users(user_id),
    FOREIGN KEY (receiver_id) REFERENCES Users(user_id)
);
--------------------------------------------------------------ASAL-----------------------------------------------------------------------
----ADD Fllowers:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE AddFollower
--    @UserId1 INT,
--    @UserId2 INT
--AS
--BEGIN
--    INSERT INTO follower (user_id1, user_id2)
--    VALUES (@UserId1, @UserId2);
--END;
--GO
----DISPLAY ALL FOLLOWER FOR ONE PERSON:
--CREATE PROCEDURE GetFollowers
--    @user_id INT
--AS
--BEGIN
--    SELECT
--        u.user_id,
--        u.username
--    FROM
--        follower f
--    JOIN
--        Users u ON f.user_id1 = u.user_id
--    WHERE
--        f.user_id2 = @user_id;
--END;
----DISPLAY ALL FOLLOWING FOR ONE PERSON:
--CREATE PROCEDURE GetFollowing
--    @user_id INT
--AS
--BEGIN
--    SELECT
--        u.user_id,
--        u.username
--    FROM
--        follower f
--    JOIN
--        Users u ON f.user_id2 = u.user_id 
--    WHERE
--        f.user_id1 = @user_id;  
--END;

----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--------------------------------------------------------------------------------------------------------------------
----ADD Wallet to the User !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE TRIGGER CreateWalletAfterUserInsert
--ON Users
--AFTER INSERT
--AS
--BEGIN
--    INSERT INTO Digital_wallet (user_id) 
--    SELECT user_id 
--    FROM inserted;
--END;
--GO
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----------------------------------------------------------------------------------------------------------------------
----ADD Ticket For evry Concert!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE AddTicketsForConcert
--    @artist_id INT,
--    @date_concert DATETIME,
--    @price1 DECIMAL(10, 2),
--    @quantity1 INT,
--    @price2 DECIMAL(10, 2),
--    @quantity2 INT,
--    @price3 DECIMAL(10, 2),
--    @quantity3 INT
--AS
--BEGIN
--    DECLARE @i INT = 1;
--    WHILE @i <= @quantity1
--    BEGIN
--        INSERT INTO Tickets (user_id, artist_id, price, date_concert)
--        VALUES (NULL, @artist_id, @price1, @date_concert);
--        SET @i = @i + 1;
--    END

--    SET @i = 1;
--    WHILE @i <= @quantity2
--    BEGIN
--        INSERT INTO Tickets (user_id, artist_id, price, date_concert)
--        VALUES (NULL, @artist_id, @price2, @date_concert);
--        SET @i = @i + 1;
--    END

--    SET @i = 1;
--    WHILE @i <= @quantity3
--    BEGIN
--        INSERT INTO Tickets (user_id, artist_id, price, date_concert)
--        VALUES (NULL, @artist_id, @price3, @date_concert);
--        SET @i = @i + 1;
--    END
--END;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------------------------------------------------------------------------------------------------------------------------
----SHOW ALL  Available CONCERT:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--SELECT artist_id, location, [date]
--FROM Concerts
--WHERE [date] > GETDATE() and Concerts.cancel!=1;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------SHOW ALL Available Tickets:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE GetAvailableTickets
--    @artist_id INT,
--    @date_concert DATETIME
--AS
--BEGIN
--    SELECT ticket_id, price
--    FROM Tickets
--    WHERE artist_id = @artist_id
--      AND date_concert = @date_concert
--      AND is_sold = 0
--      AND Expiration = 0;
--END;
--GO

----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----BUY TICKET AND UPDATE WALLET:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE BuyTicket
--    @user_id INT,       
--    @ticket_id INT      
--AS
--BEGIN
--    BEGIN TRANSACTION;

--    DECLARE @price DECIMAL(10, 2);  
--    DECLARE @balance DECIMAL(10, 2); 

--    SELECT @price = price
--    FROM Tickets
--    WHERE ticket_id = @ticket_id
--      AND is_sold = 0
--      AND Expiration = 0;
  
--    SELECT @balance = amount
--    FROM Digital_wallet
--    WHERE user_id = @user_id;

--    IF @balance < @price
--    BEGIN
--        RAISERROR('Insufficient funds in wallet.', 16, 1);
--        ROLLBACK TRANSACTION;
--        RETURN;
--    END;
--    UPDATE Tickets
--    SET user_id = @user_id, is_sold = 1
--    WHERE ticket_id = @ticket_id;

--    UPDATE Digital_wallet
--    SET amount = amount - @price
--    WHERE user_id = @user_id;

--    COMMIT TRANSACTION;
--END;
--GO
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------------------------------------------------------------------------
----SHOW ALL TICKET THAT BUY(0):!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--DROP FUNCTION SHOWALLTICKET1;
--CREATE FUNCTION SHOWALLTICKET0 (@user_id INT)
--RETURNS TABLE
--AS
--RETURN
--(
--    SELECT 
--        t.ticket_id,
--        a.bio AS Artist_information,
--        c.[date] AS concert_date,
--        c.location,
--        t.price
--    FROM 
--        Tickets t
--    JOIN 
--        Concerts c ON t.artist_id = c.artist_id AND t.date_concert = c.[date]
--    JOIN 
--        Artists a ON t.artist_id = a.artist_id
--    WHERE 
--        t.user_id = @user_id AND t.is_sold = 1 AND t.Expiration = 0 AND t.date_concert>GETDATE() 
--);

------SHOW ALL TICKET THAT BUY(1):
--CREATE FUNCTION SHOWALLTICKET1 (@user_id INT)
--RETURNS TABLE
--AS
--RETURN
--(
--    SELECT 
--        t.ticket_id,
--        a.bio AS Artist_information,
--        c.[date] AS concert_date,
--        c.location,
--        t.price
--    FROM 
--        Tickets t
--    JOIN 
--        Concerts c ON t.artist_id = c.artist_id AND t.date_concert = c.[date]
--    JOIN 
--        Artists a ON t.artist_id = a.artist_id
--    WHERE 
--        t.user_id = @user_id AND t.is_sold = 1 AND t.Expiration = 1 AND t.date_concert<=GETDATE() 
--);
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------------------------------------------------------------------------------------------------------------------
----ADD SONG TO FSVORITE:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE ToggleFavoriteSong
--@user_id INT,
--@song_id INT
--AS
--BEGIN
---- Check if the song is already a favorite
--IF EXISTS (SELECT 1 FROM Favorite_Song WHERE user_id = @user_id AND song_id = @song_id)
--BEGIN
--	-- If the song is already a favorite, remove it
--	DELETE FROM Favorite_Song 
--	WHERE user_id = @user_id AND song_id = @song_id;
--END
--ELSE
--BEGIN
--	-- If the song is not a favorite, add it
--	INSERT INTO Favorite_Song (user_id, song_id)
--	VALUES (@user_id, @song_id);
--END
--END;
----DISPLAY FAVORITE SONGS:
--CREATE PROCEDURE GetFavoriteSongs
--    @user_id INT
--AS
--BEGIN
--    SELECT 
--        s.song_id,
--        s.title AS Song_Title
--    FROM 
--        Favorite_Song fs
--    JOIN 
--        Songs s ON fs.song_id = s.song_id
--    WHERE 
--        fs.user_id = @user_id;
--END;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
---------------------------------------------------------------------------------------------------------------------------------------------------------------
----ADD PLAY LIST TO FSVORITE:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE ToggleFavoritePlaylist
--    @user_id_added INT,
--    @user_id_owner INT,
--    @playlist_name VARCHAR(50)
--AS
--BEGIN
--    IF EXISTS (SELECT 1 FROM Favorite_Play_list WHERE user_id_owner = @user_id_owner AND user_id = @user_id_added AND [name] = @playlist_name)
--    BEGIN
--        DELETE FROM Favorite_Play_list 
--        WHERE user_id_owner = @user_id_owner AND user_id = @user_id_added AND [name] = @playlist_name;
--    END
--    ELSE
--    BEGIN
--        INSERT INTO Favorite_Play_list (user_id_owner, user_id, [name])
--        VALUES (@user_id_owner, @user_id_added, @playlist_name);
--    END
--END;
----DISPLAY  PLAY LIST  FAVORITE:
--CREATE PROCEDURE GetFavoritePlaylistsByUserID
--    @UserID INT
--AS
--BEGIN
--    SELECT
--        u.username AS OwnerUsername,  
--        fp.[name] AS PlaylistName
--    FROM
--        Favorite_Play_list fp
--    JOIN
--        Users u ON fp.user_id_owner = u.user_id
--    WHERE
--        fp.user_id = @UserID;
--END;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------------------------------------------------------------------------------------------------------------------------
----SEARCH ALBUM AND SONG:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
DROP  PROCEDURE SearchMusicAndAlbum
CREATE PROCEDURE SearchMusicAndAlbum
    @name NVARCHAR(100) = NULL,
    @artist_name NVARCHAR(100) = NULL,
    @genre NVARCHAR(50) = NULL,
    @country NVARCHAR(50) = NULL,
    @age_category CHAR(2) = NULL
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX) = '';
    
    -- Base SELECT statement for Songs
    SET @sql = '
        SELECT ''Song'' AS Type, s.song_id AS ID, s.title AS Title
        FROM Songs s
        JOIN Artists ar ON s.artist_id_added = ar.artist_id
        WHERE 1=1';
    
    -- Append conditions for Songs
    IF @name IS NOT NULL
        SET @sql = @sql + ' AND s.title LIKE ''%' + @name + '%''';
    IF @artist_name IS NOT NULL
        SET @sql = @sql + ' AND ar.bio LIKE ''%' + @artist_name + '%''';
    IF @genre IS NOT NULL
        SET @sql = @sql + ' AND s.genre LIKE ''%' + @genre + '%''';
    IF @country IS NOT NULL
        SET @sql = @sql + ' AND s.country LIKE ''%' + @country + '%''';
    IF @age_category IS NOT NULL
        SET @sql = @sql + ' AND s.Age_category = ''' + @age_category + '''';
    
    -- Add UNION ALL for Albums
    SET @sql = @sql + '
        UNION ALL
        SELECT ''Album'' AS Type, a.album_id AS ID, a.title AS Title
        FROM Albums a
        JOIN Artists ar ON a.artist_id_added = ar.artist_id
        WHERE 1=1';
    
    -- Append conditions for Albums
    IF @name IS NOT NULL
        SET @sql = @sql + ' AND a.title LIKE ''%' + @name + '%''';
    IF @artist_name IS NOT NULL
        SET @sql = @sql + ' AND ar.bio LIKE ''%' + @artist_name + '%''';
    IF @genre IS NOT NULL
        SET @sql = @sql + ' AND a.genre LIKE ''%' + @genre + '%''';
    IF @country IS NOT NULL
        SET @sql = @sql + ' AND a.country LIKE ''%' + @country + '%''';
    IF @age_category IS NOT NULL
        SET @sql = @sql + ' AND a.Age_category = ''' + @age_category + '''';
    
    -- Execute the dynamic SQL
    EXEC sp_executesql @sql;
END;
------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-----------------------------------------------------------------------------------------------------------------------------------------------
--DISPLAY SONG DETAILS:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
DROP PROCEDURE GetSongDetails;
CREATE PROCEDURE GetSongDetails
    @song_id INT
AS
BEGIN
    -- Get the song details along with the artist's username
    SELECT
        s.song_id AS ID,
        s.title AS Title,
        a.title AS AlbumTitle,
        u.username AS ArtistName,  -- Retrieve the artist's username
        s.genre AS Genre,
        s.country AS Country,
        s.Age_category AS AgeCategory,
        s.lyrics AS Lyrics,
        s.address_of_picture AS PictureAddress
    FROM Songs s
    LEFT JOIN Albums a ON s.album_id = a.album_id
    LEFT JOIN Artists ar ON s.artist_id_added = ar.artist_id
    LEFT JOIN Users u ON ar.artist_id = u.user_id  -- Assuming Artists table has a column user_id referring to Users table
    WHERE s.song_id = @song_id;
END;
GO

SELECT *
FROM Songs
exec GetSongDetails @song_id=5;
------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------------------------------------------------------------------------------------------------------------------------------------------------
------DISPLAY SONG Lyrics :!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----CREATE PROCEDURE GetSongLyrics 
----    @song_id INT
----AS
----BEGIN
----    SELECT
----        s.lyrics AS Lyrics  
----    FROM Songs s
----    WHERE s.song_id = @song_id;
----END;
------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------------------------------------------------------------------------------------------------------------------------------------------------
------ADD FUND TO WALLET:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----CREATE PROCEDURE AddFundsToWallet
----    @UserID INT,
----    @Amount DECIMAL(10, 2)
----AS
----BEGIN
----    IF EXISTS (SELECT 1 FROM Digital_wallet WHERE user_id = @UserID)
----    BEGIN
----        UPDATE Digital_wallet
----        SET amount = amount + @Amount
----        WHERE user_id = @UserID;
----    END
----    ELSE
----    BEGIN
----        INSERT INTO Digital_wallet (user_id, amount)
----        VALUES (@UserID, @Amount);
----    END
----END;
------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE GetUserPlaylists
    @user_id INT
AS
BEGIN
    SELECT 
        user_id,
        [name],
        ispublic,
        address_of_picture
    FROM 
        Play_list
    WHERE 
        user_id = @user_id;
END;
GO
----------------------------------------------------------------
CREATE PROCEDURE GetUserSong
    @user_id INT
	AS
BEGIN
    SELECT 
        song_id,title,
        address_of_picture
    FROM 
        Songs
    WHERE 
        artist_id_added = @user_id;
END;
GO
CREATE PROCEDURE GetUserAlbum
    @user_id INT
	AS
BEGIN
    SELECT 
        album_id,title,
        address_of_picture
    FROM 
        Albums
    WHERE 
        artist_id_added = @user_id;
END;
GO
CREATE PROCEDURE GetUserConcerts
    @user_id INT
	AS
BEGIN
    SELECT 
        [date],
        address_of_picture
    FROM 
        Concerts
    WHERE 
        artist_id = @user_id;
END;
GO
-------------------------------------------------------------------------------------------------------------------------------------------------
------UPDATE WALLET:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----CREATE PROCEDURE UpdateWalletBalance
----    @UserID INT,
----    @Amount DECIMAL(10, 2)
----AS
----BEGIN
----    IF EXISTS (SELECT 1 FROM Digital_wallet WHERE user_id = @UserID)
----    BEGIN
----        DECLARE @CurrentBalance DECIMAL(10, 2);
----        SELECT @CurrentBalance = amount FROM Digital_wallet WHERE user_id = @UserID;
----        IF @Amount < 0 AND @CurrentBalance + @Amount < 0
----        BEGIN
----            RAISERROR('Insufficient funds in the digital wallet.', 16, 1);
----        END
----        ELSE
----        BEGIN
----            UPDATE Digital_wallet
----            SET amount = amount + @Amount
----            WHERE user_id = @UserID;
----        END
----    END
----    ELSE
----    BEGIN
----        IF @Amount >= 0
----        BEGIN
----            INSERT INTO Digital_wallet (user_id, amount)
----            VALUES (@UserID, @Amount);
----        END
----        ELSE
----        BEGIN
----            RAISERROR('User does not have a digital wallet to deduct funds from.', 16, 1);
----        END
----    END
----END;
------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----ADD ARTIST:
CREATE PROCEDURE AddArtist
    @user_id INT,
	@bio VARCHAR(100)
AS
BEGIN
    -- Check if the user exists
    IF EXISTS (SELECT 1 FROM Users WHERE user_id = @user_id)
    BEGIN
        -- Insert into Artists table with username as bio
        INSERT INTO Artists (artist_id, bio)
        VALUES (@user_id,@bio)
    END
    ELSE
    BEGIN
        RAISERROR('User does not exist.', 16, 1);
    END
END;
GO
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CHECK USER IS ARTIST OR NOT:
CREATE PROCEDURE IsUserArtist
    @user_id INT
AS
BEGIN
    -- Declare a variable to store the result
    DECLARE @is_artist BIT = 0;

    -- Check if the user is a premium user with a valid subscription and is in the Artists table
    IF EXISTS (
        SELECT 1
        FROM Premium p
        JOIN Artists a ON p.user_id = a.artist_id
        WHERE p.user_id = @user_id
          AND p.End_time > GETDATE()
    )
    BEGIN
        SET @is_artist = 1;
    END

    -- Return the result
    SELECT @is_artist AS IsArtist;
END;
GO
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--______________________________________________________________________________________________________
--ADD SONG :
drop PROCEDURE AddSong
CREATE PROCEDURE AddSong
    @artist_id INT,
    @title VARCHAR(100),
    @album_id INT = NULL, -- Optional: If the song is part of an album
    @genre VARCHAR(50),
    @lyrics VARCHAR(MAX),
    @Age_category CHAR(2),
    @country VARCHAR(50),
  @address_of_picture VARCHAR(200),
  @can_be_added BIT ,
  @release_date DATETIME
AS
BEGIN
    -- Insert the song into the Songs table with the current date
    INSERT INTO Songs (artist_id_added, title, album_id, genre, release_date, lyrics, Age_category, country, address_of_picture, can_be_added)
    VALUES (@artist_id, @title, @album_id, @genre,@release_date, @lyrics, @Age_category, @country, @address_of_picture, @can_be_added);
END;
GO
--ADD SONG WITH OTHE ARTIST :
CREATE TYPE ArtistIdTableType AS TABLE 
(
    artist_id INT
);
CREATE PROCEDURE AddSongWithAllArtist
    @artist_id INT,
    @title VARCHAR(100),
    @album_id INT = NULL, -- Optional: If the song is part of an album
    @genre VARCHAR(50),
    @lyrics VARCHAR(MAX),
    @Age_category CHAR(2),
    @country VARCHAR(50),
    @address_of_picture VARCHAR(200),
    @can_be_added BIT,
    @other_artists ArtistIdTableType READONLY -- Table-valued parameter for other artists
AS
BEGIN
    DECLARE @song_id INT;

    BEGIN TRANSACTION;

    -- Insert the song into the Songs table with the current date
    INSERT INTO Songs (artist_id_added, title, album_id, genre, release_date, lyrics, Age_category, country, address_of_picture, can_be_added)
    VALUES (@artist_id, @title, @album_id, @genre, GETDATE(), @lyrics, @Age_category, @country, @address_of_picture, @can_be_added);

    -- Get the generated song ID
    SET @song_id = SCOPE_IDENTITY();

    -- Insert the main artist into artist_has_song
    INSERT INTO artist_has_song (song_id, artist_id)
    VALUES (@song_id, @artist_id);

    -- Insert other artists into artist_has_song
    INSERT INTO artist_has_song (song_id, artist_id)
    SELECT @song_id, artist_id FROM @other_artists;

    COMMIT TRANSACTION;
END;
GO
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--________________________________________________________________________________________________________________________________
--ADD ALBUM :
DROP PROCEDURE AddAlbumAndArtists
CREATE PROCEDURE AddAlbumAndArtists
    @artist_name VARCHAR(50),
    @album_title VARCHAR(100),
    @genre VARCHAR(50),
    @age_category CHAR(2),
    @country VARCHAR(50),
    @address_of_picture VARCHAR(200),
  @artist_id INT,
� @release_date DATETIME
AS
BEGIN
    INSERT INTO Albums (title, artist_id_added, genre, release_date, Age_category, country, address_of_picture)
    VALUES (@album_title, @artist_id, @genre,  � @release_date, @age_category, @country, @address_of_picture);
END;
GO
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--_____________________________________________________________________________________________________________________________________
--DELETE song:
CREATE PROCEDURE RemoveSong
    @MusicID INT
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;
        IF NOT EXISTS (SELECT 1 FROM Songs WHERE song_id = @MusicID)
        BEGIN
            ROLLBACK TRANSACTION;
            THROW 50001, 'Song record not found', 1;
            RETURN;
        END
        DELETE FROM Songs WHERE song_id = @MusicID;
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;
        DECLARE @ErrorMessage NVARCHAR(4000), @ErrorSeverity INT, @ErrorState INT;
        SELECT 
            @ErrorMessage = ERROR_MESSAGE(), 
            @ErrorSeverity = ERROR_SEVERITY(), 
            @ErrorState = ERROR_STATE();
        RAISERROR (@ErrorMessage, @ErrorSeverity, @ErrorState);
    END CATCH
END;
GO
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--______________________________________________________________________________________________________________________
--DELETE ALBUM:
CREATE PROCEDURE RemoveAlbum
    @AlbumID INT
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;
        IF NOT EXISTS (SELECT 1 FROM Albums WHERE album_id = @AlbumID)
        BEGIN
            THROW 50001, 'Album record not found', 1;
        END
        DELETE FROM Albums WHERE album_id = @AlbumID;
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
        DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        DECLARE @ErrorSeverity INT = ERROR_SEVERITY();
        DECLARE @ErrorState INT = ERROR_STATE();
        RAISERROR (@ErrorMessage, @ErrorSeverity, @ErrorState);
    END CATCH
END;
--____________________________________________________________________________________________________________________
DROP PROCEDURE AddNewConcert
--ADD CONCERT FOR A ARTIST:
CREATE PROCEDURE AddNewConcert
    @ArtistID INT,
    @ConcertDate DATETIME,
    @ConcertLocation NVARCHAR(100)
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;

        -- Check if the artist exists
        IF NOT EXISTS (SELECT 1 FROM Artists WHERE artist_id = @ArtistID)
        BEGIN
            THROW 50002, 'Artist ID is invalid.', 1;
        END

        -- Check if the artist already has a concert scheduled on this date
        IF EXISTS (
            SELECT 1
            FROM Concerts 
            WHERE artist_id = @ArtistID AND [date] = @ConcertDate
        )
        BEGIN
            THROW 50003, 'Artist already has a concert scheduled on this date.', 1;
        END
        -- Insert the concert into Concerts table
        INSERT INTO Concerts (artist_id, location, date, address_of_picture)
        VALUES (@ArtistID, @ConcertLocation, @ConcertDate, NULL);

        -- Commit transaction
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
        THROW;
    END CATCH
END;
GO
DROP PROCEDURE GetSongsByAlbumID
CREATE PROCEDURE GetSongsByAlbumID
    @AlbumID INT
AS
BEGIN
    SET NOCOUNT ON;

    SELECT song_id AS ID , address_of_picture AS addr,title As song_title
    FROM Songs
    WHERE album_id = @AlbumID;
END;
GO

--__________________________________________________________________________________________________________________
--CANCEL CONCER AND RETURN MONEY:
CREATE PROCEDURE CancelConcert 
    @artist_id INT,
    @date_concert DATETIME
AS
BEGIN
    -- Start a transaction
    BEGIN TRANSACTION;

    BEGIN TRY
        -- Update the concert to indicate it is cancelled
        UPDATE Concerts
        SET cancel = 1
        WHERE artist_id = @artist_id AND [date] = @date_concert;

        -- Refund ticket amounts to digital wallets for sold tickets
        UPDATE dw
        SET dw.amount = dw.amount + t.price
        FROM Digital_wallet dw
        JOIN Tickets t ON dw.user_id = t.user_id
        WHERE t.artist_id = @artist_id AND t.date_concert = @date_concert AND t.is_sold = 1;

        -- Invalidate sold tickets
        UPDATE Tickets
        SET Expiration = 0
        WHERE artist_id = @artist_id AND date_concert = @date_concert AND is_sold = 1;

        -- Delete unsold tickets
        DELETE FROM Tickets
        WHERE artist_id = @artist_id AND date_concert = @date_concert AND is_sold = 0;

        -- Commit the transaction
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        -- Rollback the transaction in case of error
        ROLLBACK TRANSACTION;
        -- Raise the error
        THROW;
    END CATCH
END;
GO

-------------------------------------------------------------------------------------------ZAHRA--------------------------------------------------------------------------------------
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
END;
GO
------------------***********------------------------
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
GO
-------------------------------------------------------
DROP PROCEDURE CreatePlaylist
CREATE PROCEDURE CreatePlaylist
    @user_id INT,
    @playlist_name NVARCHAR(50),
    @is_public BIT,
  @address_of_picture VARCHAR(100)
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
            INSERT INTO Play_list (user_id, [name], ispublic,address_of_picture)
            VALUES (@user_id, @playlist_name, @is_public,@address_of_picture);
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
GO
------------------***********------------------------
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
GO
------------------***********------------------------
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
GO
------------------***********------------------------
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
END;
GO
------------------***********------------------------
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
END;
GO
------------------***********------------------------
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
END;
GO
------------------***********------------------------
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
END;
GO
------------------***********------------------------
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
END;
GO
------------------***********------------------------

CREATE PROCEDURE LikePlaylist
    @user_id INT,
    @playlist_name NVARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;

    IF NOT EXISTS (
        SELECT 1
        FROM Like_Play_list
        WHERE user_id = @user_id AND [name] = @playlist_name
    )
    BEGIN
        INSERT INTO Like_Play_list (user_id, [name])
        VALUES (@user_id, @playlist_name);

    END

END;
GO
------------------***********------------------------
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
GO
DROP PROCEDURE InsertUserGenreLikes
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
GO
------------------***********------------------------
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
GO
------------------***********------------------------
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
GO
------------------***********------------------------
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

    SELECT TOP 10
        S.song_id,
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
        GL.Likes_Count DESC, NEWID();-- Order by likes count of genre and then randomize
END;
GO
------------------***********------------------------**************************************************************************************
CREATE PROCEDURE CheckSSS
    @username VARCHAR(50),
    @password VARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;
    DECLARE @user_id INT;
    DECLARE @is_artist VARCHAR(20);

    SELECT @user_id = user_id
    FROM Users
    WHERE username = @username AND [password] = @password;

    IF @user_id IS NOT NULL
    BEGIN
        SELECT @user_id AS User_Id,
            CASE
                WHEN EXISTS (SELECT 1 FROM Premium WHERE user_id = @user_id AND GETDATE() < End_time) THEN 'Premium User'
                ELSE 'Regular User'
            END AS User_Type,
            CASE
                WHEN EXISTS (SELECT 1 FROM Artists WHERE artist_id = @user_id) THEN 'Artist'
                ELSE 'Not an Artist'
            END AS Artist_Status;
    END
    ELSE
    BEGIN
        SELECT NULL AS User_Id, 'Invalid User' AS User_Type, 'N/A' AS Artist_Status;
    END
END;
GO
------------------***********------------------------
--CREATE PROCEDURE GetRecommendedAlb
--(
--    @user_id INT
--)
--AS
--BEGIN
--    SELECT TOP 10
--        A.album_id,
--        A.title AS album_title,
--        U.username AS artist_name,
--        A.genre,
--        A.release_date
--    FROM 
--        Albums A
--    INNER JOIN 
--        artist_has_album AHA ON A.album_id = AHA.album_id
--	INNER JOIN	 User_Artist_Likes UAL ON  UAL.user_id = @user_id
--    INNER JOIN 
--        Artists AR ON AHA.artist_id = AR.artist_id
--    INNER JOIN 
--        Users U ON AR.artist_id = U.user_id
--    WHERE 
--        A.album_id  IN (SELECT album_id FROM Like_album WHERE user_id = @user_id)
--    ORDER BY 
--        NEWID(); -- Random order for diversity in recommendations
--END;

--------------------------------------------------------------------------
--CREATE PROCEDURE GetRecommendedSongsByArtistLike
--(
--    @user_id INT
--)
--AS
--BEGIN
--    SELECT TOP 10
--        S.song_id,
--        S.title AS song_title,
--        U.username AS artist_name,
--        S.genre,
--        S.release_date
--    FROM
--        Songs S
--    INNER JOIN
--        artist_has_song ASHS ON ASHS.song_id = S.song_id
--    INNER JOIN
--        Artists A ON ASHS.artist_id = A.artist_id
--    INNER JOIN
--        User_Artist_Likes UAL ON A.artist_id = UAL.artist_id
--	INNER JOIN 
--        Users U ON A.artist_id = U.user_id
--    WHERE
--        UAL.user_id = @user_id
--    AND
--        S.song_id IN (SELECT song_id FROM Like_song WHERE user_id = @user_id)
--    ORDER BY
--        UAL.Likes_Count DESC, NEWID();
--END;
--GO
--CREATE PROCEDURE GetRecommendedSongsByGenreLike
--(
--    @user_id INT
--)
--AS
--BEGIN
--    WITH GenreLikes AS (
--        SELECT 
--            UGL.user_id,
--            S.song_id,
--            S.title AS song_title,
--            S.genre,
--            UGL.Likes_Count
--        FROM 
--            User_Genre_Likes UGL
--        INNER JOIN 
--            Songs S ON UGL.song_id = S.song_id
--        WHERE 
--            UGL.user_id = @user_id
--    )
    
--    SELECT TOP 10
--        S.song_id,
--        S.title AS song_title,
--        U.username AS artist_name,
--        S.genre,
--        S.release_date
--    FROM 
--        Songs S
--    INNER JOIN 
--        artist_has_song ASHS ON ASHS.song_id = S.song_id
--    INNER JOIN 
--        Artists A ON ASHS.artist_id = A.artist_id
--    INNER JOIN 
--        GenreLikes GL ON S.song_id = GL.song_id
--	INNER JOIN 
--        Users U ON A.artist_id = U.user_id
--    WHERE 
--        S.song_id IN (SELECT song_id FROM Like_song WHERE user_id = @user_id) -- Exclude songs liked by the user
--    ORDER BY 
--        GL.Likes_Count DESC, NEWID(); -- Order by likes count of genre and then randomize
--END;
--GO
----------------------------------------------
CREATE PROCEDURE CheckUserByEmailAndUsername
    @username VARCHAR(50),
    @email VARCHAR(100)
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @user_id INT;
    SELECT @user_id = user_id
    FROM Users
    WHERE username = @username AND email = @email;
    SELECT 
        CASE
            WHEN @user_id IS NOT NULL THEN 'Valid'
            ELSE 'Invalid'
        END AS Result;
END;
GO
------------------------------------------------
CREATE PROCEDURE UpdatePassword
    @username VARCHAR(50),
    @newPassword VARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;

    UPDATE Users
    SET [password] = @newPassword
    WHERE username = @username;

    SELECT @@ROWCOUNT AS AffectedRows; -- Return the number of affected rows
END;
GO
--------------------------------------------------------
CREATE PROCEDURE GetPlaylistsByUserId
    @user_id INT
AS
BEGIN
    SET NOCOUNT ON;

    SELECT [name], address_of_picture
    FROM Play_list
    WHERE user_id = @user_id;
END;
GO
--------------------------------------------
DROP PROCEDURE GetSongsInPlaylist
CREATE PROCEDURE GetSongsInPlaylist
    @playlist_name VARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;

    SELECT s.title AS Song_Title
    FROM Playlist_has_song ps
    INNER JOIN Songs s ON ps.song_id = s.song_id
    WHERE ps.[name] = @playlist_name;
END;
GO
--------------------------------------
CREATE PROCEDURE GetSongsByPlaylist
    @playlist_name VARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;

    SELECT  s.title
    FROM Songs s
    INNER JOIN Playlist_has_song ps ON s.song_id = ps.song_id
    INNER JOIN Play_list pl ON ps.user_id = pl.user_id AND ps.[name] = pl.[name]
    WHERE pl.[name] = @playlist_name;
END;
----------------------------------------------
GO
CREATE PROCEDURE GetFriendPlaylists
    @user_id INT
AS
BEGIN
    SET NOCOUNT ON;
    CREATE TABLE #FriendUserIds (
        user_id INT
    );
    INSERT INTO #FriendUserIds (user_id)
    SELECT user_id2
    FROM Friend
    WHERE user_id1 = @user_id AND accept = 1;

    SELECT pl.[name] AS Playlist_Name
    FROM Play_list pl
    INNER JOIN #FriendUserIds f ON pl.user_id = f.user_id;
    DROP TABLE #FriendUserIds;
END;
GO
---------------------------------------------
CREATE PROCEDURE SendMessageS
    @SenderID INT,
    @ReceiverUsername VARCHAR(50),
    @MessageContent VARCHAR(MAX)
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;

        DECLARE @ReceiverID INT;

        -- Check if SenderID exists in Users table
        IF NOT EXISTS (SELECT 1 FROM Users WHERE user_id = @SenderID)
        BEGIN
            THROW 50000, 'Sender ID is invalid.', 1;
        END;

        -- Get ReceiverID from Users table based on ReceiverUsername
        SELECT @ReceiverID = user_id
        FROM Users
        WHERE username = @ReceiverUsername;

        -- Check if ReceiverID is found
        IF @ReceiverID IS NULL
        BEGIN
            THROW 50001, 'Receiver Username is invalid.', 1;
        END;

        -- Check if the users are friends and the friendship request is accepted
        IF NOT EXISTS (
            SELECT 1
            FROM Friend
            WHERE (user_id1 = @SenderID AND user_id2 = @ReceiverID AND accept = 1)
               OR (user_id1 = @ReceiverID AND user_id2 = @SenderID AND accept = 1)
        )
        BEGIN
            THROW 50002, 'Users are not friends or friendship request is not accepted.', 1;
        END;

        -- Insert the message into the Chat table
        INSERT INTO Chat (sender_id, receiver_id, message_content, sent_at)
        VALUES (@SenderID, @ReceiverID, @MessageContent, GETDATE());

        -- Commit transaction
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        -- Rollback transaction in case of error
        ROLLBACK TRANSACTION;

        -- Raise the error again to notify the caller
        THROW;
    END CATCH
END;

GO
--********
CREATE PROCEDURE GetChatsBetweenUser
    @sender_id INT,
    @receiver_username NVARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;
	DECLARE @user_id2 INT;
    SELECT @user_id2 = user_id
    FROM Users
    WHERE username = @receiver_username;
	IF @user_id2 IS NULL
    BEGIN
        RAISERROR ('User with the specified username does not exist.', 16, 1);
        RETURN;
    END
    SELECT  message_content, sent_at
    FROM Chat
    WHERE (sender_id = @sender_id AND receiver_id = @user_id2)
       OR (sender_id = @user_id2 AND receiver_id = @sender_id)
    ORDER BY sent_at;
END;
GO
--******************************************************
CREATE PROCEDURE SendFriendRequest1
    @user_id1 INT,
    @friend_username NVARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;

    -- Get user_id2 from the username
    DECLARE @user_id2 INT;
    SELECT @user_id2 = user_id
    FROM Users
    WHERE username = @friend_username;

    -- Check if the user with given username exists
    IF @user_id2 IS NULL
    BEGIN
        RAISERROR ('User with the specified username does not exist.', 16, 1);
        RETURN;
    END

    -- Check if there is already a friend request or friendship exists
    DECLARE @existing_accept INT;
    SELECT @existing_accept = accept
    FROM Friend
    WHERE (user_id1 = @user_id1 AND user_id2 = @user_id2)
       OR (user_id1 = @user_id2 AND user_id2 = @user_id1);

    IF @existing_accept IS NOT NULL
    BEGIN
        IF @existing_accept = 1
        BEGIN
            -- Friendship already exists
            RAISERROR ('These users are already friends.', 16, 1);
            RETURN;
        END
        ELSE IF @existing_accept = 3
        BEGIN
            -- Friend request already sent, waiting for acceptance
            RAISERROR ('Friend request already sent. Waiting for acceptance.', 16, 1);
            RETURN;
        END
    END
    -- Insert a new friend request
    INSERT INTO Friend (user_id1, user_id2, accept)
    VALUES (@user_id1, @user_id2, 3);  

    PRINT 'Friend request sent successfully.';
END;
GO
--**********************
CREATE PROCEDURE GetFriendSRequest
    @target_user_id INT
AS
BEGIN
    SET NOCOUNT ON;

    SELECT 
        CASE 
            WHEN F.user_id1 = @target_user_id THEN U2.username 
            WHEN F.user_id2 = @target_user_id THEN U1.username 
        END AS username
    FROM 
        Friend F
    LEFT JOIN 
        Users U1 ON F.user_id1 = U1.user_id
    LEFT JOIN 
        Users U2 ON F.user_id2 = U2.user_id
    WHERE 
        (F.user_id1 = @target_user_id OR F.user_id2 = @target_user_id) AND F.accept = 3;
END;
GO
--------------------------------------------
CREATE PROCEDURE AcceptFriendRequests
    @target_user_id INT,
    @requester_username VARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @requester_user_id INT;
    SELECT @requester_user_id = user_id
    FROM Users
    WHERE username = @requester_username;
    IF @requester_user_id IS NULL
    BEGIN
        RAISERROR('Requester user not found.', 16, 1);
        RETURN;
    END;
    UPDATE Friend
    SET accept = 1 
    WHERE (user_id1 =@target_user_id  AND user_id2 = @requester_user_id) OR (user_id1 =@requester_user_id AND user_id2 = @target_user_id  );
END;

GO
CREATE PROCEDURE DeclineFriendRequest
    @current_user_id INT,
    @requester_username VARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @requester_user_id INT;
    SELECT @requester_user_id = user_id
    FROM Users
    WHERE username = @requester_username;
    IF @requester_user_id IS NULL
    BEGIN
        RAISERROR('Requester user not found.', 16, 1);
        RETURN;
    END;
    UPDATE Friend
    SET accept = 0
    WHERE user_id1 =  @current_user_id AND user_id2 = @requester_user_id;
END;
GO


-------------------**************---------------------------
CREATE PROCEDURE GetFriendsNames
    @user_id INT
AS
BEGIN
    SELECT u.username AS friend_name
    FROM Users u
    INNER JOIN (
        SELECT user_id2 AS friend_id FROM Friend WHERE user_id1 = @user_id AND accept = 1
        UNION ALL
        SELECT user_id1 AS friend_id FROM Friend WHERE user_id2 = @user_id AND accept = 1
    ) f ON u.user_id = f.friend_id;
END;
GO
------------------------------------premum---------------------------------

----------------------------------------------------------------------Mahrokh---------------------------------------------------------------------
CREATE PROCEDURE GetFavoriteSongsAndAlbums
    @user_id INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Retrieve favorite songs
    SELECT 
        s.song_id, 
        s.title AS item_name, 
        'Song' AS item_type 
    FROM 
        Like_song ls
    JOIN 
        Songs s ON ls.song_id = s.song_id
    WHERE 
        ls.user_id = @user_id

    UNION ALL

    -- Retrieve favorite albums
    SELECT 
        a.album_id, 
        a.title AS item_name, 
        'Album' AS item_type 
    FROM 
        Like_album la
    JOIN 
        Albums a ON la.album_id = a.album_id
    WHERE 
        la.user_id = @user_id;
END;
GO


--------------------------------------------------------
-- Procedure to get all valid tickets
CREATE PROCEDURE GetValidTickets
    @user_id INT
AS
BEGIN
    SELECT 
        t.ticket_id,
        a.bio AS Artist_information,
        c.[date] AS concert_date,
        c.location,
        t.price
    FROM 
        Tickets t
    JOIN 
        Concerts c ON t.artist_id = c.artist_id AND t.date_concert = c.[date]
    JOIN 
        Artists a ON t.artist_id = a.artist_id
    WHERE 
        t.user_id = @user_id AND t.is_sold = 1 AND t.Expiration = 0 AND t.date_concert > GETDATE();
END;
GO
--------------------------------------------------------
-- Procedure to get all expired tickets
CREATE PROCEDURE GetExpiredTickets
    @user_id INT
AS
BEGIN
    SELECT 
        t.ticket_id,
        a.bio AS Artist_information,
        c.[date] AS concert_date,
        c.location,
        t.price
    FROM 
        Tickets t
    JOIN 
        Concerts c ON t.artist_id = c.artist_id AND t.date_concert = c.[date]
    JOIN 
        Artists a ON t.artist_id = a.artist_id
    WHERE 
        t.user_id = @user_id AND t.is_sold = 1 AND t.Expiration = 1 AND t.date_concert <= GETDATE();
END;
GO






----------------------------------------------------------------------Random Inserts---------------------------------------------------------------------

INSERT INTO Users (username, [password], email, birth_date, [location])
VALUES ('user1', 'password1', 'user1@example.com', '1990-01-01', 'New York'),
       ('user2', 'password2', 'user2@example.com', '1992-05-15', 'Los Angeles'),
       ('user3', 'password3', 'user3@example.com', '1985-08-20', 'Chicago');

INSERT INTO Premium (user_id, Start_time, End_time)
VALUES (1, '2023-01-01 10:00:00', '2023-12-31 23:59:59'),
       (2, '2023-02-15 08:30:00', '2023-12-31 23:59:59'),
       (3, '2023-03-20 12:00:00', '2023-12-31 23:59:59');

INSERT INTO Play_list (user_id, [name], ispublic, address_of_picture)
VALUES (1, 'My Playlis', 1, '/images/my_playlist.jpg'),
       (1, 'Favorite', 1, '/images/favorites.jpg'),
       (2, 'Road Trip Mi', 0, '/images/road_trip.jpg');

--INSERT INTO Digital_wallet (user_id, amount)
--VALUES (1, 100.00),
--       (2, 50.00),
--       (3, 75.00);
UPDATE Digital_wallet
SET amount = CASE 
    WHEN user_id = 1 THEN 200.00
    WHEN user_id = 2 THEN 150.00
    WHEN user_id = 3 THEN 175.00
END
WHERE user_id IN (1, 2, 3);


INSERT INTO Artists (artist_id, bio)
VALUES (1, 'Bio for Artist 1'),
       (2, 'Bio for Artist 2'),
       (3, 'Bio for Artist 3');

INSERT INTO Albums (title, artist_id_added, genre, release_date, Age_category, country, address_of_picture)
VALUES ('Album 1', 1, 'Pop', '2023-01-15', 'PG', 'USA', '/images/album1.jpg'),
       ('Album 2', 2, 'Rock', '2023-02-20', 'PG', 'UK', '/images/album2.jpg'),
       ('Album 3', 3, 'Electronic', '2023-03-10', 'PG', 'Canada', '/images/album3.jpg');

INSERT INTO Songs (artist_id_added, title, album_id, genre, release_date, lyrics, Age_category, country, address_of_picture, can_be_added)
VALUES (1, 'Song 1', 1, 'Pop', '2023-01-15', 'Lyrics for Song 1', 'PG', 'USA', '/images/song1.jpg', 1),
       (2, 'Song 2', 2, 'Rock', '2023-02-20', 'Lyrics for Song 2', 'PG', 'UK', '/images/song2.jpg', 1),
       (3, 'Song 3', 3, 'Electronic', '2023-03-10', 'Lyrics for Song 3', 'PG', 'Canada', '/images/song3.jpg', 1);



---- Insert sample data into the Concerts table
INSERT INTO Concerts (artist_id, location, date, cancel, address_of_picture) VALUES
(1, 'Location 1', '2025-08-01 19:00:00', 0, 'address1.jpg'),
(2, 'Location 2', '2025-08-15 19:00:00', 0, 'address2.jpg'),
(3, 'Location 3', '2025-09-01 19:00:00', 0, 'address3.jpg'),
(1, 'Location 1', '2022-07-01 19:00:00', 0, 'address4.jpg'),
(2, 'Location 2', '2022-07-15 19:00:00', 0, 'address5.jpg');

---- Inserting new rows into the Tickets table


---- Insert into Concerts table
INSERT INTO Concerts (artist_id, location, [date], cancel, address_of_picture) VALUES
(1, 'Venue 2', '2025-08-15 19:00:00', 0, 'path/to/image2.png'),
(2, 'Venue 3', '2025-09-01 19:00:00', 0, 'path/to/image3.png'),
(3, 'Venue 1', '2025-09-10 19:00:00', 0, 'path/to/image1.png'),
(3, 'Venue 2', '2025-10-01 19:00:00', 0, 'path/to/image2.png'),
(1, 'Venue 3', '2025-10-15 19:00:00', 0, 'path/to/image3.png'),
(2, 'Venue 1', '2025-11-01 19:00:00', 0, 'path/to/image1.png'),
(3, 'Venue 2', '2025-11-15 19:00:00', 0, 'path/to/image2.png'),
(1, 'Venue 3', '2025-12-01 19:00:00', 0, 'path/to/image3.png');

-- Insert into Tickets table
-----drop table Tickets;
INSERT INTO Tickets (user_id, artist_id, price, Expiration, is_sold, date_concert) VALUES
(NULL, 1, 100.00, 0, 0, '2025-08-01 19:00:00'),
(NULL, 2, 50.00, 0, 0, '2025-08-15 19:00:00'),
(NULL, 3, 150.00, 0, 0, '2025-09-01 19:00:00'),
(NULL, 1, 120.00, 0, 0, '2025-09-10 19:00:00'),
(NULL, 2, 60.00, 0, 0, '2025-10-01 19:00:00'),
(NULL, 3, 170.00, 0, 0, '2025-10-15 19:00:00'),
(NULL, 1, 130.00, 0, 0, '2025-11-01 19:00:00'),
(NULL, 2, 70.00, 0, 0, '2025-11-15 19:00:00'),
(NULL, 3, 180.00, 0, 0, '2025-12-01 19:00:00');




--INSERT INTO Favorite_Play_list (user_id, user_id_owner, [name])
--VALUES (1, 2, 'Favorites'),
--       (2, 1, 'Road Trip Mix'),
--       (3, 1, 'Favorites');

--INSERT INTO Comment_Play_list (user_id, [name], [text])
--VALUES (1, 'My Playlist', 'Great selection of songs!'),
--       (2, 'Favorites', 'Love this playlist!'),
--       (3, 'Road Trip Mix', 'Perfect for long drives.');

--INSERT INTO Like_Play_list (user_id, [name])
--VALUES (1, 'My Playlist'),
--       (2, 'Favorites'),
--       (3, 'Road Trip Mix');

--INSERT INTO Friend (user_id1, user_id2, accept)
--VALUES (1, 2, 1),
--       (2, 3, 1),
--       (3, 1, 0);

--INSERT INTO Message_Premium (user_id1, user_id2, [text])
--VALUES (1, 2, 'Hey, how are you?'),
--       (2, 1, 'Doing great, thanks!'),
--       (3, 1, 'Need to catch up soon.');

--INSERT INTO follower (user_id1, user_id2)
--VALUES (1, 2),
--       (2, 3),
--       (3, 1);

--INSERT INTO Comment_Album (user_id, album_id, [text])
--VALUES (1, 1, 'Awesome album!'),
--       (2, 2, 'Great tracks!'),
--       (3, 3, 'Love the beats.');

--INSERT INTO artist_has_song (song_id, artist_id)
--VALUES (1, 1),
--       (2, 2),
--       (3, 3);

--INSERT INTO Playlist_has_song ([name], song_id, user_id)
--VALUES ('My Playlist', 1, 1),
--       ('Favorites', 2, 2),
--       ('Road Trip Mix', 3, 3);

--INSERT INTO Favorite_Song (user_id, song_id)
--VALUES (1, 1),
--       (2, 2),
--       (3, 3);

--INSERT INTO Like_album (user_id, album_id)
--VALUES (1, 1),
--       (2, 2),
--       (3, 3);

--INSERT INTO User_Artist_Likes (user_id, artist_id, song_id, Likes_Count)
--VALUES (1, 1, 1, 100),
--       (2, 2, 2, 150),
--       (3, 3, 3, 80);

--INSERT INTO User_Genre_Likes (user_id, song_id, Likes_Count)
--VALUES (1, 1, 200),
--       (2, 2, 120),
--       (3, 3, 90);








--__________________________________________________________________check___________________________________________________________--
SELECT*
FROM Comment_song;
SELECT *
FROM Songs
exec GetCommentsForSong @song_id=48;
exec GetCommentsForSong @song_id=6;
exec AddCommentToSong @user_id= 2, @song_id = 6,@text='kjhkjhgju';
EXEC AddSongToPlaylist @user_id =1, @playlist_name = 'Favorite', @song_id = 5;
SELECT*
exec ViewPlaylistSongsWithArtists @playlist_name='Favorite',@user_id=1;
SELECT*
FROM Playlist_has_song;
SELECT*
FROM Play_list
SELECT*
FROM Favorite_Song
exec InsertUserGenreLikes
exec LikeSong  @user_id=3,
    @song_id =5;
SELECT *
FROM Like_song;
exec InsertUserArtistLikes;
SELECT *
FROM Albums;
exec AddAlbumAndArtists
    @artist_name =asal,
    @album_title= 'aaa',
    @genre ='ddd',
    @age_category ='po',
    @country ='kp',
    @address_of_picture ='ijuh',
	@artist_id=1;
	exec SearchMusicAndAlbum @genre='Rock';