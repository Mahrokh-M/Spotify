-- INSERT INTO Users
INSERT INTO Users (username, [password], email, birth_date, [location])
VALUES 
('user1', 'password1', 'user1@example.com', '1990-01-01', 'City1'),
('user2', 'password2', 'user2@example.com', '1991-02-02', 'City2'),
('user3', 'password3', 'user3@example.com', '1992-03-03', 'City3');
-- INSERT INTO Permium
INSERT INTO Permium (Start_time, End_time)
VALUES 
('2024-01-01', '2024-12-31'),
('2024-02-01', '2024-12-31'),
('2024-03-01', '2024-12-31');

-- INSERT INTO Play_list
INSERT INTO Play_list (user_id, [name], ispublic, address_of_picture)
VALUES 
(1, 'Playlist1', 1, 'path/to/picture1.jpg'),
(1, 'Playlist2', 0, 'path/to/picture2.jpg'),
(2, 'Playlist3', 1, 'path/to/picture3.jpg');

-- INSERT INTO Digital_wallet
INSERT INTO Digital_wallet (user_id, amount)
VALUES 
(1, 100.00),
(2, 150.00),
(3, 200.00);

-- INSERT INTO Artists
INSERT INTO Artists (bio)
VALUES 
('Artist Bio 1'),
('Artist Bio 2'),
('Artist Bio 3');

-- INSERT INTO Albums
INSERT INTO Albums (title, artist_id_added, genre, release_date, Age_category, country, address_of_picture)
VALUES 
('Album1', 1, 'Rock', '2024-01-01', 'PG', 'USA', 'path/to/album1.jpg'),
('Album2', 2, 'Pop', '2024-02-01', 'PG', 'UK', 'path/to/album2.jpg'),
('Album3', 3, 'Jazz', '2024-03-01', 'R', 'Canada', 'path/to/album3.jpg');

-- INSERT INTO Songs
INSERT INTO Songs (artist_id_added, title, album_id, genre, release_date, lyrics, Age_category, country, address_of_picture, can_be_added)
VALUES 
(1, 'Song1', 1, 'Rock', '2024-01-01', 'Lyrics of Song1', 'PG', 'USA', 'path/to/song1.jpg', 1),
(2, 'Song2', 2, 'Pop', '2024-02-01', 'Lyrics of Song2', 'PG', 'UK', 'path/to/song2.jpg', 1),
(3, 'Song3', 3, 'Jazz', '2024-03-01', 'Lyrics of Song3', 'R', 'Canada', 'path/to/song3.jpg', 1);

-- INSERT INTO Concerts
INSERT INTO Concerts (artist_id, [location], [date], address_of_picture)
VALUES 
(1, 'Venue1', '2025-05-01 20:00:00', 'path/to/concert1.jpg'),
(2, 'Venue2', '2029-06-01 20:00:00', 'path/to/concert2.jpg'),
(3, 'Venue3', '2027-07-01 20:00:00', 'path/to/concert3.jpg');

-- INSERT INTO Tickets
INSERT INTO Tickets (user_id, artist_id, price, Expiration, is_sold, date_concert)
VALUES 
(null, 1, 50.00,0, 0, '2024-05-01 20:00:00'),
(null, 2, 60.00, 0, 0, '2024-06-01 20:00:00'),
(null, 3, 70.00, 0, 0, '2024-07-01 20:00:00');

-- INSERT INTO Favorite_Play_list
INSERT INTO Favorite_Play_list (user_id, [name])
VALUES 
(1, 'Playlist1'),
(2, 'Playlist3');

-- INSERT INTO Comment_Play_list
INSERT INTO Comment_Play_list (user_id, [name], [text])
VALUES 
(1, 'Playlist1', 'Great playlist!'),
(2, 'Playlist3', 'I love this playlist!');

-- INSERT INTO Like_Play_list
INSERT INTO Like_Play_list (user_id, [name])
VALUES 
(1, 'Playlist2'),
(2, 'Playlist3');

-- INSERT INTO Friend
INSERT INTO Friend (user_id1, user_id2, accept)
VALUES 
(1, 2, 1),
(2, 3, 0);

-- INSERT INTO Message_Premium
INSERT INTO Message_Premium (user_id1, user_id2, [text])
VALUES 
(1, 2, 'Hello!'),
(2, 1, 'Hi there!');

-- INSERT INTO follower
INSERT INTO follower (user_id1, user_id2)
VALUES 
(1, 2),
(2, 3);

-- INSERT INTO Comment_Album
INSERT INTO Comment_Album (user_id, album_id, [text])
VALUES 
(1, 1, 'Amazing album!'),
(2, 2, 'Nice album!');

-- INSERT INTO artist_has_song
INSERT INTO artist_has_song (song_id, artist_id)
VALUES 
(1, 1),
(2, 2),
(3, 3);

-- INSERT INTO artist_has_album
INSERT INTO artist_has_album (album_id, artist_id)
VALUES 
(1, 1),
(2, 2),
(3, 3);

-- INSERT INTO Playlist_has_song
INSERT INTO Playlist_has_song ([name], song_id, user_id)
VALUES 
('Playlist1', 1, 1),
('Playlist3', 2, 2);

-- INSERT INTO Favorite_Song
INSERT INTO Favorite_Song (user_id, song_id)
VALUES 
(1, 1),
(2, 2);

-- INSERT INTO Comment_song
INSERT INTO Comment_song (song_id, [text], user_id)
VALUES 
(1, 'Great song!', 1),
(2, 'Love this track!', 2);

-- INSERT INTO Like_song
INSERT INTO Like_song (song_id, user_id)
VALUES 
(1, 1),
(2, 2);

-- INSERT INTO Like_album
INSERT INTO Like_album (user_id, album_id)
VALUES 
(1, 1),
(2, 2);

-- INSERT INTO Return_money
INSERT INTO Return_money (Digital_wallet_id, artist_id, [date], amount)
VALUES 
(1, 1, '2024-05-01 20:00:00', 50.00),
(2, 2, '2024-06-01 20:00:00', 60.00);

-- INSERT INTO Play_song
INSERT INTO Play_song (song_id, user_id)
VALUES 
(1, 1),
(2, 2);
