--ADD Fllowers:
CREATE PROCEDURE AddFollower
    @UserId1 INT,
    @UserId2 INT
AS
BEGIN
    INSERT INTO follower (user_id1, user_id2)
    VALUES (@UserId1, @UserId2);
END;
GO
--EXECUTE:
EXEC AddFollower @UserId1 = 1, @UserId2 = 2;--from some one that cklick and the profile that clicked
------------------------------------------------------------------------------------------------------------------
--ADD Wallet to the User
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
--------------------------------------------------------------------------------------------------------------------
--ADD Ticket For evry Concert
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
--EXECUTE:
EXEC AddTicketsForConcert
    @artist_id = 1,-- from artist that added concert
    @date_concert = '2024-08-15 20:00:00',-- from information about concert
    @price1 = 2000.00,-- input 
    @quantity1 = 100,-- input 
    @price2 = 2500.00,-- input 
    @quantity2 = 50,-- input 
    @price3 = 3000.00,-- input 
    @quantity3 = 30;-- input 
----------------------------------------------------------------------------------------------------------------------
--SHOW ALL  Available CONCERT:
SELECT artist_id, location, [date]
FROM Concerts
WHERE [date] > GETDATE();
--SHOW ALL Available Tickets:
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
--BUY TICKET AND UPDATE WALLET:
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
-----------------------------------------------------------------------------------------------------------------
--SHOW ALL TICKET THAT BUY(0):
CREATE FUNCTION SHOWALLTICKET (@user_id INT)
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

----SHOW ALL TICKET THAT BUY(1):
CREATE FUNCTION SHOWALLTICKET (@user_id INT)
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
-----------------------------------------------------------------------------------------------------------------------------------------------------------
--ADD SONG TO FSVORITE:
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
-------------------------------------------------------------------------------------------------------------------------------------------------------------
--ADD PLAY LIST TO FSVORITE:
CREATE PROCEDURE ToggleFavoritePlaylist
@user_id INT,
@playlist_name VARCHAR(50)
AS
BEGIN
-- Check if the playlist is already a favorite
IF EXISTS (SELECT 1 FROM Favorite_Play_list WHERE user_id = @user_id AND [name] = @playlist_name)
BEGIN
	-- If the playlist is already a favorite, remove it
	DELETE FROM Favorite_Play_list 
	WHERE user_id = @user_id AND [name] = @playlist_name;
END
ELSE
BEGIN
	-- If the playlist is not a favorite, add it
	INSERT INTO Favorite_Play_list (user_id, [name])
	VALUES (@user_id, @playlist_name);
END
END
END;
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
--SEARCH ALBUM AND SONG:
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
--EXECUTE:

--EXEC SearchMusic @name = 'Imagine';

--EXEC SearchMusic @artist_name = 'John Doe';


--EXEC SearchMusic @genre = 'Rock';


--EXEC SearchMusic @country = 'USA';


--EXEC SearchMusic @age_category = 'PG';


--EXEC SearchMusic @name = 'Imagine', @artist_name = 'John Doe', @genre = 'Rock', @country = 'USA', @age_category = 'PG';

-------------------------------------------------------------------------------------------------------------------------------------------
--DISPLAY LYRICS
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
------------------------------------------------------------------------------------------------