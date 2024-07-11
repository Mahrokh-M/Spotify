--ADD Fllowers:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE AddFollower
    @UserId1 INT,
    @UserId2 INT
AS
BEGIN
    INSERT INTO follower (user_id1, user_id2)
    VALUES (@UserId1, @UserId2);
END;
GO
--DISPLAY ALL FOLLOWER FOR ONE PERSON:
CREATE PROCEDURE GetFollowers
    @user_id INT
AS
BEGIN
    SELECT
        u.user_id,
        u.username
    FROM
        follower f
    JOIN
        Users u ON f.user_id1 = u.user_id
    WHERE
        f.user_id2 = @user_id;
END;
--DISPLAY ALL FOLLOWING FOR ONE PERSON:
CREATE PROCEDURE GetFollowing
    @user_id INT
AS
BEGIN
    SELECT
        u.user_id,
        u.username
    FROM
        follower f
    JOIN
        Users u ON f.user_id2 = u.user_id 
    WHERE
        f.user_id1 = @user_id;  
END;

--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------------------------------------------------------------------------------------------------------------------
--ADD Wallet to the User !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE TRIGGER CreateWalletAfterUserInsert
ON Users
AFTER INSERT
AS
BEGIN
    INSERT INTO Digital_wallet (user_id) 
    SELECT user_id 
    FROM inserted;
END;
GO
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--------------------------------------------------------------------------------------------------------------------
--ADD Ticket For evry Concert!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE AddTicketsForConcert
    @artist_id INT,
    @date_concert DATETIME,
    @price1 DECIMAL(10, 2),
    @quantity1 INT,
    @price2 DECIMAL(10, 2),
    @quantity2 INT,
    @price3 DECIMAL(10, 2),
    @quantity3 INT
AS
BEGIN
    DECLARE @i INT = 1;
    WHILE @i <= @quantity1
    BEGIN
        INSERT INTO Tickets (user_id, artist_id, price, date_concert)
        VALUES (NULL, @artist_id, @price1, @date_concert);
        SET @i = @i + 1;
    END

    SET @i = 1;
    WHILE @i <= @quantity2
    BEGIN
        INSERT INTO Tickets (user_id, artist_id, price, date_concert)
        VALUES (NULL, @artist_id, @price2, @date_concert);
        SET @i = @i + 1;
    END

    SET @i = 1;
    WHILE @i <= @quantity3
    BEGIN
        INSERT INTO Tickets (user_id, artist_id, price, date_concert)
        VALUES (NULL, @artist_id, @price3, @date_concert);
        SET @i = @i + 1;
    END
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----------------------------------------------------------------------------------------------------------------------
--SHOW ALL  Available CONCERT:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
SELECT artist_id, location, [date]
FROM Concerts
WHERE [date] > GETDATE();
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--SHOW ALL Available Tickets:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE GetAvailableTickets
    @artist_id INT,
    @date_concert DATETIME
AS
BEGIN
    SELECT ticket_id, price
    FROM Tickets
    WHERE artist_id = @artist_id
      AND date_concert = @date_concert
      AND is_sold = 0
      AND Expiration = 1;
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--BUY TICKET AND UPDATE WALLET:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE BuyTicket
    @user_id INT,       
    @ticket_id INT      
AS
BEGIN
    BEGIN TRANSACTION;

    DECLARE @price DECIMAL(10, 2);  
    DECLARE @balance DECIMAL(10, 2); 

    SELECT @price = price
    FROM Tickets
    WHERE ticket_id = @ticket_id
      AND is_sold = 0
      AND Expiration = 1;
  
    SELECT @balance = amount
    FROM Digital_wallet
    WHERE user_id = @user_id;

    IF @balance < @price
    BEGIN
        RAISERROR('Insufficient funds in wallet.', 16, 1);
        ROLLBACK TRANSACTION;
        RETURN;
    END;
    UPDATE Tickets
    SET user_id = @user_id, is_sold = 1
    WHERE ticket_id = @ticket_id;

    UPDATE Digital_wallet
    SET amount = amount - @price
    WHERE user_id = @user_id;

    COMMIT TRANSACTION;
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-----------------------------------------------------------------------------------------------------------------
--SHOW ALL TICKET THAT BUY(0):!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE FUNCTION SHOWALLTICKET0 (@user_id INT)
RETURNS TABLE
AS
RETURN
(
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
        t.user_id = @user_id AND t.is_sold = 1 AND t.Expiration = 0
);

--SHOW ALL TICKET THAT BUY(1):
CREATE FUNCTION SHOWALLTICKET1 (@user_id INT)
RETURNS TABLE
AS
RETURN
(
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
        t.user_id = @user_id AND t.is_sold = 1 AND t.Expiration = 1
);
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-----------------------------------------------------------------------------------------------------------------------------------------------------------
--ADD SONG TO FSVORITE:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE ToggleFavoriteSong
@user_id INT,
@song_id INT
AS
BEGIN
-- Check if the song is already a favorite
IF EXISTS (SELECT 1 FROM Favorite_Song WHERE user_id = @user_id AND song_id = @song_id)
BEGIN
	-- If the song is already a favorite, remove it
	DELETE FROM Favorite_Song 
	WHERE user_id = @user_id AND song_id = @song_id;
END
ELSE
BEGIN
	-- If the song is not a favorite, add it
	INSERT INTO Favorite_Song (user_id, song_id)
	VALUES (@user_id, @song_id);
END
END;
--DISPLAY FAVORITE SONGS:
CREATE PROCEDURE GetFavoriteSongs
    @user_id INT
AS
BEGIN
    SELECT 
        s.song_id,
        s.title AS Song_Title
    FROM 
        Favorite_Song fs
    JOIN 
        Songs s ON fs.song_id = s.song_id
    WHERE 
        fs.user_id = @user_id;
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------------------------------------------------------------------------------------------------------------------
--ADD PLAY LIST TO FSVORITE:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE ToggleFavoritePlaylist
    @user_id_added INT,
    @user_id_owner INT,
    @playlist_name VARCHAR(50)
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Favorite_Play_list WHERE user_id_owner = @user_id_owner AND user_id = @user_id_added AND [name] = @playlist_name)
    BEGIN
        DELETE FROM Favorite_Play_list 
        WHERE user_id_owner = @user_id_owner AND user_id = @user_id_added AND [name] = @playlist_name;
    END
    ELSE
    BEGIN
        INSERT INTO Favorite_Play_list (user_id_owner, user_id, [name])
        VALUES (@user_id_owner, @user_id_added, @playlist_name);
    END
END;
--DISPLAY  PLAY LIST  FAVORITE:
CREATE PROCEDURE GetFavoritePlaylistsByUserID
    @UserID INT
AS
BEGIN
    SELECT
        u.username AS OwnerUsername,  
        fp.[name] AS PlaylistName
    FROM
        Favorite_Play_list fp
    JOIN
        Users u ON fp.user_id_owner = u.user_id
    WHERE
        fp.user_id = @UserID;
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
--SEARCH ALBUM AND SONG:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
        SELECT ''Song'' AS Type, s.song_id AS ID, s.title AS Title, a.title AS AlbumTitle, ar.bio AS ArtistBio, s.genre AS Genre, s.country AS Country, s.Age_category AS AgeCategory
        FROM Songs s
        JOIN Albums a ON s.album_id = a.album_id
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
        SELECT ''Album'' AS Type, a.album_id AS ID, a.title AS Title, a.title AS AlbumTitle, ar.bio AS ArtistBio, a.genre AS Genre, a.country AS Country, a.Age_category AS AgeCategory
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
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------------------------------------------------------------------------------------------------
--DISPLAY SONG DETAILS:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE GetSongDetails
    @song_id INT
AS
BEGIN
    SELECT
        s.song_id AS ID,
        s.title AS Title,
        a.title AS AlbumTitle,
        ar.bio AS ArtistBio,
        s.genre AS Genre,
        s.country AS Country,
        s.Age_category AS AgeCategory,
        s.lyrics AS Lyrics  
    FROM Songs s
    JOIN Albums a ON s.album_id = a.album_id
    JOIN Artists ar ON s.artist_id_added = ar.artist_id
    WHERE s.song_id = @song_id;
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--------------------------------------------------------------------------------------------------------------------------------------------
--DISPLAY SONG Lyrics :!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE GetSongLyrics 
    @song_id INT
AS
BEGIN
    SELECT
        s.lyrics AS Lyrics  
    FROM Songs s
    WHERE s.song_id = @song_id;
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--------------------------------------------------------------------------------------------------------------------------------------------
--ADD FUND TO WALLET:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE AddFundsToWallet
    @UserID INT,
    @Amount DECIMAL(10, 2)
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Digital_wallet WHERE user_id = @UserID)
    BEGIN
        UPDATE Digital_wallet
        SET amount = amount + @Amount
        WHERE user_id = @UserID;
    END
    ELSE
    BEGIN
        INSERT INTO Digital_wallet (user_id, amount)
        VALUES (@UserID, @Amount);
    END
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
---------------------------------------------------------------------------------------------------------------------------------------------
--UPDATE WALLET:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CREATE PROCEDURE UpdateWalletBalance
    @UserID INT,
    @Amount DECIMAL(10, 2)
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Digital_wallet WHERE user_id = @UserID)
    BEGIN
        DECLARE @CurrentBalance DECIMAL(10, 2);
        SELECT @CurrentBalance = amount FROM Digital_wallet WHERE user_id = @UserID;
        IF @Amount < 0 AND @CurrentBalance + @Amount < 0
        BEGIN
            RAISERROR('Insufficient funds in the digital wallet.', 16, 1);
        END
        ELSE
        BEGIN
            UPDATE Digital_wallet
            SET amount = amount + @Amount
            WHERE user_id = @UserID;
        END
    END
    ELSE
    BEGIN
        IF @Amount >= 0
        BEGIN
            INSERT INTO Digital_wallet (user_id, amount)
            VALUES (@UserID, @Amount);
        END
        ELSE
        BEGIN
            RAISERROR('User does not have a digital wallet to deduct funds from.', 16, 1);
        END
    END
END;
--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!