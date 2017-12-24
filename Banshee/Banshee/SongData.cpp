#include "stdafx.h"
#include "SongData.h"

/// <summary>
/// Pre: None.
/// Post: Initializes SongData.
/// Initializes a new instance of the <see cref="SongData" /> class.
/// </summary>
SongData::SongData()
{
	songName = "";
	artist = "";
	songLength = "";
	songPath = "";
	highScore = "";
}

/// <summary>
/// Pre: None.
/// Post: Initialized SongData based on parameters.
/// Initializes a new instance of the <see cref="SongData" /> class.
/// </summary>
/// <param name="foo">The foo.</param>
/// <param name="bar">The bar.</param>
/// <param name="snafu">The snafu.</param>
/// <param name="bah">The bah.</param>
SongData::SongData(string foo, string bar, int snafu, char* bah)
{
	songName = foo;
	fullName = foo;
	trimName = foo;
	trimName.erase(remove_if(trimName.begin(), trimName.end(), isspace), trimName.end());

	if (songName.length() > 16)
	{
		songName.resize(16);
		songName.erase(songName.find_last_not_of(" \n\r\t") + 1);
		songName.append("...");
		//cout << "SONGNAME: " << songName << endl;
	}

	artist = bar;
	if (artist.length() > 9)
	{
		artist.resize(9);
		artist.erase(artist.find_last_not_of(" \n\r\t") + 1);
		artist.append("...");
	}

	songPath = bah;

	int min = snafu / 60;
	int sec = snafu % 60;
	songLength = to_string(min) + ":";
	if (sec < 10) songLength.append("0");
	songLength.append(to_string(sec));

	highScore = "0";
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Variables set to null.
/// Finalizes an instance of the <see cref="SongData" /> class.
/// </summary>
SongData::~SongData()
{
	songName = "";
	artist = "";
	songLength = "";
	songPath = "";
	fullName = "";
	highScore = "";
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Gets song name, after shortening.
/// Gets the shortened name of the song.
/// </summary>
/// <returns></returns>
string SongData::getSongName()
{
	return songName;
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Gets trimmed name.
/// Gets the trimmed name of the song.
/// </summary>
/// <returns></returns>
string SongData::getTrimmedName()
{
	return trimName;
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Gets full name.
/// Gets the full name of the song.
/// </summary>
/// <returns></returns>
string SongData::getFullName()
{
	return fullName;
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Gets artist.
/// Gets the artist of the song.
/// </summary>
/// <returns></returns>
string SongData::getArtist()
{
	return artist;
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Gets length.
/// Gets the length of the song.
/// </summary>
/// <returns></returns>
string SongData::getSongLength()
{
	return songLength;
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Sets high score.
/// Sets the high score of song.
/// </summary>
/// <param name="foo">The foo.</param>
void SongData::setHighScore(string foo)
{
	highScore = foo;
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Gets high score.
/// Gets the high score of song.
/// </summary>
/// <returns></returns>
string SongData::getHighScore()
{
	return highScore;
}

/// <summary>
/// Pre: Initialized SongData.
/// Post: Gets song path.
/// Gets the song path of song.
/// </summary>
/// <returns></returns>
char * SongData::getSongPath()
{
	return songPath;
}

/// <summary>
/// Pre: Initialized SongData, more than one SongData object.
/// Post: Returns whether one SongData is bigger than another.
/// For comparing SongData vectors.
/// </summary>
/// <param name="s1">The s1.</param>
/// <returns></returns>
bool SongData::operator<(const SongData & s1) const
{
	return this->songName < s1.songName;
}