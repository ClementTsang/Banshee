#ifndef SONGDATA
#define SONGDATA
class SongData
{
public:
	SongData();
	SongData(string, string, int, char*);
	~SongData();
	string getSongName();
	string getTrimmedName();
	string getFullName();
	string getArtist();
	string getSongLength();
	void setHighScore(string);
	string getHighScore();
	char* getSongPath();
	bool operator<(const SongData &s1) const;
private:
	string songName;
	string trimName;
	string fullName;
	string artist;
	string songLength;
	string highScore;
	char* songPath;
};
#endif