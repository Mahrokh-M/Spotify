INSERT INTO Users (user_id, username, [password], email, birth_date, [location]) VALUES
(1, 'alice', 'password123', 'alice@example.com', '1990-01-15', 'New York'),
(2, 'bob', 'password456', 'bob@example.com', '1992-02-20', 'Los Angeles'),
(3, 'charlie', 'password789', 'charlie@example.com', '1988-03-25', 'Chicago');
--------------------------------------------------------------------------------------------
INSERT INTO Permium (user_id, Start_time, End_time) VALUES
(1, '2024-01-01', '2025-01-01'),
(2, '2024-06-01', '2025-06-01');
--------------------------------------------------------------------------------------------
INSERT INTO Play_list (user_id, [name], ispublic, address_of_picture) VALUES
(1, 'Rock Classics', 1, 'path/to/rock_classics.jpg'),
(2, 'Chill Vibes', 0, 'path/to/chill_vibes.jpg');
--------------------------------------------------------------------------------------------

INSERT INTO Artists (artist_id, bio) VALUES
(1, 'Rock singer and guitarist.'),
(2, 'Pop artist with multiple hits.');
----------------------------------------------------------------------------------------------
INSERT INTO Albums (album_id, title, artist_id_added, genre, release_date, Age_category, country, address_of_picture) VALUES
(1, 'Greatest Hits', 1, 'Rock', '2020-05-01', 'PG', 'USA', 'path/to/greatest_hits.jpg'),
(2, 'Best of Pop', 2, 'Pop', '2022-10-15', 'PG', 'USA', 'path/to/best_of_pop.jpg');
---------------------------------------------------------------------------------------------------
INSERT INTO Songs (song_id, artist_id_added, title, album_id, genre, release_date, lyrics, Age_category, country, address_of_picture, can_be_added) VALUES
(1, 1, 'Rock Anthem', 1, 'Rock', '2020-05-01', 'Lyrics of Rock Anthem', 'PG', 'USA', 'path/to/rock_anthem.jpg', 1),
(2, 2, 'Pop Hit', 2, 'Pop', '2022-10-15', 'Lyrics of Pop Hit', 'PG', 'USA', 'path/to/pop_hit.jpg', 1);
----------------------------------------------------------------------------------------------------
INSERT INTO Concerts (artist_id, [location], [date]) VALUES
(1, 'Madison Square Garden', '2024-07-15 20:00:00'),
(2, 'Hollywood Bowl', '2024-08-10 19:30:00');
----------------------------------------------------------------------------------------------------
INSERT INTO Tickets (ticket_id, user_id, artist_id, price, Expiration, is_sold, date_concert) VALUES
(1, 1, 1, 75.00, 1, 0, '2024-07-15 20:00:00'),
(2, 2, 2, 60.00, 1, 1, '2024-08-10 19:30:00');
-------------------------------------------------------------------------------------------------------
INSERT INTO Favorite_Play_list (user_id, [name]) VALUES
(1, 'Rock Classics'),
(2, 'Chill Vibes');
------------------------------------------------------------------------------------------------------
INSERT INTO Comment_Play_list (user_id, [name], [text]) VALUES
(1, 'Rock Classics', 'Great playlist for rock fans!'),
(2, 'Chill Vibes', 'Perfect for a relaxing evening.');
----------------------------------------------------------------------------------------------------------
INSERT INTO Like_Play_list (user_id, [name]) VALUES
(1, 'Rock Classics'),
(2, 'Chill Vibes');
-----------------------------------------------------------------------------------------------------------
INSERT INTO Friend (user_id1, user_id2, accept) VALUES
(1, 2, 1),
(2, 3, 0);
---------------------------------------------------------------------------------------------------------
INSERT INTO Message_Premium (user_id1, user_id2, [text]) VALUES
(1, 2, 'Hey, how are you?'),
(2, 1, 'I\'m good, thanks!');
------------------------------------------------------------------------------------------------------
INSERT INTO follower (user_id1, user_id2) VALUES
(1, 2),
(2, 3);
--------------------------------------------------------------------------------------------------
INSERT INTO Comment_Album (user_id, album_id, [text]) VALUES
(1, 1, 'Love this album!'),
(2, 2, 'Great collection of pop hits.');
----------------------------------------------------------------------------------------------------
INSERT INTO artist_has_song (song_id, artist_id) VALUES
(1, 1),
(2, 2);
---------------------------------------------------------------------------------------------------
INSERT INTO Playlist_has_song ([name], song_id, user_id) VALUES
('Rock Classics', 1, 1),
('Chill Vibes', 2, 2);
---------------------------------------------------------------------------------------------------------