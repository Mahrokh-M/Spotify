------ DELETE FOREIGN KEY constraints
----DECLARE @sql NVARCHAR(MAX) = '';

----SELECT @sql = @sql + 'ALTER TABLE ' + t.name + ' DROP CONSTRAINT ' + fk.name + '; '
----FROM sys.foreign_keys AS fk
----JOIN sys.tables AS t ON fk.parent_object_id = t.object_id;

----EXEC sp_executesql @sql;
----------
----DECLARE @sql NVARCHAR(MAX) = '';

----SELECT @sql = @sql + 'DROP TABLE ' + t.name + '; '
----FROM sys.tables AS t;

----EXEC sp_executesql @sql;
-----------------------------------
----SELECT DB_NAME() AS CurrentDatabase;
----------------------------------------------------------------------------------------------------------------------
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
--	address_of_picture VARCHAR(100),
--    FOREIGN KEY (user_id) REFERENCES Users(user_id),
--	PRIMARY KEY(user_id,[name])
--);
-------------------------------------------------------
--CREATE TABLE Digital_wallet (
--    Digital_wallet_id INT PRIMARY KEY IDENTITY,
--    user_id INT,
--    amount DECIMAL(10, 2) DEFAULT 0.00,
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
--	address_of_picture VARCHAR(100),
--	FOREIGN KEY (artist_id_added) REFERENCES Artists(artist_id)
--);
-------------------------------------------------------
--CREATE TABLE Songs (
--    song_id INT PRIMARY KEY IDENTITY,
--	artist_id_added INT,
--	title VARCHAR(100)  NOT NULL,
--	album_id INT NULL,
--    genre VARCHAR(50),
--    release_date DATE,
--    lyrics VARCHAR(MAX),
--	Age_category CHAR(2),
--	country VARCHAR(50),
--	address_of_picture VARCHAR(100),
--    can_be_added BIT DEFAULT 0,
--	FOREIGN KEY (album_id) REFERENCES Albums(album_id)ON DELETE CASCADE,
--	FOREIGN KEY (artist_id_added) REFERENCES Artists(artist_id)
--);
------------------------------------------------------
--CREATE TABLE Concerts (
--    artist_id INT ,
--    [location] VARCHAR(100),
--    [date] DATETIME ,
--	address_of_picture VARCHAR(100),
--    FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
--	PRIMARY KEY (artist_id,[date])
--);
------------------------------------------------------
--CREATE TABLE Tickets (
--    ticket_id INT PRIMARY KEY IDENTITY,
--    user_id INT,
--	artist_id INT,
--	price DECIMAL(10, 2),
--    Expiration BIT DEFAULT 1,-- 1
--	is_sold BIT DEFAULT 0,-- 0 
--	date_concert DATETIME ,--**
--    FOREIGN KEY (user_id) REFERENCES Users(user_id),
--	FOREIGN KEY (artist_id,date_concert) REFERENCES Concerts(artist_id,[date])
--);
------------------------------------------------------
--CREATE TABLE Favorite_Play_list(
--    user_id INT,
--	user_id_owner INT,
--    [name] VARCHAR(50) NOT NULL,
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--    FOREIGN KEY (user_id_owner, [name]) REFERENCES Play_list(user_id, [name]),
--    PRIMARY KEY (user_id_owner,user_id, [name])
--);
-----------------------------------------------------
--CREATE TABLE Comment_Play_list(
--    user_id INT ,
--	[name] VARCHAR(50) NOT NULL ,
--	[text] VARCHAR(100),
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
--	PRIMARY KEY (user_id,[name])
--);
-----------------------------------------------------
--CREATE TABLE Like_Play_list(
--    user_id INT ,
--	[name] VARCHAR(50) NOT NULL,
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
--	PRIMARY KEY(user_id,[name])
--);
------------------------------------------------------
--CREATE TABLE Friend(
--    user_id1 INT,
--	user_id2 INT,
--	accept BIT DEFAULT 0,
--    FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
--	FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
--	PRIMARY KEY(user_id1,user_id2)
--);
------------------------------------------------------
--CREATE TABLE Message_Premium (
--    user_id1 INT,
--    user_id2 INT,
--    [text] VARCHAR(100),
--	CreatedDate DATETIME DEFAULT GETDATE(),
--    FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
--    FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
--    PRIMARY KEY (user_id1, user_id2)
--);
---------------------------------------------------------
--CREATE TABLE follower(
--	user_id1 INT,
--	user_id2 INT,
--    FOREIGN KEY (user_id1) REFERENCES Premium(user_id),
--	FOREIGN KEY (user_id2) REFERENCES Premium(user_id),
--	PRIMARY KEY(user_id1,user_id2)
--);
---------------------------------------------------------
--CREATE TABLE Comment_Album (
--    user_id INT,                  
--    album_id INT,
--    [text] VARCHAR(100),
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--    FOREIGN KEY (album_id) REFERENCES Albums(album_id)ON DELETE CASCADE,
--	PRIMARY KEY(user_id,album_id)
--);
--------------------------------------------------------
--CREATE TABLE artist_has_song(
--    song_id INT ,
--	artist_id INT ,
--    FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
--	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
--	PRIMARY KEY(song_id,artist_id)
--);
---------------------------------------------------------
--CREATE TABLE artist_has_album(
--    album_id INT,
--	artist_id INT ,
--    FOREIGN KEY (album_id) REFERENCES Albums(album_id)ON DELETE CASCADE,
--	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
--	PRIMARY KEY(album_id,artist_id)
--);
---------------------------------------------------------
--CREATE TABLE Playlist_has_song(
--    [name]  VARCHAR(50),
--	song_id INT ,
--	user_id INT ,
--    FOREIGN KEY (user_id,[name]) REFERENCES Play_list(user_id,[name]),
--	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
--	PRIMARY KEY([name],song_id,user_id)
--);
---------------------------------------------------------
--CREATE TABLE Favorite_Song(
--    user_id INT,
--	song_id INT,
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
--	PRIMARY KEY(user_id,song_id)
--);
---------------------------------------------------------
--CREATE TABLE Comment_song(
--    song_id INT,
--	[text] VARCHAR(100),
--	user_id INT,
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
--	PRIMARY KEY(user_id,song_id)
--);
---------------------------------------------------------
--CREATE TABLE Like_song(
--    song_id INT ,
--	user_id INT ,
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
--	PRIMARY KEY(user_id,song_id)
--);
---------------------------------------------------------
--CREATE TABLE Like_album(
--    user_id INT ,
--	album_id INT ,
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (album_id) REFERENCES Albums(album_id)ON DELETE CASCADE,
--	PRIMARY KEY(user_id,album_id)

--);
---------------------------------------------------------
----CREATE TABLE Return_money(
----    Digital_wallet_id INT ,
----	artist_id INT  ,
----    [date] DATETIME ,
----	amount DECIMAL(10, 2), --**
----    FOREIGN KEY (artist_id,[date]) REFERENCES Concerts(artist_id,[date]),
----	FOREIGN KEY (Digital_wallet_id) REFERENCES Digital_wallet(Digital_wallet_id),
----	PRIMARY KEY(artist_id,Digital_wallet_id,[date])
----);
---------------------------------------------------------
--CREATE TABLE Play_song(
--   song_id INT ,
--	user_id INT ,
--    FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (song_id) REFERENCES Songs(song_id)ON DELETE CASCADE,
--	PRIMARY KEY(user_id,song_id)
--);
-------------------------------------------------------------------------
--CREATE TABLE User_Artist_Likes (
--	user_id INT,
--	artist_id INT,
--	song_id INT ,
--	Likes_Count INT,
--	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
--	FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
--	PRIMARY KEY(user_id,song_id)
--);
-------------------------------------------------------------------------
--CREATE TABLE User_Genre_Likes (
--	user_id INT,
--	song_id INT ,
--	Likes_Count INT,
--	FOREIGN KEY (user_id) REFERENCES Premium(user_id),
--	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
--	PRIMARY KEY(user_id,song_id)
--);
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
--WHERE [date] > GETDATE();
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----SHOW ALL Available Tickets:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
--      AND Expiration = 1;
--END;
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
--      AND Expiration = 1;
  
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
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------------------------------------------------------------------------
----SHOW ALL TICKET THAT BUY(0):!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
--        t.user_id = @user_id AND t.is_sold = 1 AND t.Expiration = 0
--);

----SHOW ALL TICKET THAT BUY(1):
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
--        t.user_id = @user_id AND t.is_sold = 1 AND t.Expiration = 1
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
--CREATE PROCEDURE SearchMusicAndAlbum
--    @name NVARCHAR(100) = NULL,
--    @artist_name NVARCHAR(100) = NULL,
--    @genre NVARCHAR(50) = NULL,
--    @country NVARCHAR(50) = NULL,
--    @age_category CHAR(2) = NULL
--AS
--BEGIN
--    DECLARE @sql NVARCHAR(MAX) = '';
    
--    -- Base SELECT statement for Songs
--    SET @sql = '
--        SELECT ''Song'' AS Type, s.song_id AS ID, s.title AS Title, a.title AS AlbumTitle, ar.bio AS ArtistBio, s.genre AS Genre, s.country AS Country, s.Age_category AS AgeCategory
--        FROM Songs s
--        JOIN Albums a ON s.album_id = a.album_id
--        JOIN Artists ar ON s.artist_id_added = ar.artist_id
--        WHERE 1=1';
    
--    -- Append conditions for Songs
--    IF @name IS NOT NULL
--        SET @sql = @sql + ' AND s.title LIKE ''%' + @name + '%''';
--    IF @artist_name IS NOT NULL
--        SET @sql = @sql + ' AND ar.bio LIKE ''%' + @artist_name + '%''';
--    IF @genre IS NOT NULL
--        SET @sql = @sql + ' AND s.genre LIKE ''%' + @genre + '%''';
--    IF @country IS NOT NULL
--        SET @sql = @sql + ' AND s.country LIKE ''%' + @country + '%''';
--    IF @age_category IS NOT NULL
--        SET @sql = @sql + ' AND s.Age_category = ''' + @age_category + '''';
    
--    -- Add UNION ALL for Albums
--    SET @sql = @sql + '
--        UNION ALL
--        SELECT ''Album'' AS Type, a.album_id AS ID, a.title AS Title, a.title AS AlbumTitle, ar.bio AS ArtistBio, a.genre AS Genre, a.country AS Country, a.Age_category AS AgeCategory
--        FROM Albums a
--        JOIN Artists ar ON a.artist_id_added = ar.artist_id
--        WHERE 1=1';
    
--    -- Append conditions for Albums
--    IF @name IS NOT NULL
--        SET @sql = @sql + ' AND a.title LIKE ''%' + @name + '%''';
--    IF @artist_name IS NOT NULL
--        SET @sql = @sql + ' AND ar.bio LIKE ''%' + @artist_name + '%''';
--    IF @genre IS NOT NULL
--        SET @sql = @sql + ' AND a.genre LIKE ''%' + @genre + '%''';
--    IF @country IS NOT NULL
--        SET @sql = @sql + ' AND a.country LIKE ''%' + @country + '%''';
--    IF @age_category IS NOT NULL
--        SET @sql = @sql + ' AND a.Age_category = ''' + @age_category + '''';
    
--    -- Execute the dynamic SQL
--    EXEC sp_executesql @sql;
--END;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
---------------------------------------------------------------------------------------------------------------------------------------------
----DISPLAY SONG DETAILS:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE GetSongDetails
--    @song_id INT
--AS
--BEGIN
--    SELECT
--        s.song_id AS ID,
--        s.title AS Title,
--        a.title AS AlbumTitle,
--        ar.bio AS ArtistBio,
--        s.genre AS Genre,
--        s.country AS Country,
--        s.Age_category AS AgeCategory,
--        s.lyrics AS Lyrics  
--    FROM Songs s
--    JOIN Albums a ON s.album_id = a.album_id
--    JOIN Artists ar ON s.artist_id_added = ar.artist_id
--    WHERE s.song_id = @song_id;
--END;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----------------------------------------------------------------------------------------------------------------------------------------------
----DISPLAY SONG Lyrics :!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE GetSongLyrics 
--    @song_id INT
--AS
--BEGIN
--    SELECT
--        s.lyrics AS Lyrics  
--    FROM Songs s
--    WHERE s.song_id = @song_id;
--END;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----------------------------------------------------------------------------------------------------------------------------------------------
----ADD FUND TO WALLET:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE AddFundsToWallet
--    @UserID INT,
--    @Amount DECIMAL(10, 2)
--AS
--BEGIN
--    IF EXISTS (SELECT 1 FROM Digital_wallet WHERE user_id = @UserID)
--    BEGIN
--        UPDATE Digital_wallet
--        SET amount = amount + @Amount
--        WHERE user_id = @UserID;
--    END
--    ELSE
--    BEGIN
--        INSERT INTO Digital_wallet (user_id, amount)
--        VALUES (@UserID, @Amount);
--    END
--END;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-----------------------------------------------------------------------------------------------------------------------------------------------
----UPDATE WALLET:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--CREATE PROCEDURE UpdateWalletBalance
--    @UserID INT,
--    @Amount DECIMAL(10, 2)
--AS
--BEGIN
--    IF EXISTS (SELECT 1 FROM Digital_wallet WHERE user_id = @UserID)
--    BEGIN
--        DECLARE @CurrentBalance DECIMAL(10, 2);
--        SELECT @CurrentBalance = amount FROM Digital_wallet WHERE user_id = @UserID;
--        IF @Amount < 0 AND @CurrentBalance + @Amount < 0
--        BEGIN
--            RAISERROR('Insufficient funds in the digital wallet.', 16, 1);
--        END
--        ELSE
--        BEGIN
--            UPDATE Digital_wallet
--            SET amount = amount + @Amount
--            WHERE user_id = @UserID;
--        END
--    END
--    ELSE
--    BEGIN
--        IF @Amount >= 0
--        BEGIN
--            INSERT INTO Digital_wallet (user_id, amount)
--            VALUES (@UserID, @Amount);
--        END
--        ELSE
--        BEGIN
--            RAISERROR('User does not have a digital wallet to deduct funds from.', 16, 1);
--        END
--    END
--END;
----!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------------------------------------------------ZAHRA--------------------------------------------------------------------------------------
--CREATE PROCEDURE InsertUser
--    @username NVARCHAR(50),
--    @password NVARCHAR(50),
--    @birth_date DATE,
--    @location NVARCHAR(100),
--    @Email NVARCHAR(100)
--AS
--BEGIN
--    INSERT INTO Users (username, [password], email, birth_date, [location])
--    VALUES (@username, @password, @Email, @birth_date, @location);
--END;

-----------------------------------------------------
--CREATE PROCEDURE InsertPremium
--    @user_id INT, 
--    @end_time DATETIME,
--    @start_time DATETIME
--AS 
--BEGIN 
--    INSERT INTO Premium (user_id, Start_time, End_time)
--    VALUES (@user_id, @start_time, @end_time); 

--    PRINT 'Premium subscription added successfully.'; 
--END;

---------------------------------------------------------
--CREATE PROCEDURE CreatePlaylist
--    @user_id INT,
--    @playlist_name NVARCHAR(50),
--    @is_public BIT
--AS
--BEGIN
--    -- Check if the user has a valid subscription
--    IF EXISTS (
--        SELECT 1
--        FROM Premium
--        WHERE user_id = @user_id AND End_time > GETDATE()
--    )
--    BEGIN
--        -- Check if the playlist name is already used by the user
--        IF NOT EXISTS (
--            SELECT 1
--            FROM Play_list
--            WHERE user_id = @user_id
--              AND [name] = @playlist_name
--        )
--        BEGIN
--            -- Insert the playlist into Play_list table
--            INSERT INTO Play_list (user_id, [name], ispublic)
--            VALUES (@user_id, @playlist_name, @is_public);
--            PRINT 'Playlist created successfully.';
--        END
--        ELSE
--        BEGIN
--            PRINT 'Playlist with this name already exists.';
--        END;
--    END
--    ELSE
--    BEGIN
--        PRINT 'User does not have a valid subscription. Playlist creation is not allowed.';
--    END;
--END;
------------------------------------------------
--CREATE PROCEDURE AddSongToPlaylist
--    @user_id INT,
--    @playlist_name NVARCHAR(50),
--    @song_id INT
--AS
--BEGIN
--    -- Check if the playlist exists for the user
--    IF EXISTS (
--        SELECT 1
--        FROM Play_list
--        WHERE user_id = @user_id AND [name] = @playlist_name
--    )
--    BEGIN
--        -- Check if the song already exists in the playlist
--        IF NOT EXISTS (
--            SELECT 1
--            FROM Playlist_has_song
--            WHERE user_id = @user_id AND [name] = @playlist_name AND song_id = @song_id
--        )
--        BEGIN
--            -- Insert the song into the playlist
--            INSERT INTO Playlist_has_song (user_id, [name], song_id)
--            VALUES (@user_id, @playlist_name, @song_id);
--            PRINT 'Song added to playlist successfully.';
--        END
--        ELSE
--        BEGIN
--            PRINT 'This song is already in the playlist.';
--        END
--    END
--    ELSE
--    BEGIN
--        PRINT 'The specified playlist does not exist for the user.';
--    END
--END;

----------------------
--CREATE PROCEDURE ViewPlaylistSongsWithArtists
--    @playlist_name NVARCHAR(50),
--    @user_id INT
--AS
--BEGIN
--    SELECT 
--        PHS.[name] AS playlist_name,
--        S.song_id,
--        S.title AS song_title,
--        STRING_AGG(U.username, ', ') AS artist_names,
--        S.genre,
--        S.release_date
--    FROM 
--        Playlist_has_song PHS
--    INNER JOIN 
--        Songs S ON PHS.song_id = S.song_id
--    INNER JOIN 
--        artist_has_song AHS ON S.song_id = AHS.song_id
--    INNER JOIN 
--        Artists A ON AHS.artist_id = A.artist_id
--    INNER JOIN 
--        Users U ON A.artist_id = U.user_id -- Assuming artist_id corresponds to user_id in Users
--    WHERE 
--        PHS.[name] = @playlist_name
--    GROUP BY 
--        PHS.[name], S.song_id, S.title, S.genre, S.release_date
--    ORDER BY 
--        S.song_id;
--END;
-------------------------------------------------------
--CREATE PROCEDURE AddCommentToPlaylist
--    @user_id INT,
--    @playlist_name NVARCHAR(50),
--    @text VARCHAR(100)
--AS
--BEGIN
--    IF EXISTS (
--        SELECT 1
--        FROM Premium 
--        WHERE user_id = @user_id AND End_time > GETDATE()
--    )
--    BEGIN
--        INSERT INTO Comment_Play_list (user_id, [name], [text])
--        VALUES (@user_id, @playlist_name, @text);
--        PRINT 'Comment added successfully to playlist.';
--    END
--    ELSE
--    BEGIN
--        PRINT 'User does not have a valid subscription. Commenting is not allowed.';
--    END
--END
-------------------------------------------------------------------
--CREATE PROCEDURE AddCommentToSong
--    @user_id INT,
--    @song_id INT,
--    @text VARCHAR(100)
--AS
--BEGIN
--    IF EXISTS (
--        SELECT 1
--        FROM Premium
--        WHERE user_id = @user_id AND End_time > GETDATE()
--    )
--    BEGIN
--        INSERT INTO Comment_song (song_id, [text], user_id)
--        VALUES (@song_id, @text, @user_id);
        
--        PRINT 'Comment added successfully to song.';
--    END
--    ELSE
--    BEGIN
--        PRINT 'User does not have a valid subscription. Commenting is not allowed.';
--    END
--END
------------------------------------------------------------------
--CREATE PROCEDURE AddCommentToAlbum
--    @user_id INT,
--    @album_id INT,
--    @text VARCHAR(100)
--AS
--BEGIN
--    IF EXISTS (
--        SELECT 1
--        FROM Premium
--        WHERE user_id = @user_id AND End_time > GETDATE()
--    )
--    BEGIN
--        INSERT INTO Comment_Album (user_id, album_id, [text])
--        VALUES (@user_id, @album_id, @text);
        
--        PRINT 'Comment added successfully to album.';
--    END
--    ELSE
--    BEGIN

--        PRINT 'User does not have a valid subscription. Commenting is not allowed.';
--    END
--END
-------------------------------------------------------------------
--CREATE PROCEDURE LikeSong
--    @user_id INT,
--    @song_id INT
--AS
--BEGIN
--    IF EXISTS (
--        SELECT 1
--        FROM Premium
--        WHERE user_id = @user_id AND End_time > GETDATE()
--    )
--    BEGIN
--        IF NOT EXISTS (
--            SELECT 1     -- Using SELECT 1 in SQL is a shorthand way to check the existence of a record or condition without selecting any specific columns. It's efficient because it avoids selecting unnecessary data and simply returns a constant value (1) to indicate if the condition exists or not.
--            FROM Like_song
--            WHERE user_id = @user_id AND song_id = @song_id
--        )
--        BEGIN
--            INSERT INTO Like_song (user_id, song_id)
--            VALUES (@user_id, @song_id);
            
--            PRINT 'Song liked successfully.';
--        END
--        ELSE
--        BEGIN
--            PRINT 'You have already liked this song.';
--        END
--    END
--    ELSE
--    BEGIN
--        PRINT 'User does not have a valid subscription. Liking is not allowed.';
--    END
--END
-----------------------------------------------------------------
--CREATE PROCEDURE LikeAlbum
--    @user_id INT,
--    @album_id INT
--AS
--BEGIN
--    IF EXISTS (
--        SELECT 1
--        FROM Premium
--        WHERE user_id = @user_id AND End_time > GETDATE()
--    )
--    BEGIN
--        IF NOT EXISTS (
--            SELECT 1
--            FROM Like_album
--            WHERE user_id = @user_id AND album_id = @album_id
--        )
--        BEGIN
--            INSERT INTO Like_album (user_id, album_id)
--            VALUES (@user_id, @album_id);
            
--            PRINT 'Album liked successfully.';
--        END
--        ELSE
--        BEGIN
--            PRINT 'You have already liked this album.';
--        END
--    END
--    ELSE
--    BEGIN
--        PRINT 'User does not have a valid subscription. Liking is not allowed.';
--    END
--END
---------------------------------------------------------
--CREATE PROCEDURE LikePlaylist
--    @user_id INT,
--    @playlist_name NVARCHAR(50)
--AS
--BEGIN
--    IF EXISTS (
--        SELECT 1
--        FROM Premium
--        WHERE user_id = @user_id AND End_time > GETDATE()
--    )
--    BEGIN
--        IF NOT EXISTS (
--            SELECT 1
--            FROM Like_Play_list
--            WHERE user_id = @user_id AND [name] = @playlist_name
--        )
--        BEGIN
--            INSERT INTO Like_Play_list(user_id, [name])
--            VALUES (@user_id, @playlist_name);
            
--            PRINT 'Playlist liked successfully.';
--        END
--        ELSE
--        BEGIN
--            PRINT 'You have already liked this playlist.';
--        END
--    END
--    ELSE
--    BEGIN
--        PRINT 'User does not have a valid subscription. Liking is not allowed.';
--    END
--END
------------------------------------------------------------
--CREATE PROCEDURE InsertUserArtistLikes
--AS
--BEGIN
--    INSERT INTO User_Artist_Likes (user_id, artist_id, song_id, Likes_Count)
--    SELECT 
--        ls.user_id,
--        ar.artist_id,
--        ls.song_id,
--        COUNT(ls.song_id) OVER (PARTITION BY ls.user_id, ar.artist_id) AS Likes_Count
--    FROM 
--        Like_song ls
--    JOIN 
--        Songs s ON ls.song_id = s.song_id
--    JOIN 
--        artist_has_song ahs ON s.song_id = ahs.song_id
--    JOIN 
--        Artists ar ON ahs.artist_id = ar.artist_id;
--END;

--CREATE PROCEDURE InsertUserGenreLikes
--AS
--BEGIN
--    INSERT INTO User_Genre_Likes (user_id, song_id, Likes_Count)
--    SELECT 
--        ls.user_id,
--        ls.song_id,
--        COUNT(ls.song_id) OVER (PARTITION BY ls.user_id, s.genre) AS Likes_Count
--    FROM 
--        Like_song ls
--    JOIN 
--        Songs s ON ls.song_id = s.song_id;
--END;



----EXEC GetUserInterests @user_id = 1;
---------------------------------------------------------
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
---------------------------------------
--CREATE PROCEDURE CheckU
--    @username VARCHAR(50),
--    @password VARCHAR(50)
--AS
--BEGIN
--    SET NOCOUNT ON;
--    DECLARE @user_id INT;
--    SELECT @user_id = user_id
--    FROM Users
--    WHERE username = @username AND [password] = @password;
    
--    IF @user_id IS NOT NULL
--    BEGIN
--        SELECT @user_id AS User_Id,
--            CASE
--                WHEN EXISTS (SELECT 1 FROM Premium WHERE user_id = @user_id) THEN 'Premium User'
--                ELSE 'Regular User'
--            END AS User_Type;
--    END
--    ELSE
--    BEGIN
--        SELECT NULL AS User_Id, 'Invalid User' AS User_Type;
--    END
--END;
--GO 
----------------------------------------------
--CREATE PROCEDURE CheckUserByEmailAndUsername
--    @username VARCHAR(50),
--    @email VARCHAR(100)
--AS
--BEGIN
--    SET NOCOUNT ON;

--    DECLARE @user_id INT;
--    SELECT @user_id = user_id
--    FROM Users
--    WHERE username = @username AND email = @email;
--    SELECT 
--        CASE
--            WHEN @user_id IS NOT NULL THEN 'Valid'
--            ELSE 'Invalid'
--        END AS Result;
--END;
--GO
------------------------------------------------
--CREATE PROCEDURE UpdatePassword
--    @username VARCHAR(50),
--    @newPassword VARCHAR(50)
--AS
--BEGIN
--    SET NOCOUNT ON;

--    UPDATE Users
--    SET [password] = @newPassword
--    WHERE username = @username;

--    SELECT @@ROWCOUNT AS AffectedRows; -- Return the number of affected rows
--END;
--GO
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
CREATE PROCEDURE GetSongsInPlaylist
    @user_id INT,
    @playlist_name VARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;

    SELECT s.title AS Song_Title
    FROM Playlist_has_song ps
    INNER JOIN Songs s ON ps.song_id = s.song_id
    WHERE ps.user_id = @user_id
    AND ps.[name] = @playlist_name;
END;
GO
