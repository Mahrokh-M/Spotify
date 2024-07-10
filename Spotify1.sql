CREATE TABLE Users (
    user_id INT PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    [password] VARCHAR(50) NOT NULL,
    email VARCHAR(100) NOT NULL,
    birth_date DATE,
    [location] VARCHAR(100)
);
-----------------------------------------------------
CREATE TABLE Permium(
    user_id INT PRIMARY KEY,  
	Start_time DATE,
	End_time DATE
	FOREIGN KEY (user_id) REFERENCES Users(user_id)
);
-----------------------------------------------------
CREATE TABLE Play_list(
    user_id INT ,
	[name] VARCHAR(50) NOT NULL ,
    ispublic BIT DEFAULT 0,
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
	PRIMARY KEY(user_id,[name])
);
-----------------------------------------------------
CREATE TABLE Digital_wallet (
    Digital_wallet_id INT PRIMARY KEY,
    user_id INT,
    amount DECIMAL(10, 2),
    FOREIGN KEY (user_id) REFERENCES Users(user_id)
);
-----------------------------------------------------
CREATE TABLE Artists (
    artist_id INT PRIMARY KEY,
    bio VARCHAR(MAX),
    FOREIGN KEY (artist_id) REFERENCES Users(user_id)
);
------------------------------------------------------------
CREATE TABLE Albums (
    album_id INT PRIMARY KEY,
	title VARCHAR(100) NOT NULL,
	artist_id_added INT,
    genre VARCHAR(50),
    release_date DATE,
	Age_category CHAR(2),
	country VARCHAR(50),
	FOREIGN KEY (artist_id_added) REFERENCES Artists(artist_id)
);
-----------------------------------------------------
CREATE TABLE Songs (
    song_id INT PRIMARY KEY,
	artist_id_added INT,
	title VARCHAR(100)  NOT NULL,
	album_id INT,
    genre VARCHAR(50),
    release_date DATE,
    lyrics VARCHAR(MAX),
	Age_category CHAR(2),
	country VARCHAR(50),
    can_be_added BIT DEFAULT 0,
	FOREIGN KEY (album_id) REFERENCES Albums(album_id),
	FOREIGN KEY (artist_id_added) REFERENCES Artists(artist_id)
);
----------------------------------------------------
CREATE TABLE Concerts (
    artist_id INT ,
    [location] VARCHAR(100),
    [date] DATETIME ,
    FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
	PRIMARY KEY (artist_id,[date])
);
----------------------------------------------------
CREATE TABLE Tickets (
    ticket_id INT PRIMARY KEY IDENTITY,
    user_id INT,
	artist_id INT,
	price DECIMAL(10, 2),
    purchase_date DATETIME DEFAULT GETDATE(),--**
	date_concert DATETIME ,--**
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
	FOREIGN KEY (artist_id,date_concert) REFERENCES Concerts(artist_id,[date])
);
----------------------------------------------------
---------------------------------------------------
CREATE TABLE Favorite_Play_list(
    user_id INT,
    [name] VARCHAR(50) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
    FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
    PRIMARY KEY (user_id, [name])
);
---------------------------------------------------
CREATE TABLE Comment_Play_list(
    user_id INT ,
	[name] VARCHAR(50) NOT NULL ,
	[text] VARCHAR(100),
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
	PRIMARY KEY (user_id,[name])
);
---------------------------------------------------
CREATE TABLE Like_Play_list(
    user_id INT ,
	[name] VARCHAR(50) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (user_id, [name]) REFERENCES Play_list(user_id, [name]),
	PRIMARY KEY(user_id,[name])
);
----------------------------------------------------
CREATE TABLE Friend(
    user_id1 INT,
	user_id2 INT,
	accept BIT DEFAULT 0,
    FOREIGN KEY (user_id1) REFERENCES Permium(user_id),
	FOREIGN KEY (user_id2) REFERENCES Permium(user_id),
	PRIMARY KEY(user_id1,user_id2)
);
----------------------------------------------------
CREATE TABLE Message_Premium (
    user_id1 INT,
    user_id2 INT,
    [text] VARCHAR(100),
    FOREIGN KEY (user_id1) REFERENCES Permium(user_id),
    FOREIGN KEY (user_id2) REFERENCES Permium(user_id),
    PRIMARY KEY (user_id1, user_id2)
);
-------------------------------------------------------
CREATE TABLE follower(
	user_id1 INT,
	user_id2 INT,
	accept BIT DEFAULT 0,
    FOREIGN KEY (user_id1) REFERENCES Permium(user_id),
	FOREIGN KEY (user_id2) REFERENCES Permium(user_id),
	PRIMARY KEY(user_id1,user_id2)
);
-------------------------------------------------------
CREATE TABLE Comment_Album (
    user_id INT,                  
    album_id INT,
    [text] VARCHAR(100),
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
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
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------
CREATE TABLE Comment_song(
    song_id INT,
	[text] VARCHAR(100),
	user_id INT,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------
CREATE TABLE Like_song(
    song_id INT ,
	user_id INT ,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------
--DROP TABLE Like_album;
CREATE TABLE Like_album(
    user_id INT ,
	album_id INT ,
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
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
    FOREIGN KEY (user_id) REFERENCES Permium(user_id),
	FOREIGN KEY (song_id) REFERENCES Songs(song_id),
	PRIMARY KEY(user_id,song_id)
);
-------------------------------------------------------