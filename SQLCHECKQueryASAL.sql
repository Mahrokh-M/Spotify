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