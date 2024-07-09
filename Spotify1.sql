CREATE TABLE Users (
    user_id INT PRIMARY KEY IDENTITY,
    username NVARCHAR(50) NOT NULL,
    password NVARCHAR(50) NOT NULL,
    email NVARCHAR(100) NOT NULL,
    birth_date DATE,
    location NVARCHAR(100)
);
----------------------------------------------------
CREATE TABLE Permium(
    user_id INT PRIMARY KEY IDENTITY,  
	Start_time DATE,
	End_time DATE
	FOREIGN KEY (user_id) REFERENCES Users(user_id)
);
-----------------------------------------------------
CREATE TABLE Play_list(
    user_id INT PRIMARY KEY IDENTITY,
	name NVARCHAR(50) NOT NULL PRIMARY KEY,
    ispublic BIT DEFAULT 0,
    FOREIGN KEY (user_id) REFERENCES Users(user_id)
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
    Artists_id INT PRIMARY KEY IDENTITY,
    bio NVARCHAR(MAX),
    FOREIGN KEY (Artists_id) REFERENCES Users(user_id)
);
-----------------------------------------------------
CREATE TABLE Songs (
    song_id INT PRIMARY KEY IDENTITY,
	artists_id_added INT,
	title NVARCHAR(100)  NOT NULL,
	album_id INT,
    genre NVARCHAR(50),
    release_date DATE,
    lyrics NVARCHAR(MAX),
	Age_category CHAR(2),
	country NVARCHAR(50),
    can_be_added BIT DEFAULT 0,
	FOREIGN KEY (album_id) REFERENCES Albums(album_id)
	FOREIGN KEY (artists_id_added) REFERENCES Artists(Artists_id)
);
----------------------------------------------------
CREATE TABLE Concerts (
    artist_id INT  PRIMARY KEY,
    location NVARCHAR(100),
    date DATETIME PRIMARY KEY,
    FOREIGN KEY (artist_id) REFERENCES Artists(artist_id)
);
----------------------------------------------------
CREATE TABLE Tickets (
    ticket_id INT PRIMARY KEY IDENTITY,
    user_id INT,
	Artists_id INT,
	price DECIMAL(10, 2),
    purchase_date DATETIME DEFAULT GETDATE(),
	date_concert DATETIME DEFAULT GETDATE(),
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
	FOREIGN KEY (Artists_id,date_concert) REFERENCES Concerts(Artists_id,date)
);
----------------------------------------------------

----------------------------------------------------
CREATE TABLE Albums (
    album_id INT PRIMARY KEY IDENTITY,
	title NVARCHAR(100) NOT NULL,
	artists_id_added INT,
    genre NVARCHAR(50),
    release_date DATE,
	Age_category CHAR(2),
	country NVARCHAR(50),
	FOREIGN KEY (artists_id_added) REFERENCES Artists(Artists_id)
);
---------------------------------------------------
CREATE TABLE Favorite_Play_list(
    user_id INT PRIMARY KEY IDENTITY,
	name NVARCHAR(50) NOT NULL PRIMARY KEY,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (name) REFERENCES Play_list(name)
);
---------------------------------------------------
CREATE TABLE Comment_Play_list(
    user_id INT PRIMARY KEY IDENTITY,
	name NVARCHAR(50) NOT NULL PRIMARY KEY,
	text NVARCHAR(100),
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (name) REFERENCES Play_list(name)
);
---------------------------------------------------
CREATE TABLE Like_Play_list(
    user_id INT PRIMARY KEY IDENTITY,
	name NVARCHAR(50) NOT NULL PRIMARY KEY,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (name) REFERENCES Play_list(name)
);
----------------------------------------------------
CREATE TABLE Friend(
    user_id1 INT PRIMARY KEY IDENTITY,
	user_id2 INT PRIMARY KEY IDENTITY,
	accept BIT DEFAULT 0,
    FOREIGN KEY (user_id1) REFERENCES Permium(user_id),
	FOREIGN KEY (user_id2) REFERENCES Permium(user_id),
);
----------------------------------------------------
CREATE TABLE Message_Permium(
    user_id1 INT PRIMARY KEY IDENTITY,
	user_id2 INT PRIMARY KEY IDENTITY,
	text NVARCHAR(100),
	--accept BIT DEFAULT 0,
    FOREIGN KEY (user_id1) REFERENCES Permium(user_id),
	FOREIGN KEY (user_id2) REFERENCES Permium(user_id),
);
-------------------------------------------------------
CREATE TABLE follower(
    user_id INT PRIMARY KEY IDENTITY,
	name NVARCHAR(50) NOT NULL PRIMARY KEY,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (name) REFERENCES Play_list(name)
);
-------------------------------------------------------
CREATE TABLE Favorite_Song(
    user_id INT PRIMARY KEY IDENTITY,
	artist_id INT PRIMARY KEY IDENTITY,
	title NVARCHAR(100) PRIMARY KEY NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (title) REFERENCES Songs(title)
	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id)
);
------------------------------------------------------
CREATE TABLE Comment_Album(
    user_id INT IDENTITY,
	album_id INT IDENTITY
	text NVARCHAR(100),
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (album_id) REFERENCES Album(album_id)
);
------------------------------------------------------
CREATE TABLE artist_has_song(
    song_id INT PRIMARY KEY IDENTITY,
	artist_id INT PRIMARY KEY IDENTITY,
    FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id)
);
-------------------------------------------------------
CREATE TABLE artist_has_album(
    album_id INT PRIMARY KEY IDENTITY,
	artist_id INT PRIMARY KEY IDENTITY,
    FOREIGN KEY (album_id) REFERENCES Albums(album_id),
	FOREIGN KEY (artist_id) REFERENCES Artists(artist_id)
);
-------------------------------------------------------
CREATE TABLE Playlist_has_song(
    name INT PRIMARY KEY IDENTITY,
	song_id INT PRIMARY KEY IDENTITY,
	user_id INT PRIMARY KEY IDENTITY,
    FOREIGN KEY (name) REFERENCES Play_list(name),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	FOREIGN KEY (user_id) REFERENCES Play_list(user_id)
);
-------------------------------------------------------
CREATE TABLE Favorite_Song(
    user_id INT PRIMARY KEY IDENTITY,
	song_id NVARCHAR(50) NOT NULL PRIMARY KEY,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id)
);
-------------------------------------------------------
CREATE TABLE Comment_song(
    song_id INT PRIMARY KEY IDENTITY,
	text NVARCHAR(100),
	user_id INT PRIMARY KEY IDENTITY,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id)
);
-------------------------------------------------------
CREATE TABLE Like_song(
    song_id INT PRIMARY KEY IDENTITY,
	user_id INT PRIMARY KEY IDENTITY,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id)
);
-------------------------------------------------------
CREATE TABLE Like_album(
    user_id INT IDENTITY,
	album_id INT IDENTITY
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (album_id) REFERENCES Album(album_id)
);
-------------------------------------------------------
CREATE TABLE Return_money(
    Digital_wallet_id INT PRIMARY KEY IDENTITY,
	artist_id INT  PRIMARY KEY,
    date DATETIME PRIMARY KEY,
	amount DECIMAL(10, 2), --**
    FOREIGN KEY (artist_id,date) REFERENCES Artists(artist_id,date),
	FOREIGN KEY (Digital_wallet_id) REFERENCES Digital_wallet(Digital_wallet_id)
);
-------------------------------------------------------