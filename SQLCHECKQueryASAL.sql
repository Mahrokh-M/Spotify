SELECT*
FROM Digital_wallet;
SELECT *
FROM Users;
SELECT *
FROM Permium;
EXEC AddFollower @UserId1 = 5, @UserId2 = 2;--from some one that cklick and the profile that clicked
EXEC GetFollowers @user_id=2;
EXEC GetFollowing @user_id=5;
EXEC AddTicketsForConcert
    @artist_id = 3,
    @date_concert = '2027-07-01 20:00:00.000',
    @price1 = 50.00,
    @quantity1 = 10,
    @price2 = 75.00,
    @quantity2 = 5,
    @price3 = 100.00,
    @quantity3 = 2;
EXEC GetAvailableTickets @artist_id=3,@date_concert='2027-07-01 20:00:00.000';
EXEC BuyTicket @user_id=10,@ticket_id=10;
EXEC ToggleFavoriteSong @user_id=10,
						@song_id=7;
EXEC GetFavoriteSongs @user_id=10;
SELECT * FROM SHOWALLTICKET1(10);
EXEC ToggleFavoritePlaylist  @user_id_added=1,
                             @user_id_owner=2,
							  @playlist_name='Playlist3';
EXEC GetFavoritePlaylistsByUserID @UserID = 1;
EXEC AddFundsToWallet @UserID = 1, @Amount = -50.00;
UPDATE Digital_wallet		
SET amount=100
WHERE user_id=10;
--EXECUTE:
EXEC SearchMusicAndAlbum @name = 'Imagine';
EXEC SearchMusicAndAlbum @artist_name = 'John Doe';
EXEC SearchMusicAndAlbum @genre = 'Rock';
EXEC SearchMusicAndAlbum @country = 'USA';
EXEC SearchMusicAndAlbum @age_category = 'PG';
EXEC SearchMusicAndAlbum @name = 'Imagine', @artist_name = 'John Doe', @genre = 'Rock', @country = 'USA', @age_category = 'PG';
EXEC GetSongDetails @song_id=5;
EXEC GetSongLyrics  @song_id=5;
EXEC UpdateWalletBalance @UserID = 1, @Amount = 50.00;
EXEC UpdateWalletBalance @UserID = 1, @Amount = -20.00;
EXEC UpdateWalletBalance @UserID = 5, @Amount = -20.00;
SELECT*
FROM follower;
SELECT*
FROM Artists;
SELECT*
FROM Concerts;
SELECT*
FROM Tickets;
SELECT *
FROM Songs;
SELECT* 
FROM Albums;
SELECT *
FROM Play_list;
SELECT *
FROM Favorite_Play_list;




-- Create Users
INSERT INTO Users (username, [password], email, birth_date, [location])
VALUES 
('artist1', 'password1', 'artist1@example.com', '1980-01-01', 'Location1'),
('artist2', 'password2', 'artist2@example.com', '1982-02-02', 'Location2');

-- Create Artists
INSERT INTO Artists (artist_id, bio)
VALUES 
((SELECT user_id FROM Users WHERE username = 'artist1'), 'Bio of artist 1'),
((SELECT user_id FROM Users WHERE username = 'artist2'), 'Bio of artist 2');

-- Create Albums
INSERT INTO Albums (title)
VALUES ('Album1');

-- Create Songs
INSERT INTO Songs (title, album_id, genre, country, Age_category, lyrics)
VALUES ('fhdjkashfjkhasdl', (SELECT album_id FROM Albums WHERE title = 'Album1'), 'Genre1', 'Country1', 'A', 'Lyrics of song 14444444444444444444455555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555 455555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555');

-- Create artist_has_song
INSERT INTO artist_has_song (song_id, artist_id)
VALUES 
((SELECT song_id FROM Songs WHERE title = 'Song1'), (SELECT artist_id FROM Artists WHERE artist_id = (SELECT user_id FROM Users WHERE username = 'artist1'))),
((SELECT song_id FROM Songs WHERE title = 'Song1'), (SELECT artist_id FROM Artists WHERE artist_id = (SELECT user_id FROM Users WHERE username = 'artist2')));
